#ifndef LOGGER_CUMULATIVE_H
#define LOGGER_CUMULATIVE_H

#include "logger.h"
#include "logfilter.h"
#include "logfilternull.h"
#include "logformatter.h"

#include <deque>

namespace Log
{
  class LoggerCumulative : public ILogger
  {
  public:
    LoggerCumulative(PLogger endpoint,
                     const PLogMessage & initialMessage);

    virtual void PushMessage(const PLogMessage &message);

    void Success(const PLogMessage & message);
    void Fail(const PLogMessage &message);

    virtual ~LoggerCumulative();

  private:

    void Commit();
    PLogMessage SquashMessages();

private:

    PLogger m_endpoint;
    PLogMessage m_initialMessage;
    PLogMessage m_finalMessage;

    bool m_success;
    bool m_finalized;


    std::deque<PLogMessage> m_logMessages;

  };

  class LoggerFormatterCumulative : public ILogFormatter
  {
  public:
    virtual std::string DoFormatMessage(const PLogMessage &message);
  };
}
#endif // LOGGER_CUMULATIVE_H
