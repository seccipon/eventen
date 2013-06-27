#ifndef SOCKET_H
#define SOCKET_H

#include <boost/noncopyable.hpp>
class Socket
{
public:
  explicit Socket(int sockfd) :
    m_sockfd(sockfd)
  {}

  int GetSocket() const {
    return m_sockfd;
  }

  void SetNonblock(bool v);

private:
  const int m_sockfd;
};

#endif // SOCKET_H
