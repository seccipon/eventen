#ifndef NETWORKLOOP_H
#define NETWORKLOOP_H

#include "general/loop.h"
#include "engine_eht/task/task.h"
#include "network/server_socket.h"
#include "network/pipeinterruptor.h"

#include <boost/noncopyable.hpp>
#include <deque>
#include <vector>


template <typename EventHandlerType>
class LoopSocketListen : public Loop,
                         public Task<EventHandlerType>,
                         public boost::noncopyable,
                         public std::enable_shared_from_this<LoopSocketListen<EventHandlerType> >
{
public:
  typedef std::shared_ptr<EventHandlerType> PEventHandler;
  explicit LoopSocketListen(PEventHandler eh, int timeout) :
    Task<EventHandlerType>(eh),
    m_maxNfds(0),
    m_timeout(timeout)
  {
  }

  virtual ~LoopSocketListen()
  {}

  void AddListenSocket(PServerSocket serverSocket);
  void GrabNewListenSockets();

  virtual void Init();
  virtual void Destroy();

  virtual void OneLoop();
  void Interrupt();

private:

  virtual void DoBreak();

private:
  int m_maxNfds;
  int m_timeout;
  PipeInterruptor m_interruptor;


  boost::mutex m_serverSocketsToAddMutex;
  std::vector<PServerSocket> m_serverSockets;
  std::deque<PServerSocket> m_serverSocketsToAdd;
};

#endif // NETWORKLOOP_H
