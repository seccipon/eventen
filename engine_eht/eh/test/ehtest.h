#ifndef EHTEST_H
#define EHTEST_H


#include "eventhandler.h"
class EHTest : public EventHandler
{
public:
  virtual void HandleEvent(const EventTest &event);
};

#endif // EHTEST_H
