#include "loggerthreaded.h"

Log::LoggerThreaded::LoggerThreaded(Log::PLogFilter filter, Log::PLogEndpoint endpoint) :
  m_filter(filter),
  m_endpoint(endpoint)
{

}

void Log::LoggerThreaded::PushMessage(const Log::LogMessage &message)
{
  PLogMessage lm(new Log::LogMessage(message));
  m_queue.Put(lm);
}

void Log::LoggerThreaded::OneLoop()
{
  PLogMessage lm;
  while(!m_queue.GetBlock(lm));

  if (lm) {
    if (m_filter->DoForwardMessage(*lm)) {
      m_endpoint->DoWriteLogMessage(*lm);
    }
  }
}

void Log::LoggerThreaded::Init()
{

}

void Log::LoggerThreaded::Destroy()
{
}


void Log::LoggerThreaded::DoBreak()
{
  m_queue.Put(PLogMessage());
}
