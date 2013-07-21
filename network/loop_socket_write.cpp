#include "loop_socket_write.h"


#include "network/events.h"
#include "log/log.h"
#include "util/assertion.h"
#include <boost/thread/mutex.hpp>
#include <utility>
#include <errno.h>

#undef LOG_DEFINE_FILELOCAL_LOGGER
#undef LOG_LOGGER_TAG
#define LOG_FILELOCAL_LOGGER Log::GetNetworkLogger()
#define LOG_LOGGER_TAG "NETW"

void LoopSocketWrite::OneLoop()
{
  LOG_SET_LOGGER_FILELOCAL;

  fd_set writeSet;
  int maxfd = 0;
  FillFdSet(writeSet, maxfd);

  int r = ::select(maxfd + 1, NULL, &writeSet, NULL, NULL);
  TRACK(r);

  if (r == -1) {
    throw EXCEPTION_LIBCALL((boost::format("select failed : %1%") % std::string(::strerror(errno))).str());
  }

  {
    boost::lock_guard<boost::mutex> lock(m_SSmutex);

    for (auto i = m_SocketToSocketWriteTask.begin(); i != m_SocketToSocketWriteTask.end(); ++i) {
      if (FD_ISSET(i->first, &writeSet)) {
        SocketWriteTask::Result res = i->second->DoWrite();
        if (res == SocketWriteTask::Result::RES_COMPLETED) {
          m_SocketToSocketWriteTask.erase(i);
        }
      }
    }
  }
}

void LoopSocketWrite::PostWriteTask(PSocketWriteTask task)
{
  boost::lock_guard<boost::mutex> lock(m_SSmutex);
  m_SocketToSocketWriteTask.insert(
        std::pair<int, PSocketWriteTask>(task->GetStreamSocket()->GetSocket(), task));

}

void LoopSocketWrite::FillFdSet(fd_set &st, int & max_fd)
{
  boost::lock_guard<boost::mutex> lock(m_SSmutex);
  max_fd = 0;

  FD_ZERO(&st);
  FD_SET(m_interruptor.GetPipeReadFd(), &st);
  max_fd = std::max(max_fd, m_interruptor.GetPipeReadFd());
  for (auto & x : m_SocketToSocketWriteTask) {
    FD_SET(x.first, &st);
    max_fd = std::max(max_fd, x.first);
  }
}

