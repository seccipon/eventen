
#include "ehnetworkloop.h"
#include <iostream>

#include "engine_eht/event/network/eventstreamsocketaccepted.h"
#include "engine_eht/event/network/event_socket_ready_to_accept.h"


using namespace std;
void EHNetworkLoop::HandleEvent(const EventStreamSocketAccepted &event)
{
  cout << "Event happened : socket accepted!" << event.GetSocket() << endl;

}

void EHNetworkLoop::HandleEvent(const EventSocketReadyToAccept &event)
{
  cout << "Ready to accept! " << endl;
  int sockfd = 0;
  cout << event.GetServerSocket()->Accept(sockfd) << endl;
}



