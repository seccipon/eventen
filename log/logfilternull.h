#ifndef LOGFILTERNULL_H
#define LOGFILTERNULL_H
#include"logfilter.h"

namespace Log
{
  class LogFilterNull : public LogFilter
  {
  public:
    LogFilterNull(const PLogger & endpoint);
    virtual bool ShouldForwardMessage(const PLogMessage &logMessage);
  };
}
#endif // LOGFILTERNULL_H
