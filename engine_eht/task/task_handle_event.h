#ifndef TASK_HANDLE_EVENT_H
#define TASK_HANDLE_EVENT_H

//#include "engine_eht/task/task.h"
#include "general/runnable.h"
//#include "engine_eht/eh/eventhandler.h"
#include <functional>


template <typename EventHandlerType, typename EventType>
class EventHandleRoutine : public IRunnable
{
public:
  typedef std::shared_ptr<EventHandlerType> PEventHandler;
  typedef std::shared_ptr<EventType> PEvent;
  typedef std::shared_ptr<EventHandleRoutine> PEventHandleRoutine;

  EventHandleRoutine (PEventHandler ehTask, PEvent event)  :
    m_ehTask(ehTask),
    m_event(event)
  {   }

  void Run() {
    m_ehTask->HandleEvent(*m_event);
  }

private:
  PEventHandler m_ehTask;
  PEvent m_event;
};


#endif // TASK_HANDLE_EVENT_H
