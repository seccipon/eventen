
#include "logendpoint_ostream.h"

namespace Log
{
  void Logger_ostream::PushMessage(const PLogMessage &message)
  {
    GetOstream() << GetFormattedMessage(message) << std::endl;
  }


  Logger_ostream::Logger_ostream(std::shared_ptr<std::ostream> ostream, PLogFormatter formatter) :
    LoggerFormatted(formatter),
    m_ostreamptr(ostream),
    m_ostream(*m_ostreamptr)
  {   }

  Logger_ostream::Logger_ostream(std::ostream &ostream, PLogFormatter formatter) :
    LoggerFormatted(formatter),
    m_ostream(ostream)
  {

  }
}
