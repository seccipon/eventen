#include "server_socket.h"


#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

ServerSocket ServerSocket::Init(uint16_t port)
{
  int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
  assert(sockfd > 0);

  int r = 0;
  int v = 1;
  r = ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(v));
  r = ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &v, sizeof(v));

  sockaddr_in sa;
  ::memset(&sa, 0, sizeof(sa));
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);

  r = ::bind(sockfd, reinterpret_cast<sockaddr*>(&sa), sizeof(sa));

  assert(r != -1);

  return ServerSocket(sockfd);
}

void ServerSocket::Listen(int backlog)
{
  ::listen(GetSocket(), backlog);
}

bool ServerSocket::Accept(int &sockfd)
{
  int r = ::accept(GetSocket(), NULL, NULL);
  if (r > 0) {
    sockfd = r;
    return true;
  }
  perror("accept()");

  return false;
}

