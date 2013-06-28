#include "loop.h"


bool Loop::IsBreak()
{
  return m_flBreak;
}

void Loop::Run()
{
  Init();
  while(!IsBreak()) {
    OneLoop();
  }
  Destroy();
}

void Loop::Break()
{
  m_flBreak = true;
  DoBreak();
}

