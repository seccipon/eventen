#include "loggerthreaded.h"

Log::LoggerThreaded::LoggerThreaded(Log::PLogger endpoint) :
  m_endpoint(endpoint)
{

}

void Log::LoggerThreaded::PushMessage(const PLogMessage &message)
{
  m_queue.Put(message);
}

void Log::LoggerThreaded::OneLoop()
{
  PLogMessage lm;
  while(!m_queue.GetBlock(lm));

  if (lm) {
      m_endpoint->PushMessage(lm);
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
