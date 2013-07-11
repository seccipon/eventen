#ifndef FORMATUTIL_H
#define FORMATUTIL_H

#include <string>
#include "boost/date_time/posix_time/ptime.hpp"

namespace Util
{
  std::string FormatDate(const boost::posix_time::ptime & time);
}
#endif // FORMATUTIL_H
