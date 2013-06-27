
#include "socket.h"


#include <sys/socket.h>
#include <fcntl.h>

#include <assert.h>
void Socket::SetNonblock(bool v)
{
  int flags = ::fcntl(m_sockfd, F_GETFL, 0);
  if (v) {
    flags |= O_NONBLOCK;
  } else {
    flags &= ~O_NONBLOCK;
  }

  assert(!::fcntl(m_sockfd, F_SETFL, flags));
}


