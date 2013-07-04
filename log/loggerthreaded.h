#ifndef LOGGERTHREADED_H
#define LOGGERTHREADED_H

#include "logger.h"
#include "logformatter.h"
#include "logendpoint.h"
#include "logfilter.h"
#include "multithread/threadpool.h"
#include "multithread/shared_queue.h"
#include "general/loop.h"

namespace Log
{
  class LoggerThreaded : public ILogger, public Loop
  {
  public:
    LoggerThreaded(PLogFilter filter, PLogEndpoint endpoint);
    virtual void PushMessage(const LogMessage &message);

    virtual void OneLoop();
    virtual void Init();
    virtual void Destroy();
    virtual void DoBreak();
  private:
    SharedQueue<PLogMessage> m_queue;

    PLogFilter m_filter;
    PLogEndpoint m_endpoint;
  };
  typedef std::shared_ptr<LoggerThreaded> PLoggerThreaded;


}
#endif // LOGGERTHREADED_H
