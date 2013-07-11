#ifndef STREAM_SOCKET_H
#define STREAM_SOCKET_H

#include "socket.h"
#include <memory>
#include <stdint-gcc.h>
class StreamSocket : public Socket
{
public:

  enum class WriteResult
  {
    RES_EOF,
    RES_OK,
    RES_SOCKET_ERROR
  };

  StreamSocket(int sock);

  WriteResult Write(uint8_t * p, uint64_t sz, uint64_t & bytesWritten);

};

typedef std::shared_ptr<StreamSocket> PStreamSocket;
#endif // STREAM_SOCKET_H
