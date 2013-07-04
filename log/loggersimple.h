#ifndef LOGGERSIMPLE_H
#define LOGGERSIMPLE_H

#include "logger.h"
#include "logformatterdefault.h"
#include "logendpoint_stderr.h"
#include "logfilter.h"

namespace Log
{
  class LoggerSimple : public ILogger
  {
  public:
    LoggerSimple(PLogFilter filter, PLogEndpoint endpoint);
    virtual void PushMessage(const LogMessage &message);
  private:
    PLogFilter m_filter;
    PLogEndpoint m_endpoint;
  };
}
#endif // LOGGERSIMPLE_H
