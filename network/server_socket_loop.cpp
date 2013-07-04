#include "server_socket_loop.h"
#include <sys/select.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include "network/events.h"

#include "log/log.h"




#undef LOG_DEFINE_FILELOCAL_LOGGER
#undef LOG_LOGGER_TAG
#define LOG_FILELOCAL_LOGGER Log::GetDefaultLogger()
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

  LOG("select() == %1%", % r);

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
      bool r = x->Accept(sockfd, errn);
      PEvent event;
      if (r) {
        LOG("Socket accepted successfully, socket id = %1%", % sockfd);
        event.reset(new EventStreamSocketAccepted(shared_from_this(), sockfd, x));
      } else {
        LOG("Socket accept failed, errno : %1%", % errn);
        event.reset(new EventNetworkAcceptFailed(shared_from_this(), x, errn));
      }

      PostEventAsync(event, gThreadPool);
    }
  }
}

void LoopSocketListen::Interrupt()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Loop interrupted");
  m_interruptor.TouchByWrite1Byte();
}


void LoopSocketListen::AddListenSocket(PServerSocket serverSocket)
{
  LOG_SET_LOGGER_FILELOCAL;

  boost::lock_guard<boost::mutex> lock(m_serverSocketsToAddMutex);
  m_serverSocketsToAdd.push_back(serverSocket);
  LOG("Added new listen socket: %1%", % serverSocket->GetSocket());
}

void LoopSocketListen::GrabNewListenSockets()
{
  LOG_SET_LOGGER_FILELOCAL;
  boost::lock_guard<boost::mutex> lock(m_serverSocketsToAddMutex);

  for (auto & x : m_serverSocketsToAdd) {
    m_serverSockets.push_back(x);
    LOG("Socket %1% grabbed to loop", % x->GetSocket());
  }
  m_serverSocketsToAdd.clear();


}

void LoopSocketListen::Init()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Initialized");
}

void LoopSocketListen::Destroy()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Uninitialized");

}

void LoopSocketListen::DoBreak()
{
  LOG_SET_LOGGER_FILELOCAL;
  LOG("Break");
  Interrupt();
}
