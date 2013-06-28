#ifndef PIPEINTERRUPTOR_H
#define PIPEINTERRUPTOR_H

#include <unistd.h>
#include <assert.h>
#include <fcntl.h>


class PipeInterruptor
{
public:
  PipeInterruptor();
  ~PipeInterruptor();

  int GetPipeReadFd();
  void TouchByWrite1Byte();

  void FlushRead();
private:
  int m_pipe[2];
};

#endif // PIPEINTERRUPTOR_H
