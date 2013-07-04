#include "logfilterbylevel.h"


namespace Log
{
    LogFilterByLevel::LogFilterByLevel(int levelMax, int levelMin) :
      m_levelMax(levelMax),
      m_levelMin(levelMin)
    {    }

    bool LogFilterByLevel::DoForwardMessage(const LogMessage &logMessage)
    {
      return m_levelMin <= logMessage.Level() && logMessage.Level() <= m_levelMax;
    }
}
