#ifndef LOGENDPOINT_OSTREAM_H
#define LOGENDPOINT_OSTREAM_H

#include "logendpointformatted.h"
#include "logformatter.h"

namespace Log {
  class LogEndpoint_ostream : public LogEndpointFormatted
  {
  public:
    LogEndpoint_ostream(std::shared_ptr<std::ostream> ostream, PLogFormatter formatter);
    void DoWriteLogMessage(const LogMessage &message);

    virtual ~LogEndpoint_ostream();
  private:
      std::shared_ptr<std::ostream> m_ostream;
  };
}
#endif // LOGENDPOINT_OSTREAM_H
