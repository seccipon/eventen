#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

#include "shared_queue.h"
#include "../general/runnable.h"
class ThreadPool : public boost::noncopyable
{

public:
  explicit ThreadPool()
  { }

  void Init(int threadCnt);


  void ThreadRoutine();
  void Join();
  void Stop();

  void PostRunnable(PRunnable p);
private:
  int m_threadCnt;
  boost::thread_group m_threadGroup;
  SharedQueue<PRunnable> m_runnablesQueue;
};

typedef std::shared_ptr<ThreadPool> PThreadPool;



extern PThreadPool gThreadPool;
#endif // THREADPOOL_H
