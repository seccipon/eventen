#include "log.h"

#include "loggersimple.h"
#include "logendpoint_stderr.h"
#include "logfilternull.h"
#include "logendpoint_ostream.h"




namespace Log
{
  PLogger gDefaultLogger, gNetworkLogger;

  void InitDefaultLogger()
  {
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_stderr(formatter));

    gDefaultLogger.reset(new LoggerSimple(filter, endpoint));
  }

  PLogger CreateSimpleFileLogger(const std::string &fileName)
  {
    std::shared_ptr<std::ostream> pOstream(new std::ofstream(fileName));
    Log::PLogFormatter logFormatter(new Log::LogFormatterDefault);
    Log::PLogEndpoint logEndpoint(new Log::LogEndpoint_ostream(pOstream, logFormatter));
    Log::PLogFilter logFilter(new Log::LogFilterNull);
    Log::PLogger logger(new Log::LoggerSimple(logFilter, logEndpoint));
    return logger;
  }

  PLogger GetDefaultLogger()
  {
    return gDefaultLogger;
  }

  void InitNetworkLogger()
  {
    std::shared_ptr<std::ostream> pOstream(new std::ofstream("network.log"));
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_ostream(pOstream, formatter));
    gNetworkLogger.reset(new LoggerSimple(filter, endpoint));
  }

  PLogger GetNetworkLogger()
  {
    return gNetworkLogger;
  }

}
