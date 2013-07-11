#include "formatutil.h"
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <iostream>
#include <sstream>

std::string Util::FormatDate(const boost::posix_time::ptime &time)
{
  std::stringstream ss;

  static std::locale loc(ss.getloc(),
                         new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S%F"));

  ss.imbue(loc);
  ss << time;
  return ss.str();
}

