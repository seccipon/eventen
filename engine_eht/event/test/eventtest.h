#ifndef EVENTTEST_H
#define EVENTTEST_H


#include "../event.h"

class EventTest : public IEvent
{
public:
  EVENT_POST_TO_HANDLER_DECL
};

#endif // EVENTTEST_H
