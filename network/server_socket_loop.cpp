#include "server_socket_loop.h"
#include <sys/select.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include "network/events.h"
using namespace std;
void LoopSocketListen::OneLoop()
{
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


  if (FD_ISSET(m_interruptor.GetPipeReadFd(), &fdsetRead)) {
    cout << "Interrupted" << endl;
    m_interruptor.FlushRead();
  }

  for (auto &x : m_serverSockets) {
    if (!r) {
      break;
    }

    if (FD_ISSET(x->GetSocket(), &fdsetRead)) {
      r--;
      int sockfd = -1;
      bool r = x->Accept(sockfd);
      PEvent event;
      if (r) {
        event.reset(new EventStreamSocketAccepted(shared_from_this(), sockfd, x));
      } else {
        event.reset(new EventNetworkAcceptFailed(shared_from_this(), x, errno));
      }

      PostEventAsync(event, gThreadPool);
    }
  }
}

void LoopSocketListen::Interrupt()
{
  m_interruptor.TouchByWrite1Byte();
}


void LoopSocketListen::AddListenSocket(PServerSocket serverSocket)
{
  boost::lock_guard<boost::mutex> lock(m_serverSocketsToAddMutex);
  m_serverSocketsToAdd.push_back(serverSocket);
}

void LoopSocketListen::GrabNewListenSockets()
{
  boost::lock_guard<boost::mutex> lock(m_serverSocketsToAddMutex);


  for (auto & x : m_serverSocketsToAdd) {
    m_serverSockets.push_back(x);
  }
  m_serverSocketsToAdd.clear();
}

void LoopSocketListen::Init()
{

}

void LoopSocketListen::Destroy()
{

}

void LoopSocketListen::DoBreak()
{
  Interrupt();
}
