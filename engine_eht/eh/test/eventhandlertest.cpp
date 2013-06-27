#include "eventhandlertest.h"

#include <iostream>
using namespace std;

void EventHandlerTest::HandleEvent(const EventTest &event)
{
  cout << "handle event test!" << endl;
}
