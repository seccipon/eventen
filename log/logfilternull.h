#ifndef LOGFILTERNULL_H
#define LOGFILTERNULL_H
#include"logfilter.h"

namespace Log
{
  class LogFilterNull : public ILogFilter
  {
    virtual bool DoForwardMessage(const LogMessage &logMessage);
  };
}
#endif // LOGFILTERNULL_H
