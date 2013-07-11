#ifndef SOCKET_WRITE_TASK_H
#define SOCKET_WRITE_TASK_H

#include "engine_eht/task/task.h"
#include "stream_socket.h"
#include "util/buffer.h"
class SocketWriteTask : public Task
{
public:

  enum class Result
  {
    RES_COMPLETED,
    RES_NOT_COMPLETED
  };

  explicit SocketWriteTask(PEventHandler eh, PStreamSocket pSocket, const Buffer & buffer);
  PStreamSocket GetStreamSocket();

  Result DoWrite();
private:
  PStreamSocket m_socket;
  Buffer m_buffer;

  uint64_t m_sentCnt;
};

typedef std::shared_ptr<SocketWriteTask> PSocketWriteTask;

#endif // SOCKET_WRITE_TASK_H
