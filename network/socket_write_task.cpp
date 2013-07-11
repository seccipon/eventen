#include "socket_write_task.h"

#include "network/events.h"
#include "exceptions/exceptions.h"

#include "log/log.h"
SocketWriteTask::SocketWriteTask(PEventHandler eh, PStreamSocket pSocket, const Buffer &buffer) :
  Task(eh),
  m_socket(pSocket),
  m_buffer(buffer),
  m_sentCnt(0)
{

}

PStreamSocket SocketWriteTask::GetStreamSocket()
{
  return m_socket;
}

SocketWriteTask::Result SocketWriteTask::DoWrite()
{
  try {
    if (m_socket->Write(m_buffer.GetBuffer() + m_sentCnt, m_buffer.GetSz() - m_sentCnt, m_sentCnt) ==
        StreamSocket::WriteResult::RES_EOF)
    {
      PostEventAsync(PEvent(new EventSocketWriteEOF(m_socket)), gThreadPool);
    }
  } catch(ExceptionLibcall & e) {
    Log::GetLogicErrorLogger()->PushMessage(LOG_MSG_LEV(LOG_LEVEL_FATAL, (boost::format("libcall exception while Write() %1%") % e.what()).str()));
    PostEventAsync(PEvent(new EventSocketError(m_socket)), gThreadPool);
    return Result::RES_COMPLETED;

  } catch(...) {
    Log::GetLogicErrorLogger()->PushMessage(LOG_MSG_LEV(LOG_LEVEL_FATAL, "Unknown exception while Write()"));
    PostEventAsync(PEvent(new EventSocketError(m_socket)), gThreadPool);
    return Result::RES_COMPLETED;
  }

  if (m_sentCnt == m_buffer.GetSz()) {
    PostEventAsync(PEvent(new EventSocketWriteCompleted(m_socket)), gThreadPool);
    return Result::RES_COMPLETED;
  }
  return Result::RES_NOT_COMPLETED;
}
