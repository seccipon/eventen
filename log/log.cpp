#include "loggersimple.h"
#include "logendpoint_stderr.h"
#include "logfilternull.h"
#include "logendpoint_ostream.h"
#include "logformatterdefault.h"
#include "loggerthreaded.h"
#include "multithread/threadpool.h"


#include <fstream>


namespace Log
{
  PLogger gDefaultLogger, gNetworkLogger, gLogicErrorLogger, gEventLogger, gThreadLogger;
  PThreadPool gLogThreadPool;


//  PLogger CreateSimpleFileLogger(const std::string &fileName)
//  {
//    std::shared_ptr<std::ostream> pOstream(new std::ofstream(fileName));
//    Log::PLogFormatter logFormatter(new Log::LogFormatterDefault);
//    Log::PLogEndpoint logEndpoint(new Log::LogEndpoint_ostream(pOstream, logFormatter));
//    Log::PLogFilter logFilter(new Log::LogFilterNull);
//    Log::PLogger logger(new Log::LoggerThreaded(logFilter, logEndpoint));
//    return logger;
//  }

  void InitLoggerThreadPool() {
    gLogThreadPool.reset(new ThreadPool);
    gLogThreadPool->Init(10);
  }

  void InitDefaultLogger()
  {
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_stderr(formatter));

    gDefaultLogger.reset(new LoggerThreaded(filter, endpoint));
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
    PLoggerThreaded lg(new LoggerThreaded(filter, endpoint));
    gNetworkLogger = lg;
  }

  PLogger GetNetworkLogger()
  {
    return gNetworkLogger;
  }

  void InitLogicErrorLogger()
  {
    std::shared_ptr<std::ostream> pOstream(new std::ofstream("logic_error.log"));
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_ostream(pOstream, formatter));
    PLoggerThreaded lg(new LoggerThreaded(filter, endpoint));
    gLogicErrorLogger = lg;
  }

  PLogger GetLogicErrorLogger()
  {
    return gLogicErrorLogger;
  }

  void InitEventLogger()
  {
    std::shared_ptr<std::ostream> pOstream(new std::ofstream("event.log"));
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_ostream(pOstream, formatter));
    PLoggerThreaded lg(new LoggerThreaded(filter, endpoint));
    gEventLogger = lg;
  }

  PLogger GetEventLogger()
  {
    return gEventLogger;
  }

  void InitThreadLogger()
  {
    std::shared_ptr<std::ostream> pOstream(new std::ofstream("thread.log"));
    PLogFormatter formatter (new LogFormatterDefault);
    PLogFilter filter (new LogFilterNull);
    PLogEndpoint endpoint (new LogEndpoint_ostream(pOstream, formatter));
    PLoggerThreaded lg(new LoggerThreaded(filter, endpoint));
    gThreadLogger = lg;
  }

  PLogger GetThreadLogger()
  {
    return gThreadLogger;
  }

  void InitLoggers()
  {
    InitDefaultLogger();
    InitEventLogger();
    InitLogicErrorLogger();
    InitNetworkLogger();
    InitThreadLogger();

    InitLoggerThreadPool();

    gLogThreadPool->PostRunnable(std::dynamic_pointer_cast<IRunnable>(GetThreadLogger()));
    gLogThreadPool->PostRunnable(std::dynamic_pointer_cast<IRunnable>(GetEventLogger()));
    gLogThreadPool->PostRunnable(std::dynamic_pointer_cast<IRunnable>(GetNetworkLogger()));
    gLogThreadPool->PostRunnable(std::dynamic_pointer_cast<IRunnable>(GetDefaultLogger()));
    gLogThreadPool->PostRunnable(std::dynamic_pointer_cast<IRunnable>(GetLogicErrorLogger()));
  }

  void DestroyLoggers()
  {
    std::dynamic_pointer_cast<Loop>(GetThreadLogger())->Break();
    std::dynamic_pointer_cast<Loop>(GetEventLogger())->Break();
    std::dynamic_pointer_cast<Loop>(GetNetworkLogger())->Break();
    std::dynamic_pointer_cast<Loop>(GetDefaultLogger())->Break();
    std::dynamic_pointer_cast<Loop>(GetLogicErrorLogger())->Break();

    gLogThreadPool->Stop();
    gLogThreadPool->Join();
  }

}
