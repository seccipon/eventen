#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "socket.h"

#include <stdint-gcc.h>

#include <memory>
class ServerSocket : public Socket
{
public:
  explicit ServerSocket(int sockfd, uint16_t port) :
    Socket(sockfd),
    m_port(port)
  {}

  //performs socket() and bind()
  static ServerSocket Init(uint16_t port);

  void Listen(int backlog);

  uint16_t GetPort() const {
    return m_port;
  }

  bool Accept(int & sockfd, int & errn);

private:
  uint16_t m_port;
};

typedef std::shared_ptr<ServerSocket> PServerSocket;


#endif // SERVERSOCKET_H
