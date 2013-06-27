#ifndef NETWORKLOOP_H
#define NETWORKLOOP_H

#include "general/loop.h"
#include "engine_eht/task/task.h"
#include <boost/noncopyable.hpp>
#include "network/serversocket.h"
#include <vector>

class NetworkLoop : public Loop, public Task, public boost::noncopyable, public std::enable_shared_from_this<NetworkLoop>
{
public:
  explicit NetworkLoop(PEventHandler eh, int timeout) :
    Task(eh),
    m_interrupt(false),
    m_timeout(timeout)
  {
    m_interruptPipe[0] = m_interruptPipe[1] = 0;
  }

  virtual ~NetworkLoop()
  {}

  void AddListenSocket(PServerSocket serverSocket);


  virtual void Init();
  virtual void Destroy();

  virtual void OneLoop();
  virtual void Interrupt();
  virtual bool IsInterrupted();

private:
  bool m_interrupt;

  int m_timeout;
  int m_interruptPipe[2];

  std::vector<PServerSocket> m_serverSockets;

};


typedef std::shared_ptr<NetworkLoop> PNetworkLoop;
#endif // NETWORKLOOP_H
