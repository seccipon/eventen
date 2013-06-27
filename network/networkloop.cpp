#include "networkloop.h"
#include <sys/select.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include "engine_eht/event/network/eventstreamsocketaccepted.h"
#include "engine_eht/event/network/event_socket_ready_to_accept.h"

void NetworkLoop::OneLoop()
{
  fd_set fdsetRead, fdsetWrite;
  FD_ZERO(&fdsetRead);
  FD_ZERO(&fdsetWrite);

  FD_SET(m_interruptPipe[0], &fdsetRead);

  for (auto &x : m_serverSockets) {
    FD_SET(x->GetSocket(), &fdsetRead);
  }


  int nfds = 1024;


  timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  int r = ::select(nfds, &fdsetRead, &fdsetWrite, NULL, &tv);


  for (auto &x : m_serverSockets) {
    if (FD_ISSET(x->GetSocket(), &fdsetRead)) {
        PostEvent(PEvent(new EventSocketReadyToAccept(shared_from_this(), x)));
    }
  }
}

void NetworkLoop::Interrupt()
{
  m_interrupt = true;
  char t = 0;
  while(write(m_interruptPipe[1], &t, sizeof(t)) < 1);
}


void NetworkLoop::AddListenSocket(PServerSocket serverSocket)
{
  m_serverSockets.push_back(serverSocket);
}

void NetworkLoop::Init()
{
  assert(::pipe2(m_interruptPipe, O_NONBLOCK) != -1);
}

void NetworkLoop::Destroy()
{
  close(m_interruptPipe[0]);
  close(m_interruptPipe[1]);
}


bool NetworkLoop::IsInterrupted()
{
  return m_interrupt;
}
