#include "tasktest.h"
#include "../../event/test/eventtest.h"

#include <iostream>

using namespace std;


void TaskTest::DoThing()
{
  cout << "Doing Task things"<< endl;
  PostEvent(PEvent(new EventTest()));
}
