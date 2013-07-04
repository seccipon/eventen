#include "log.h"

#include "loggersimple.h"
#include "logendpoint_stderr.h"
#include "logfilternull.h"





namespace Log
{
  PLogger gDefaultLogger;

  void InitDefaultLogger()
  {
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_stderr(formatter));

    gDefaultLogger.reset(new LoggerSimple(filter, endpoint));
  }
}
