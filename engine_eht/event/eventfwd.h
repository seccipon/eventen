#ifndef EVENTFWD_H
#define EVENTFWD_H
#include <memory>


class IEvent;
typedef std::shared_ptr<IEvent> PEvent;


class EventTest;
class EventStreamSocketAccepted;
class EventSocketReadyToAccept;


#endif // EVENTFWD_H
