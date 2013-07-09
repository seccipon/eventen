
#include "logger_cumulative.h"

#include "logendpoint_ostream.h"
#include "logformatterdefault.h"
#include "util/assertion.h"
#include <boost/bind.hpp>
namespace Log
{

  LoggerCumulative::LoggerCumulative(PLogger endpoint,
                                     const PLogMessage &initialMessage) :
    m_success(false),
    m_initialMessage(initialMessage),
    m_endpoint(endpoint),
    m_finalized(false)
  {

  }

  void LoggerCumulative::PushMessage(const PLogMessage &message)
  {
    m_logMessages.push_back(message);
  }

  void LoggerCumulative::Success(const PLogMessage &message)
  {
    m_finalMessage = message;
    m_success = true;
    Commit();
  }

  void LoggerCumulative::Fail(const PLogMessage &message)
  {
    m_finalMessage = message;
    m_success = false;
    Commit();
  }

  LoggerCumulative::~LoggerCumulative()
  {
    ASSERT(m_finalized);
  }

  void LoggerCumulative::Commit()
  {
    PLogMessage squashedMsg (SquashMessages());
    m_endpoint->PushMessage(squashedMsg);
    m_finalized = true;
  }

  PLogMessage LoggerCumulative::SquashMessages()
  {
    PLogMessage ret(new LogMessage(m_initialMessage->Level(), m_initialMessage->File(), m_initialMessage->Line(),
                                   "", m_initialMessage->Time(), m_initialMessage->Tag()));


    std::stringstream resText;
    LoggerFormatterCumulative formatter;

    resText << m_initialMessage->Message() << std::endl;



    for (auto & x : m_logMessages) {
      resText << formatter.DoFormatMessage(x) << std::endl;
    }

    resText << std::string(m_success ? "SUCCESS ": "FAIL").append(formatter.DoFormatMessage(m_finalMessage));

    ret->SetText(resText.str());
    return ret;
  }

  std::string LoggerFormatterCumulative::DoFormatMessage(const PLogMessage &message)
  {
    std::stringstream ss;
    ss << (boost::format(std::string("\t %1% { %2%: %3% } >> %4%"))
           % message->Time() % message->File() % message->Line()) % message->Message();
    return ss.str();

  }

}

