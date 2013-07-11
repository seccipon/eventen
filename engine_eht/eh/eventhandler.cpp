#include "eventhandler.h"
#include "engine_eht/event/event.h"
#include "network/events.h"
#include "engine_eht/event/test/eventtest.h"
#include <iostream>

#include "log/log.h"

#undef LOG_DEFINE_FILELOCAL_LOGGER
#undef LOG_LOGGER_TAG


#define LOG_FILELOCAL_LOGGER Log::GetEventLogger()
#define LOG_LOGGER_TAG "Events"

using namespace std;

void EventHandler::HandleEvent(const PEvent & event) {
  LOG_SET_LOGGER_FILELOCAL;

  LOG("Handling event ({%1%}, %2%) by event handler ({%3%}, %4%)",
      % &event % typeid(*event).name() % this % typeid(*this).name());
  event->PostToHandler(*this);
}

void EventHandler::UnexpectedEvent(const IEvent & event) {
  LOG_SET_LOGGER_FILELOCAL;

  LOG("Unexpected event ({%1%}, %2%) handled by event handler (%3%, %4%",
      % &event % typeid(event).name() % this % typeid(*this).name());
}

void EventHandler::HandleEvent(const EventTest & event) {
  UnexpectedEvent(event);
}

void EventHandler::HandleEvent(const EventStreamSocketAccepted & event) {
  UnexpectedEvent(event);
}

void EventHandler::HandleEvent(const EventSocketReadyToAccept &event)
{
  UnexpectedEvent(event);
}

void EventHandler::HandleEvent(const EventNetworkAcceptFailed &event)
{
  UnexpectedEvent(event);
}

void EventHandler::HandleEvent(const EventSocketWriteEOF &event)
{
  UnexpectedEvent(event);
}

void EventHandler::HandleEvent(const EventSocketWriteCompleted &event)
{
  UnexpectedEvent(event);
}

void EventHandler::HandleEvent(const EventSocketError &event)
{
  UnexpectedEvent(event);
}


