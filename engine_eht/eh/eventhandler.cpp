#include "eventhandler.h"
#include "../event/event.h"
#include "../event/network/eventstreamsocketaccepted.h"
#include "engine_eht/event/network/event_socket_ready_to_accept.h"
#include "../event/test/eventtest.h"

#include <iostream>
using namespace std;

void EventHandler::HandleEvent(const PEvent & event) {
  event->PostToHandler(*this);
}


void EventHandler::UnexpectedEvent(const IEvent *event) {
  cout << "Unexpected Event!" << typeid(*event).name() << endl;
}


void EventHandler::HandleEvent(const EventTest & event) {
  UnexpectedEvent(&event);
}

void EventHandler::HandleEvent(const EventStreamSocketAccepted & event) {
  UnexpectedEvent(&event);
}

void EventHandler::HandleEvent(const EventSocketReadyToAccept &event)
{
  UnexpectedEvent(&event);
}

