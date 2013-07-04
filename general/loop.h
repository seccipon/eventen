#ifndef LOOP_H
#define LOOP_H

#include "runnable.h"
#include <memory>
class Loop : public IRunnable
{

protected:
  virtual bool IsBreak();
public:
  virtual void Run();
  virtual void OneLoop() = 0;
  virtual void Break();
  virtual void Init() = 0;
  virtual void Destroy() = 0;
  virtual ~Loop()
  {}

  Loop() :
    m_flBreak(false)
  {  }

private:
  bool m_flBreak;

  virtual void DoBreak() = 0;

};

#endif // LOOP_H
