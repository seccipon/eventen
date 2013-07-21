#ifndef EHNETWORKLOOP_H
#define EHNETWORKLOOP_H

#include "engine_eht/eh/eventhandler.h"
#include "engine_eht/event/eventfwd.h"
class EHNetworkLoop
{
public:
  void HandleEvent(const EventStreamSocketAccepted &event);
  void HandleEvent(const EventSocketReadyToAccept &event);
};

#endif // EHNETWORKLOOP_H
