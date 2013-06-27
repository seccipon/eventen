#ifndef LOOP_H
#define LOOP_H

#include "runnable.h"
#include <memory>
class Loop : public IRunnable
{

protected:
  virtual bool IsInterrupted() = 0;
public:
  virtual void Run();
  virtual void OneLoop() = 0;
  virtual void Interrupt() = 0;
  virtual void Init() = 0;
  virtual void Destroy() = 0;

  virtual ~Loop()
  {}
};

#endif // LOOP_H
