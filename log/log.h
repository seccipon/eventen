#ifndef LOG_H
#define LOG_H
#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#define EVENTEN_LOG(formatstr,val) \
  std::cerr <<  "[ " <<  boost::posix_time::microsec_clock::local_time() << " ]" << (boost::format(std::string(" %s: %u >> "))  % __FILE__ % __LINE__) << (boost::format(formatstr) % val) << std::endl;
#define LOG EVENTEN_LOG
#define TRACK(val) \
  EVENTEN_LOG("%1% == %2%", std::string(#val) % val)



#define LOG_BASE(logger,level,formatstr,val) \
{\
  Log::LogMessage lm((level), __FILE__, __LINE__, (boost::format(std::string(formatstr)) % val).str(), boost::posix_time::microsec_clock::local_time()); \
  logger->PushMessage(lm); \
}

#define LOG0_GLOB(formatstr,val) LOG_BASE(Log::gDefaultLogger, 0, formatstr, val)

#include "loggersimple.h"
namespace Log
{
  extern PLogger gDefaultLogger;
  void InitDefaultLogger();
}
#endif // LOG_H
