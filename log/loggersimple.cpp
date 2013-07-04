#include "loggersimple.h"


namespace Log
{
  LoggerSimple::LoggerSimple(PLogFilter filter, PLogEndpoint endpoint) :
    m_filter(filter),
    m_endpoint(endpoint)
  {
  }

  void LoggerSimple::PushMessage(const LogMessage &message)
  {
    if (m_filter->DoForwardMessage(message)) {
      m_endpoint->DoWriteLogMessage(message);
    }
  }
}
