#ifndef BUFFER_H
#define BUFFER_H

#include <boost/shared_array.hpp>
#include <stdint-gcc.h>

class Buffer
{
public:
  Buffer(uint8_t * m, uint64_t sz);
  Buffer(boost::shared_array<uint8_t> m, uint64_t sz);

  uint8_t * GetBuffer() const {
    return m_mem.get();
  }

  uint64_t GetSz() const {
    return m_sz;
  }
private:
  boost::shared_array<uint8_t> m_mem;
  uint64_t m_sz;
};

#endif // BUFFER_H
