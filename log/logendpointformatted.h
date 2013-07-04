#ifndef LOGENDPOINTFORMATTED_H
#define LOGENDPOINTFORMATTED_H

#include "logendpoint.h"
#include "logformatter.h"
namespace Log
{
  class LogEndpointFormatted : public ILogEndpoint
  {
  public:
    LogEndpointFormatted(PLogFormatter formatter) :
      m_formatter(formatter)
    {  }

    std::string GetFormattedMessage(const LogMessage & message) const {
      return m_formatter->DoFormatMessage(message);
    }

    virtual ~LogEndpointFormatted()
    { }
  private:
    PLogFormatter m_formatter;
  };

}
#endif // LOGENDPOINTFORMATTED_H
