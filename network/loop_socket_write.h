#ifndef LOOP_SOCKET_WRITE_H
#define LOOP_SOCKET_WRITE_H

#include "general/loop.h"
#include "engine_eht/task/task.h"
#include "network/pipeinterruptor.h"
#include "socket_write_task.h"

#include <vector>

template<typename EventHandlerType>
class LoopSocketWrite : public Loop, public Task<EventHandlerType>, public boost::noncopyable, public std::enable_shared_from_this<LoopSocketWrite>
{
public:
  explicit LoopSocketWrite(PEventHandler eh, int timeout) :
    Task(eh)
  {   }

  virtual ~LoopSocketWrite()
  {   }

  virtual void OneLoop();

  void PostWriteTask(PSocketWriteTask task);

private:

  PipeInterruptor m_interruptor;

  void FillFdSet(fd_set & st, int & max_fd);

  std::multimap<int, PSocketWriteTask> m_SocketToSocketWriteTask;
  boost::mutex m_SSmutex;
};

#endif // LOOP_SOCKET_WRITE_H
