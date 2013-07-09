#ifndef LOGENDPOINT_OSTREAM_H
#define LOGENDPOINT_OSTREAM_H

#include "logendpointformatted.h"
#include "logformatter.h"

namespace Log {
  class Logger_ostream : public LoggerFormatted
  {
  public:
    Logger_ostream(std::shared_ptr<std::ostream> ostream, PLogFormatter formatter);
    Logger_ostream(std::ostream & ostream, PLogFormatter formatter);

    virtual void PushMessage(const PLogMessage & message);

    virtual ~Logger_ostream() {   }
    std::ostream & GetOstream() {
      return m_ostream;
    }

  private:
      std::shared_ptr<std::ostream> m_ostreamptr;
      std::ostream & m_ostream;
  };
}
#endif // LOGENDPOINT_OSTREAM_H
