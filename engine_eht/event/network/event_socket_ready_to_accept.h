#ifndef EVENT_SOCKET_READY_TO_ACCEPT_H
#define EVENT_SOCKET_READY_TO_ACCEPT_H


#include "engine_eht/event/event.h"
#include "network/server_socket_loop.h"

class EventSocketReadyToAccept : public IEvent
{
public:
  EventSocketReadyToAccept(PServerSocketLoop networkLoop, PServerSocket serverSocket) :
    m_networkLoop(networkLoop),
    m_serverSocket(serverSocket)
  {  }

  const PServerSocketLoop & GetNetworkLoop() const {
    return m_networkLoop;
  }

  const PServerSocket & GetServerSocket() const {
    return m_serverSocket;
  }

  EVENT_POST_TO_HANDLER_DECL
private:
  PServerSocketLoop m_networkLoop;
  PServerSocket m_serverSocket;
};

#endif // EVENT_SOCKET_READY_TO_ACCEPT_H
