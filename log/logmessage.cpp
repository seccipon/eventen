#include "logmessage.h"

namespace Log
{
  LogMessage::LogMessage(int level, const std::string &file, int line, const std::string &message,
                              const boost::posix_time::ptime & time, const std::string & tag ) :
    m_time(time),
    m_level(level),
    m_file(file),
    m_line(line),
    m_message(message),
    m_tag(tag),
    m_messageId(lastLogMessageId++)
  {

  }


  std::atomic_int LogMessage::lastLogMessageId;
}
