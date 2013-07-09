#ifndef LOGENDPOINTFORMATTED_H
#define LOGENDPOINTFORMATTED_H

#include "logger.h"
#include "logformatter.h"
namespace Log
{
  class LoggerFormatted : public ILogger
  {
  public:
    LoggerFormatted(PLogFormatter formatter) :
      m_formatter(formatter)
    {  }

    std::string GetFormattedMessage(const PLogMessage & message) const {
      return m_formatter->DoFormatMessage(message);
    }

    virtual ~LoggerFormatted()
    { }
  private:
    PLogFormatter m_formatter;
  };

}
#endif // LOGENDPOINTFORMATTED_H
