#ifndef LOGFORMATTERDEFAULT_H
#define LOGFORMATTERDEFAULT_H


#include "logformatter.h"
namespace Log  {
class LogFormatterDefault : public ILogFormatter
{
public:
  std::string DoFormatMessage(const LogMessage &message);
};
}
#endif // LOGFORMATTERDEFAULT_H
