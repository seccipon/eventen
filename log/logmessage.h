#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>
#include <stdint-gcc.h>
#include <atomic>
namespace Log
{
  class LogMessage
  {
  public:
    LogMessage(int level, const std::string & file, int line, const std::string & message,
               const boost::posix_time::ptime & time, const std::string & tag = "");

    int Level() const {
      return m_level;
    }

    int Id() const {
      return m_messageId;
    }

    const std::string & File() const {
      return m_file;
    }

    const std::string & Tag() const {
      return m_tag;
    }

    int Line() const {
      return m_line;
    }

    const std::string & Message() const {
      return m_message;
    }

    const boost::posix_time::ptime Time() const {
      return m_time;
    }

    void SetText(const std::string & text);

  private:

    boost::posix_time::ptime m_time;
    int m_level;
    std::string m_file;
    int m_line;
    std::string m_message;
    std::string m_tag;
    int m_messageId;
    static std::atomic_int lastLogMessageId;
  };

  typedef std::shared_ptr<LogMessage> PLogMessage;
}
#endif // LOGMESSAGE_H
