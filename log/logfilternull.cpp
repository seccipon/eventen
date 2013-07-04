#include "logfilternull.h"


namespace Log
{
  bool LogFilterNull::DoForwardMessage(const Log::LogMessage &logMessage)
  {
    return true;
  }
}

