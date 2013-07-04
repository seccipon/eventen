
#include "logendpoint_ostream.h"
#include <boost/format.hpp>
#include <boost/date_time.hpp>
namespace Log
{
  void LogEndpoint_ostream::DoWriteLogMessage(const Log::LogMessage &message)
  {
    *m_ostream << GetFormattedMessage(message) << std::endl;
  }

  LogEndpoint_ostream::~LogEndpoint_ostream()
  {
    *m_ostream << boost::format("=== Logfile writing done at %1% ===")
                  % boost::posix_time::microsec_clock::local_time()  << std::endl;
  }

  LogEndpoint_ostream::LogEndpoint_ostream(std::shared_ptr<std::ostream> ostream, PLogFormatter formatter) :
    LogEndpointFormatted(formatter),
    m_ostream(ostream)
  {
    *m_ostream << boost::format("=== Logfile created by pid %1% at %2% ===")
                  % ::getpid() % boost::posix_time::microsec_clock::local_time()  << std::endl;
  }

}
