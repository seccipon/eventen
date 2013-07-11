#ifndef LOG_H
#define LOG_H
#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>


#define LOG_LEVEL_LOGICERROR 0


#define LOG_LEVEL_FATAL     0
#define LOG_LEVEL_ERROR     1
#define LOG_LEVEL_DEFAULT   2
#define LOG_LEVEL_TRACK     5
#define LOG_LEVEL_DEBUG     5

#define LOG_CURRENT_LOGGER_VAR_NAME ____CURRENTLOGGER12345678______

#define LOG_LOGGER_TAG ""

/////////////////////////////////////////////////////////////// obsolete

//Set function-local logger
#define LOG_SET_LOGGER(logger) const Log::PLogger & LOG_CURRENT_LOGGER_VAR_NAME(logger)

//Set function-local logger to global default logger
#define LOG_SET_LOGGER_DEFAULT LOG_SET_LOGGER(Log::GetDefaultLogger())

//Set function-local logger to file-local logger
#define LOG_SET_LOGGER_FILELOCAL LOG_SET_LOGGER(LOG_FILELOCAL_LOGGER)

//LogMessage Builders
#define LOG_MSG_LEVEL_TAG(level, tag, formatstr,...) \
(Log::PLogMessage(new Log::LogMessage((level), __FILE__, __LINE__, (boost::format(std::string(formatstr))  __VA_ARGS__).str(), boost::posix_time::microsec_clock::local_time() , (tag))))

#define LOG_MSG(formatstr,...) \
  LOG_MSG_LEVEL_TAG(LOG_LEVEL_DEFAULT, "", (formatstr), __VA_ARGS__)

#define LOG_MSG_TAG(tag,formatstr,...) \
  LOG_MSG_LEVEL_TAG(LOG_LEVEL_DEFAULT, (tag), (formatstr), __VA_ARGS__)

#define LOG_MSG_LEV(level,formatstr,...) \
  LOG_MSG_LEVEL_TAG((level), "", (formatstr), __VA_ARGS__)


//Main log functions (build LogMessage  and push it to default logger)
#define LOG_LEVEL_TAG(level, tag, formatstr,...) \
{ LOG_CURRENT_LOGGER_VAR_NAME->PushMessage(LOG_MSG_LEVEL_TAG((level), (tag), (formatstr), __VA_ARGS__)); }

#define LOG(formatstr,...) \
  LOG_LEVEL_TAG(LOG_LEVEL_DEFAULT, "", (formatstr), __VA_ARGS__)

#define LOG_TAG(tag,formatstr,...) \
  LOG_LEVEL_TAG(LOG_LEVEL_DEFAULT, (tag), (formatstr), __VA_ARGS__)

#define LOG_LEV(level,formatstr,...) \
  LOG_LEVEL_TAG((level), "", (formatstr), __VA_ARGS__)

#define LOG_DEBUG_TAG(tag, formatstr,...) \
  LOG_LEVEL_TAG(LOG_LEVEL_DEBUG, (tag), (formatstr), __VA_ARGS__)

#define LOG_DEBUG(formatstr,...) \
  LOG_LEVEL_TAG(LOG_LEVEL_DEBUG, "", (formatstr), __VA_ARGS__)



//TRACK functions
//build track LogMessage
#define TRACK_MSG(x) \
  LOG_MSG_LEV(LOG_LEVEL_TRACK, "%1% = %2%", % std::string(#x) % x)

//TRACK: build and push a track message to default logger
#define TRACK(x) \
{    LOG_CURRENT_LOGGER_VAR_NAME->PushMessage(TRACK_MSG(x));   }


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
