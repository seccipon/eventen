#ifndef RUNNABLE_H
#define RUNNABLE_H


#include <memory>


class IRunnable
{
public:
  virtual void Run() = 0;
};

typedef std::shared_ptr<IRunnable> PRunnable;


#endif // RUNNABLE_H
