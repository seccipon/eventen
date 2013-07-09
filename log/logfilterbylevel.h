#ifndef LOGFILTERBYLEVEL_H
#define LOGFILTERBYLEVEL_H


#include "logfilter.h"

#include <limits>
namespace Log
{
  class LogFilterByLevel : public LogFilter
  {
  public:
    const int LevelMaxUnlimited = std::numeric_limits<int>::max();
    const int LevelMinUnlimited = std::numeric_limits<int>::min();

    LogFilterByLevel(const PLogger & endpoint, int levelMax, int levelMin);

    virtual bool ShouldForwardMessage(const PLogMessage &logMessage);
  private:
    int m_levelMax;
    int m_levelMin;
  };
}
#endif // LOGFILTERBYLEVEL_H
