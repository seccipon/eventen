#ifndef EVENTSTREAMSOCKETACCEPTED_H
#define EVENTSTREAMSOCKETACCEPTED_H
#include "../event.h"
#include "network/server_socket.h"
#include "../../../network/server_socket_loop.h"
class EventStreamSocketAccepted : public IEvent
{
public:
  EVENT_POST_TO_HANDLER_DECL

  EventStreamSocketAccepted(PServerSocketLoop networkLoop, int sockfd, PServerSocket serverSocket) :
    m_sockfd(sockfd),
    m_serverSocket(serverSocket),
    m_networkLoop(networkLoop)
  {}
  int GetSocket() const {
    return m_sockfd;
  }
  const PServerSocket & GetServerSocket() const {
    return m_serverSocket;
  }

  const PServerSocketLoop & GetNetworkLoop() const {
    return m_networkLoop;
  }

  virtual ~EventStreamSocketAccepted() {}
private:
  int m_sockfd;
  PServerSocket m_serverSocket;
  PServerSocketLoop m_networkLoop;

};

#endif // EVENTSTREAMSOCKETACCEPTED_H
