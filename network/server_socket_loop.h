#ifndef NETWORKLOOP_H
#define NETWORKLOOP_H

#include "general/loop.h"
#include "engine_eht/task/task.h"
#include "network/server_socket.h"
#include "network/pipeinterruptor.h"

#include <boost/noncopyable.hpp>
#include <deque>
#include <vector>

class ServerSocketLoop : public Loop, public Task, public boost::noncopyable, public std::enable_shared_from_this<ServerSocketLoop>
{
public:
  explicit ServerSocketLoop(PEventHandler eh, int timeout) :
    Task(eh),
    m_timeout(timeout)
  {
  }

  virtual ~ServerSocketLoop()
  {}

  void AddListenSocket(PServerSocket serverSocket);
  void GrabNewListenSockets();

  virtual void Init();
  virtual void Destroy();

  virtual void OneLoop();
  void Interrupt();

private:

  virtual void DoBreak();

  int m_timeout;
  PipeInterruptor m_interruptor;
  std::vector<PServerSocket> m_serverSockets;
  boost::mutex m_serverSocketsToAddMutex;
  std::deque<PServerSocket> m_serverSocketsToAdd;
};


typedef std::shared_ptr<ServerSocketLoop> PServerSocketLoop;
#endif // NETWORKLOOP_H
