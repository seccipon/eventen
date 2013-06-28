#include "pipeinterruptor.h"

PipeInterruptor::PipeInterruptor()
{
  assert(::pipe2(m_pipe, O_NONBLOCK) != -1);
}

PipeInterruptor::~PipeInterruptor()
{
  close(m_pipe[0]);
  close(m_pipe[1]);
}

int PipeInterruptor::GetPipeReadFd()
{
  return m_pipe[0];
}

void PipeInterruptor::TouchByWrite1Byte()
{
  char t = 0;
  while(write(m_pipe[1], &t, sizeof(t)) < 1);
}

void PipeInterruptor::FlushRead()
{
  char buf[1024];
  while(read(m_pipe[0], buf, 1024)> 0);
}
