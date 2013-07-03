#ifndef TASK_H
#define TASK_H

#include "engine_eht/event/eventfwd.h"
#include "engine_eht/eh/eventhandlerfwd.h"
#include "multithread/threadpool.h"
class Task
{
public:
  Task(const PEventHandler & eh) :
    m_eh(eh)
  {}

  virtual ~Task()
  {}

protected:
  void PostEvent(const PEvent & event);
  void PostEventAsync(const PEvent & event, PThreadPool tp);

private:
  PEventHandler m_eh;
};

typedef std::shared_ptr<Task> PTask;
#endif // TASK_H
