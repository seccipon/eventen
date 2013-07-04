#include "logendpoint_stderr.h"


void Log::LogEndpoint_stderr::DoWriteLogMessage(const Log::LogMessage &message)
{
  std::cerr << m_formatter->DoFormatMessage(message) << std::endl;
}
