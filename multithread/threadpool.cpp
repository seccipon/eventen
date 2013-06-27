#include "threadpool.h"


#include <iostream>


using namespace std;

void ThreadPool::Init(int threadCnt)
{
  m_threadCnt = threadCnt;
  while (threadCnt--) {
    m_threadGroup.create_thread(std::bind(&ThreadPool::ThreadRoutine, this));
  }

}

void ThreadPool::ThreadRoutine()
{
  cout << "Thraed started" << endl;
  for (;;) {
    PRunnable runnable;
    while(!m_runnablesQueue.GetBlock(runnable));
    if (!runnable) {
      break;
    }
    runnable->Run();

  }
  cout << "Thread stopped" << endl;
}

void ThreadPool::Join()
{
  m_threadGroup.join_all();
}

void ThreadPool::Stop()
{
  int threadCnt = m_threadCnt;
  while(threadCnt--) {
    m_runnablesQueue.Put(PRunnable());
  }
}

void ThreadPool::PostRunnable(PRunnable p)
{
  m_runnablesQueue.Put(p);
}

