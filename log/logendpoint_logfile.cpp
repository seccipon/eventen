#include "logendpoint_logfile.h"


#include <boost/format.hpp>
#include <boost/date_time.hpp>
namespace Log
{

  Logger_logfile::Logger_logfile(std::shared_ptr<std::ostream> ostream, PLogFormatter formatter) :
    Logger_ostream(ostream, formatter)
  {
    GetOstream() << boost::format("=== Logfile created by pid %1% at %2% ===")
                  % ::getpid() % boost::posix_time::microsec_clock::local_time()  << std::endl;
  }

  Logger_logfile::~Logger_logfile()
  {
    GetOstream() << boost::format("=== Logfile writing done at %1% ===")
                  % boost::posix_time::microsec_clock::local_time()  << std::endl;
  }
}
