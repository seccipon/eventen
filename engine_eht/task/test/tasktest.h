#ifndef TASKTEST_H
#define TASKTEST_H


#include "../task.h"

class TaskTest : public Task
{
public:
  TaskTest(const PEventHandler & eh) :
    Task(eh)
  {}

  void DoThing();

};

#endif // TASKTEST_H
