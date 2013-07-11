#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class ExceptionContext
{
public:
  static std::string MakeExceptionContextStr(const std::string & file, int line, const std::string & excType, const std::string & excText);
};

class ExceptionLibcall : public std::runtime_error
{
public:
  ExceptionLibcall(const std::string & file, int line, const std::string & whatHappened);
};

#define EXCEPTION_LIBCALL(str) \
  ExceptionLibcall(__FILE__, __LINE__, (str))


class ExceptionAssertFailed : public std::logic_error
{
public:
  ExceptionAssertFailed(const std::string & file, int line, const std::string & assertionStr);
};

#define EXCEPTION_ASSERT_FAILED(str) \
  ExceptionAssertFailed(__FILE__, __LINE__, (str))



#endif // EXCEPTIONS_H
