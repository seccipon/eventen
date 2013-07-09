#include "logfilterbylevel.h"


namespace Log
{
    LogFilterByLevel::LogFilterByLevel(const PLogger &endpoint, int levelMax, int levelMin) :
      LogFilter(endpoint),
      m_levelMax(levelMax),
      m_levelMin(levelMin)
    {    }

    bool LogFilterByLevel::ShouldForwardMessage(const PLogMessage &logMessage)
    {
      return m_levelMin <= logMessage->Level() && logMessage->Level() <= m_levelMax;
    }
}
