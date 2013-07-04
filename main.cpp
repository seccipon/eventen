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

#include "log/logfilternull.h"
using namespace std;

PThreadPool gThreadPool;


int main()
{
  Log::InitDefaultLogger();
  Log::InitNetworkLogger();

//  LOG_SET_LOGGER(Log::CreateSimpleFileLogger("zhopa!!!"));
  LOG_SET_LOGGER_DEFAULT;

  int a = 100;
  TRACK(a);

  LOG("sotona: %1% %2% %3%", % "sobaka" % 123 % boost::posix_time::microsec_clock::local_time());

  gThreadPool.reset(new ThreadPool);
  gThreadPool->Init(10);

  TaskTest taskTest(PEventHandler(new EventHandlerTest));
  taskTest.DoThing();





  PEventHandler ehNetworkLoop(new EHNetworkLoop);


  PServerSocketLoop networkLoop(new LoopSocketListen(ehNetworkLoop, 1));

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


  gThreadPool->Stop();
  gThreadPool->Join();

  return 0;
}

