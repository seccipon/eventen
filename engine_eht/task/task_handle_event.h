#ifndef TASK_HANDLE_EVENT_H
#define TASK_HANDLE_EVENT_H

#include "engine_eht/task/task.h"
#include "general/runnable.h"
#include "engine_eht/eh/eventhandler.h"
#include <functional>

class EventHandleRoutine : public IRunnable
{
public:
  EventHandleRoutine (PEventHandler ehTask, PEvent event);

  void Run();

private:
  PEventHandler m_ehTask;
  PEvent m_event;

};

typedef std::shared_ptr<EventHandleRoutine> PEventHandleRoutine;
#endif // TASK_HANDLE_EVENT_H
