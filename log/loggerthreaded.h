#ifndef LOGGERTHREADED_H
#define LOGGERTHREADED_H

#include "logger.h"
#include "logformatter.h"

#include "logfilter.h"
#include "multithread/threadpool.h"
#include "multithread/shared_queue.h"
#include "general/loop.h"

namespace Log
{
  class LoggerThreaded : public ILogger, public Loop
  {
  public:
    LoggerThreaded(PLogger endpoint);
    virtual void PushMessage(const PLogMessage &message);

    virtual void OneLoop();
    virtual void Init();
    virtual void Destroy();
    virtual void DoBreak();
  private:
    SharedQueue<PLogMessage> m_queue;

    PLogger m_endpoint;
  };
  typedef std::shared_ptr<LoggerThreaded> PLoggerThreaded;


}
#endif // LOGGERTHREADED_H
