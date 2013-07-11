#ifndef LOGGERSIMPLE_H
#define LOGGERSIMPLE_H

#include "logger.h"
#include "logformatter.h"

#include "logfilter.h"

namespace Log
{
  class LoggerSimple : public ILogger
  {
  public:
    LoggerSimple(PLogger endpoint);
    virtual void PushMessage(const PLogMessage &message);
  private:
    PLogger m_endpoint;
  };
}
#endif // LOGGERSIMPLE_H
