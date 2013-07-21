#include <iostream>


#include "engine_eht/task/taskfwd.h"
#include "engine_eht/event/eventfwd.h"
#include "engine_eht/eh/eventhandlerfwd.h"

#include "engine_eht/task/test/tasktest.h"
#include "engine_eht/eh/test/eventhandlertest.h"


#include "multithread/threadpool.h"

#include "network/server_socket.h"
#include "network/server_socket_loop.h"
#include "network/ehsocketloop.h"
#include "log/log.h"
#include "log/loggersimple.h"
#include "log/logendpoint_ostream.h"

#include "log/logger_cumulative.h"
#include "log/logfilternull.h"
#include "log/logfilter.h"
#include "util/assertion.h"
using namespace std;

PThreadPool gThreadPool;


int main()
{
  Log::InitLoggers();

  LOG_SET_LOGGER_DEFAULT;

  Log::LoggerCumulative lcm(Log::GetDefaultLogger(), LOG_MSG("Main function loop"));
  lcm.PushMessage(LOG_MSG("zhopa pizda %1% %2% %3% ", % 234 % "asdfasdf" % 231));
  lcm.Success(LOG_MSG("alright"));

  gThreadPool.reset(new ThreadPool);
  gThreadPool->Init(10);

  int a = 100;
  TRACK(a);

  LOG("sotona: %1% %2% %3%", % "sobaka" % 123 % boost::posix_time::microsec_clock::local_time());


  TaskTest<EventHandlerTest> taskTest(std::shared_ptr<EventHandlerTest>(new EventHandlerTest));
  taskTest.DoThing();

  std::shared_ptr<EHNetworkLoop> ehNetworkLoop(new EHNetworkLoop);

  std::shared_ptr<LoopSocketListen<EHNetworkLoop> > networkLoop(new LoopSocketListen<EHNetworkLoop>(ehNetworkLoop, 1));

  PServerSocket pSock(new ServerSocket(ServerSocket::Init(33600)));
  pSock->SetNonblock(true);
  pSock->Listen(64);

  networkLoop->AddListenSocket(pSock);

  gThreadPool->PostRunnable(networkLoop);

  sleep(1);
  networkLoop->Interrupt();
  sleep(1);
  networkLoop->Interrupt();
  sleep(1);
  networkLoop->Interrupt();
  sleep(1);
  networkLoop->Interrupt();
  sleep(1);
  networkLoop->Interrupt();
  sleep(1);
  networkLoop->Interrupt();
  sleep(1);
  networkLoop->Interrupt();

  networkLoop->Break();


  Log::LoggerCumulative lcm1(Log::GetDefaultLogger(), LOG_MSG("ANALNIY FIMOZ SRANIY PIDORAS"));
  lcm1.PushMessage(LOG_MSG("zhopa pizda %1% %2% %3% ", % 234 % "asdfasdf" % 231));
  lcm1.PushMessage(LOG_MSG("zhopa pizda %1% %2% %3% ", % 234 % "asdasdfasdffasdf" % 231));
  lcm1.PushMessage(LOG_MSG("zhopa pizda %1% %2% %3% ", % 4321 % "asdf" % 2341));
  lcm1.PushMessage(LOG_MSG("zhopa pizda %1% %2% %3% ", % "2qwe3qwer4" % "asdfasdfqwerasdf" % 123));
  lcm1.Fail(LOG_MSG("i've fucked"));


  gThreadPool->Stop();
  gThreadPool->Join();
  Log::DestroyLoggers();
  return 0;
}

