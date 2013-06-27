#include <iostream>


#include "engine_eht/task/taskfwd.h"
#include "engine_eht/event/eventfwd.h"
#include "engine_eht/eh/eventhandlerfwd.h"

#include "engine_eht/task/test/tasktest.h"
#include "engine_eht/eh/test/eventhandlertest.h"


#include "multithread/threadpool.h"

#include "network/serversocket.h"
#include "network/networkloop.h"
#include "engine_eht/eh/network/ehnetworkloop.h"
using namespace std;

int main()
{
  TaskTest taskTest(PEventHandler(new EventHandlerTest));
  taskTest.DoThing();

  ThreadPool tp;
  tp.Init(10);

  PEventHandler ehNetworkLoop(new EHNetworkLoop);

  PNetworkLoop networkLoop(new NetworkLoop(ehNetworkLoop, 1));

  PServerSocket pSock(new ServerSocket(ServerSocket::Init(33600)));
  pSock->SetNonblock(true);
  pSock->Listen(64);

  networkLoop->AddListenSocket(pSock);

  tp.PostRunnable(networkLoop);

  sleep(15);
  networkLoop->Interrupt();
  tp.Stop();
  tp.Join();


  return 0;
}

