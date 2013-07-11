
#include "stream_socket.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <boost/format.hpp>
#include <errno.h>
#include <string.h>

#include "exceptions/exceptions.h"
StreamSocket::WriteResult StreamSocket::Write(uint8_t *p, uint64_t sz, uint64_t & bytesWritten)
{
  while (bytesWritten < sz) {
    int r = ::send(GetSocket(), p, sz, MSG_DONTWAIT);
    if (r == -1) {
      if (errno == EAGAIN) {
        return WriteResult::RES_OK;
      } if (errno == EINTR) {
        continue;
      } else {
        throw EXCEPTION_LIBCALL((boost::format("socket error: %i %s") % errno % ::strerror(errno)).str());
      }
    }

    if (r == 0) {
      return WriteResult::RES_EOF;
    }

    bytesWritten += r;
  }

  return WriteResult::RES_OK;
}



