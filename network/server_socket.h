#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "socket.h"

#include <stdint-gcc.h>

#include <memory>
class ServerSocket : public Socket
{
public:
  explicit ServerSocket(int sockfd) :
    Socket(sockfd)
  {}

  //performs socket() and bind()
  static ServerSocket Init(uint16_t port);

  void Listen(int backlog);

  bool Accept(int & sockfd, int & errn);
};

typedef std::shared_ptr<ServerSocket> PServerSocket;


#endif // SERVERSOCKET_H
