#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event/eventfwd.h"

#include <memory>

class EventHandler
{
public:
  //Entry point for all events
  void HandleEvent(const PEvent & event);

  virtual void HandleEvent(const EventTest & event);
  virtual void HandleEvent(const EventStreamSocketAccepted & event);
  virtual void HandleEvent(const EventSocketReadyToAccept & event);
  virtual void HandleEvent(const EventNetworkAcceptFailed & event);
  virtual void HandleEvent(const EventSocketWriteEOF & event);
  virtual void HandleEvent(const EventSocketWriteCompleted & event);
  virtual void HandleEvent(const EventSocketError & event);

private:

  //Unexpected event handler. Can be overloaded.
  virtual void UnexpectedEvent(const IEvent &event);
};


#endif // EVENTHANDLER_H
