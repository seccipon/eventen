#include "logfilternull.h"


namespace Log
{
  bool LogFilterNull::ShouldForwardMessage(const PLogMessage &logMessage)
  {
    return true;
  }

  LogFilterNull::LogFilterNull(const PLogger &endpoint) :
    LogFilter(endpoint)
  {

  }

}

