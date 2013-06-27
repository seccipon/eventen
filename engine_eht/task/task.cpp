
#include "task.h"
#include "../eh/eventhandler.h"
void Task::PostEvent(const PEvent &event)
{
  m_eh->HandleEvent(event);
}



