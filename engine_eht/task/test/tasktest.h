#ifndef TASKTEST_H
#define TASKTEST_H


#include "../task.h"
#include "../../event/test/eventtest.h"


template <typename EventHandlerType>
class TaskTest : public Task<EventHandlerType>
{
public:
  typedef std::shared_ptr<EventHandlerType> PEventHandler;

  explicit TaskTest(const PEventHandler & eh) :
    Task<EventHandlerType>(eh)
  {}

  void DoThing() {
    EventTest tt;
    this->PostEvent(tt);
  }

};

#endif // TASKTEST_H
