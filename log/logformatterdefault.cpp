#include "logformatterdefault.h"
#include <array>
#include <boost/format.hpp>


std::string Log::LogFormatterDefault::DoFormatMessage(const PLogMessage &message)
{
  std::stringstream ss;
  ss << (boost::format(std::string(" [ %1% ] %2% [%3%] { %4%: %5% } >> \n\t%6% >> \n\t\t%7%\n"))
         % message->Id() % message->Time() % message->Level() % message->File() % message->Line()) % message->Tag() % message->Message();
  return ss.str();
}
