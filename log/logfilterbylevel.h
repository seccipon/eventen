#ifndef LOGFILTERBYLEVEL_H
#define LOGFILTERBYLEVEL_H


#include "logfilter.h"

#include <limits>
namespace Log
{
  class LogFilterByLevel : public ILogFilter
  {
  public:
    const int LevelMaxUnlimited = std::numeric_limits<int>::max();
    const int LevelMinUnlimited = std::numeric_limits<int>::min();
    LogFilterByLevel(int levelMax, int levelMin);
    virtual bool DoForwardMessage(const LogMessage &logMessage);
  private:
    int m_levelMax;
    int m_levelMin;
  };
}
#endif // LOGFILTERBYLEVEL_H
