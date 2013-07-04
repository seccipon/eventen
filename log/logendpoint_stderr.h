#ifndef LOGENDPOINT_STDERR_H
#define LOGENDPOINT_STDERR_H

#include "logendpointformatted.h"
#include "logformatter.h"
namespace Log
{
  class LogEndpoint_stderr : public LogEndpointFormatted
  {
  public:
    LogEndpoint_stderr(PLogFormatter formatter) :
      LogEndpointFormatted(formatter)
    {  }

    void DoWriteLogMessage(const LogMessage &message);
  private:
    PLogFormatter m_formatter;
  };
}
#endif // LOGENDPOINT_STDERR_H
