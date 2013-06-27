#ifndef TASK_H
#define TASK_H

#include "../event/eventfwd.h"
#include "../eh/eventhandlerfwd.h"

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

private:
  PEventHandler m_eh;
};

typedef std::shared_ptr<Task> PTask;
#endif // TASK_H
