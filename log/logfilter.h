#ifndef LOGFILTER_H
#define LOGFILTER_H


#include "logmessage.h"
#include "logger.h"
#include <memory.h>
namespace Log
{
  class LogFilter : public ILogger
  {
  public :
    LogFilter(const PLogger & endpoint) :
      m_endpoint(endpoint)
    {  }

    virtual void PushMessage(const PLogMessage &message);
  protected:
    virtual bool ShouldForwardMessage(const PLogMessage & logMessage) = 0;
  private:
    PLogger m_endpoint;
  };
}
#endif // LOGFILTER_H
