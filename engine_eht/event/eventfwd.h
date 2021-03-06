#ifndef EVENTFWD_H
#define EVENTFWD_H
#include <memory>


class IEvent;
typedef std::shared_ptr<IEvent> PEvent;


class EventTest;
class EventStreamSocketAccepted;
class EventSocketReadyToAccept;
class EventNetworkAcceptFailed;
class EventSocketWriteEOF;
class EventSocketWriteCompleted;
class EventSocketError;

#endif // EVENTFWD_H
