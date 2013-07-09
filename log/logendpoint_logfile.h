#ifndef LOGENDPOINT_LOGFILE_H
#define LOGENDPOINT_LOGFILE_H


#include "logformatter.h"
#include "logendpoint_ostream.h"
namespace Log
{
  class Logger_logfile : public Logger_ostream
  {
  public:
    Logger_logfile(std::shared_ptr<std::ostream> ostream, PLogFormatter formatter);

    virtual ~Logger_logfile();
  };
}
#endif // LOGENDPOINT_LOGFILE_H
