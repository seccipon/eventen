#ifndef EVENTHANDLERTEST_H
#define EVENTHANDLERTEST_H


#include "../eventhandler.h"

class EventHandlerTest : public EventHandler
{
public:
  virtual void HandleEvent(const EventTest &event);
};

#endif // EVENTHANDLERTEST_H
