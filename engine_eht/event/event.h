#ifndef EVENT_H
#define EVENT_H

#include <memory>

#include "../eh/eventhandlerfwd.h"
#include "../task/taskfwd.h"

class IEvent
{

public:
  virtual void PostToHandler(EventHandler & eventHandler) const = 0;
  virtual ~IEvent()
  {}
};



#define EVENT_POST_TO_HANDLER_DECL \
virtual void PostToHandler(EventHandler & eventHandler) const;

#define EVENT_POST_TO_HANDLER_IMPL(EventClassName)                     \
void EventClassName::PostToHandler(EventHandler & eventHandler) const  \
{                                                                      \
  eventHandler.HandleEvent(*this);                                     \
}

#endif // EVENT_H
