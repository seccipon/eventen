#include "loop.h"


void Loop::Run()
{
  Init();
  while(!IsInterrupted()) {
    OneLoop();
  }
  Destroy();
}

