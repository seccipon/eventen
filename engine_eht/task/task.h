#ifndef TASK_H
#define TASK_H


#include <memory>

#include "task_handle_event.h"
#include "multithread/threadpool.h"



template <typename EventHandlerType>
class Task
{
public:
  typedef std::shared_ptr<EventHandlerType> PEventHandler;

  Task(const PEventHandler & eh) :
    m_eh(eh)
  {}

  virtual ~Task()
  {}

protected:
  template <typename EventType> void PostEvent(const EventType & event) {
    m_eh->HandleEvent(event);
  }

  template <typename EventType> void PostEventAsync(const EventType & event, PThreadPool tp) {
    typedef std::shared_ptr<EventType> PEvent;
    PEvent pEv ( new EventType(event) );
    PRunnable routine( new EventHandleRoutine<EventHandlerType, EventType>(m_eh, event) );
    tp->PostRunnable(routine);
  }

private:
    PEventHandler m_eh;
};

#endif // TASK_H
