#include "exceptions.h"
#include <boost/format.hpp>


ExceptionLibcall::ExceptionLibcall(const std::string &file, int line, const std::string &whatHappened) :
  m_file(file),
  m_line(line)
{

}

const char *ExceptionLibcall::what()
{
  std::string ret = boost::format("EXCEPTION LIBCALL %s : %u >> ") % m_file % m_line % m_what;
}
