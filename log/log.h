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

namespace Log
{

}
#endif // LOG_H
