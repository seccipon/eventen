
#include "logfilter.h"
namespace Log
{
  void LogFilter::PushMessage(const Log::PLogMessage &message)
  {
    if (ShouldForwardMessage(message)) {
      m_endpoint->PushMessage(message);
    }
  }

}


