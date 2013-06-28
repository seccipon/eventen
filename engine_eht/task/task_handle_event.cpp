#include "task_handle_event.h"

EventHandleRoutine::EventHandleRoutine(PEventHandler ehTask, PEvent event) :
  m_ehTask(ehTask),
  m_event(event)
{

}

void EventHandleRoutine::Run()
{
  m_ehTask->HandleEvent(m_event);
}
