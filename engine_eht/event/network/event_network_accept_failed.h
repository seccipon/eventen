#ifndef EVENT_NETWORK_ACCEPT_FAILED_H
#define EVENT_NETWORK_ACCEPT_FAILED_H
#include "engine_eht/event/event.h"
#include "network/server_socket.h"
#include "network/server_socket_loop.h"

class EventNetworkAcceptFailed : public IEvent
{
public:
  EVENT_POST_TO_HANDLER_DECL

  EventNetworkAcceptFailed(PServerSocketLoop loop, PServerSocket ssocket, int errn) :
    m_networkLoop(loop),
    m_serverSocket(ssocket),
    m_errno(errn)
  {}
  virtual ~EventNetworkAcceptFailed() {}


  const PServerSocket & GetServerSocket() const {
    return m_serverSocket;
  }

  const PServerSocketLoop & GetNetworkLoop() const {
    return m_networkLoop;
  }

  int GetErrno() const {
    return m_errno;
  }
private:
  PServerSocketLoop m_networkLoop;
  PServerSocket m_serverSocket;
  int m_errno;


};

#endif // EVENT_NETWORK_ACCEPT_FAILED_H
