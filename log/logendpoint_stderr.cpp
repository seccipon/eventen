#include "logendpoint_stderr.h"


void Log::Logger_stderr::PushMessage(const PLogMessage &message)
{
  std::cerr << GetFormattedMessage(message) << std::endl;
}
