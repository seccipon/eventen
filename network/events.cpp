#include "events.h"
#include "engine_eht/eh/eventhandler.h"

EVENT_POST_TO_HANDLER_IMPL(EventNetworkAcceptFailed)

EVENT_POST_TO_HANDLER_IMPL(EventSocketReadyToAccept)

EVENT_POST_TO_HANDLER_IMPL(EventStreamSocketAccepted)

EVENT_POST_TO_HANDLER_IMPL(EventSocketWriteEOF)

EVENT_POST_TO_HANDLER_IMPL(EventSocketWriteCompleted)

EVENT_POST_TO_HANDLER_IMPL(EventSocketError)
