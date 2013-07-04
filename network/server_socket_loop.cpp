#include "server_socket_loop.h"
#include <sys/select.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include "network/events.h"

#include "log/log.h"
#include "util/assertion.h"

#undef LOG_DEFINE_FILELOCAL_LOGGER
#undef LOG_LOGGER_TAG
#define LOG_FILELOCAL_LOGGER Log::GetNetworkLogger()
#define LOG_LOGGER_TAG "Network accept loop"

using namespace std;
void LoopSocketListen::OneLoop()
{
  LOG_SET_LOGGER_FILELOCAL;
  GrabNewListenSockets();

  fd_set fdsetRead;
  FD_ZERO(&fdsetRead);

  FD_SET(m_interruptor.GetPipeReadFd(), &fdsetRead);

  for (auto &x : m_serverSockets) {
    FD_SET(x->GetSocket(), &fdsetRead);
  }

  int nfds = 1024;

  timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  int r = ::select(nfds, &fdsetRead, NULL, NULL, &tv);

  LOG("Loop{%1%} select() == %2%", % this % r);

  if (FD_ISSET(m_interruptor.GetPipeReadFd(), &fdsetRead)) {
    m_interruptor.FlushRead();
  }

  for (auto &x : m_serverSockets) {
    if (!r) {
      break;
    }
    if (FD_ISSET(x->GetSocket(), &fdsetRead)) {

      r--;
      int sockfd = -1;
      int errn = 0;
      bool res = x->Accept(sockfd, errn);
      PEvent event;
      if (res) {
        LOG("Loop{%1%} Socket accepted successfully, socket id = %2%",  % this % sockfd);
        event.reset(new EventStreamSocketAccepted(shared_from_this(), sockfd, x));
      } else {
        LOG("Loop{%1%} Socket accept failed, errno : %2%",  % this % errn);
        event.reset(new EventNetworkAcceptFailed(shared_from_this(), x, errn));
      }

      PostEventAsync(event, gThreadPool);
    }
  }
}

void LoopSocketListen::Interrupt()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Loop{%1%} Interrupted", % this );
  m_interruptor.TouchByWrite1Byte();
}


void LoopSocketListen::AddListenSocket(PServerSocket serverSocket)
{
  LOG_SET_LOGGER_FILELOCAL;

  boost::lock_guard<boost::mutex> lock(m_serverSocketsToAddMutex);
  m_serverSocketsToAdd.push_back(serverSocket);
  LOG("Loop{%1%}  Added new listen socket: %2%, port: %3%", % this % serverSocket->GetSocket() % serverSocket->GetPort());
}

void LoopSocketListen::GrabNewListenSockets()
{
  LOG_SET_LOGGER_FILELOCAL;
  boost::lock_guard<boost::mutex> lock(m_serverSocketsToAddMutex);

  for (auto & x : m_serverSocketsToAdd) {
    m_serverSockets.push_back(x);
    LOG("Loop{%1%}  Socket %2% (port %3%) grabbed to loop", % this % x->GetSocket() % x->GetPort());
  }
  m_serverSocketsToAdd.clear();
}

void LoopSocketListen::Init()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Loop{%1%}  Initialized", % this);
}

void LoopSocketListen::Destroy()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Loop{%1%} Uninitialized", % this);

}

void LoopSocketListen::DoBreak()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Loop{%1%} Break", % this);
  Interrupt();
}
