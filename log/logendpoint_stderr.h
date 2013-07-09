#ifndef LOGENDPOINT_STDERR_H
#define LOGENDPOINT_STDERR_H

#include "logendpoint_ostream.h"
#include "logformatter.h"
namespace Log
{
  class Logger_stderr : public Logger_ostream
  {
  public:
    Logger_stderr(PLogFormatter formatter) :
      Logger_ostream(std::cerr, formatter)
    {  }

    virtual void PushMessage(const PLogMessage & message);
  private:
  };
}
#endif // LOGENDPOINT_STDERR_H
