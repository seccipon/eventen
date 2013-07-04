#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

#include "logmessage.h"
#include <memory>

namespace Log
{
  class ILogFormatter
  {
  public:
    virtual std::string DoFormatMessage(const LogMessage & message) = 0;
  };
  typedef std::shared_ptr<ILogFormatter> PLogFormatter;
}
#endif // LOGFORMATTER_H
