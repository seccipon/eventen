#include "buffer.h"
#include <string.h>

Buffer::Buffer(uint8_t *m, uint64_t sz) :
  m_mem(new uint8_t[sz]),
  m_sz(sz)
{
  ::memcpy(m_mem.get(), m, sz);
}

Buffer::Buffer(boost::shared_array<uint8_t> m, uint64_t sz) :
  m_mem(m),
  m_sz(sz)
{

}

