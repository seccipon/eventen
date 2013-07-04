#ifndef LOG_H
#define LOG_H
#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>


#define LOG_LEVEL_LOGICERROR 0
#define LOG_LEVEL_DEFAULT 2
#define LOG_LEVEL_TRACK 5

#define LOG_CURRENT_LOGGER_VAR_NAME ____CURRENTLOGGER12345678______

#define LOG_LOGGER_TAG ""

#define LOG_BASE(logger,level,formatstr,...) \
{                                            \
  Log::LogMessage lm((level), __FILE__, __LINE__, (boost::format(std::string(formatstr))  __VA_ARGS__).str(), boost::posix_time::microsec_clock::local_time() , LOG_LOGGER_TAG);  \
  logger->PushMessage(lm); \
}

#define LOG_DEF(level,formatstr,...) LOG_BASE(LOG_CURRENT_LOGGER_VAR_NAME, level, formatstr,  __VA_ARGS__)

#define LOG(formatstr,...) LOG_DEF(LOG_LEVEL_DEFAULT,formatstr,  __VA_ARGS__)
#define TRACK(val) \
  LOG_DEF(LOG_LEVEL_TRACK, "%1% == %2%", % std::string(#val) % val)

#define LOG_SET_LOGGER(logger) const Log::PLogger & LOG_CURRENT_LOGGER_VAR_NAME(logger)

#define LOG_SET_LOGGER_DEFAULT LOG_SET_LOGGER(Log::GetDefaultLogger())
#define LOG_SET_LOGGER_FILELOCAL LOG_SET_LOGGER(LOG_FILELOCAL_LOGGER)

#include "loggersimple.h"
namespace Log
{
  void InitLoggers();
  void DestroyLoggers();

  void InitDefaultLogger();
  PLogger GetDefaultLogger();

  void InitNetworkLogger();
  PLogger GetNetworkLogger();

  void InitLogicErrorLogger();
  PLogger GetLogicErrorLogger();

  void InitThreadLogger();
  PLogger GetThreadLogger();

  void InitEventLogger();
  PLogger GetEventLogger();

  PLogger CreateSimpleFileLogger(const std::string & fileName);
}
#endif // LOG_H
