#ifndef LOGGER_H
#define LOGGER_H


#include "logmessage.h"
#include <memory>
namespace Log
{
  class ILogger
  {
  public:
    virtual void PushMessage(const PLogMessage & message) = 0;
    virtual ~ILogger(){ }
  };
  typedef std::shared_ptr<ILogger> PLogger;
}

#endif // LOGGER_H
