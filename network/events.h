#ifndef NETWORK_EVENTS_H
#define NETWORK_EVENTS_H

#include "engine_eht/event/event.h"
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


#endif // NETWORK_EVENTS_H
