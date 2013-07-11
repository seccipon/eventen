#include "logformatterdefault.h"
#include <array>
#include <boost/format.hpp>

#include "util/formatutil.h"
std::string Log::LogFormatterDefault::DoFormatMessage(const PLogMessage &message)
{
  std::stringstream ss;
  ss << (boost::format(std::string("[ %09d ] %s [ %d ] { %s: %d } \t >> %s\n\t%s\n"))
         % message->Id() % Util::FormatDate(message->Time()) % message->Level() % message->File() % message->Line()) % message->Tag() % message->Message();
  return ss.str();
}
