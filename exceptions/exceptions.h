#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class ExceptionLibcall : public std::runtime_error
{
public:
  ExceptionLibcall(const std::string & file, int line, const std::string & whatHappened);

  virtual const char* what();

private:
 std::string m_what;
 std::string m_file;
 int line;
};



class ExceptionAssertFailed : public std::logic_error
{

};

#endif // EXCEPTIONS_H
