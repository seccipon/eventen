
#include "task.h"
#include "../eh/eventhandler.h"

#include "task_handle_event.h"
void Task::PostEvent(const PEvent &event)
{
  m_eh->HandleEvent(event);
}

void Task::PostEventAsync(const PEvent &event, PThreadPool tp)
{
  PEventHandleRoutine routine(new EventHandleRoutine(m_eh, event));
  tp->PostRunnable(routine);
}



