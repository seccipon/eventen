#include "logformatterdefault.h"
#include <array>
#include <boost/format.hpp>


std::string Log::LogFormatterDefault::DoFormatMessage(const Log::LogMessage &message)
{
  std::stringstream ss;
  ss << "[ " <<  message.Time() << " ]"
     << (boost::format(std::string(" [%i] [ %s ] {%s: %u} >> %s"))
         % message.Level() % message.Tag() % message.File() % message.Line()) % message.Message();
  return ss.str();
}
