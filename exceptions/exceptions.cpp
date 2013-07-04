#include "exceptions.h"
#include <boost/format.hpp>



std::string ExceptionContext::MakeExceptionContextStr(const std::string & file, int line, const std::string & excType, const std::string & excText)
{
  return (boost::format("EXCEPTION %s thrown at %s : %u >> %s") % excType % file % line % excText).str();
}
////

ExceptionLibcall::ExceptionLibcall(const std::string &file, int line, const std::string &whatHappened) :
  std::runtime_error(ExceptionContext::MakeExceptionContextStr(file, line, "libcall failed", whatHappened))
{

}

ExceptionAssertFailed::ExceptionAssertFailed(const std::string &file, int line, const std::string &assertionStr) :
  std::logic_error(ExceptionContext::MakeExceptionContextStr(file, line, "assertion failed", std::string("(") + assertionStr + std::string(")")))
{

}

