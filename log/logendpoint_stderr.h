#ifndef LOGENDPOINT_STDERR_H
#define LOGENDPOINT_STDERR_H

#include "logendpoint.h"
#include "logformatter.h"
namespace Log
{
  class LogEndpoint_stderr : public ILogEndpoint
  {
  public:
    LogEndpoint_stderr(PLogFormatter formatter) :
      m_formatter(formatter)
    {  }

    void DoWriteLogMessage(const LogMessage &message);
  private:
    PLogFormatter m_formatter;
  };
}
#endif // LOGENDPOINT_STDERR_H
