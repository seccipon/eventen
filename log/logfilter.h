#ifndef LOGFILTER_H
#define LOGFILTER_H


#include "logmessage.h"
#include <memory.h>
namespace Log
{
  class ILogFilter
  {
  public:
    virtual bool DoForwardMessage(const LogMessage & logMessage) = 0;
  };
  typedef std::shared_ptr<ILogFilter> PLogFilter;
}
#endif // LOGFILTER_H
