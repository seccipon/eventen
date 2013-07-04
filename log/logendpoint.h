#ifndef LOGENDPOINT_H
#define LOGENDPOINT_H


#include "logmessage.h"
#include <memory>
namespace Log
{
  class ILogEndpoint
  {
  public:
    virtual void DoWriteLogMessage(const LogMessage & message) = 0;
  };

  typedef std::shared_ptr<ILogEndpoint> PLogEndpoint;
}
#endif // LOGENDPOINT_H
