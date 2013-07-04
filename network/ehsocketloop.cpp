
#include "ehsocketloop.h"
#include <iostream>
#include "events.h"

using namespace std;

void EHNetworkLoop::HandleEvent(const EventStreamSocketAccepted &event)
{
  cout << "Event happened : socket accepted!" << event.GetSocket() << endl;
}

void EHNetworkLoop::HandleEvent(const EventSocketReadyToAccept &event)
{
  cout << "Ready to accept! " << endl;
  int sockfd = 0;
  int errn = 0;
  cout << event.GetServerSocket()->Accept(sockfd, errn) << endl;
}




