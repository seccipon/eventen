#include "logendpoint_stderr.h"


void Log::LogEndpoint_stderr::DoWriteLogMessage(const Log::LogMessage &message)
{
  std::cerr << GetFormattedMessage(message) << std::endl;
}
