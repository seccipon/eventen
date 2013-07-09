#include "loggersimple.h"


namespace Log
{
  LoggerSimple::LoggerSimple(PLogger endpoint) :
    m_endpoint(endpoint)
  {
  }

  void LoggerSimple::PushMessage(const PLogMessage &message)
  {
      m_endpoint->PushMessage(message);
  }
}
