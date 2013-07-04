#include "threadpool.h"


#include <iostream>

#include "log/log.h"
#include "exceptions/exceptions.h"

#undef LOG_DEFINE_FILELOCAL_LOGGER
#undef LOG_LOGGER_TAG
#define LOG_FILELOCAL_LOGGER Log::GetThreadLogger()
#define LOG_LOGGER_TAG "Thread Pool"


using namespace std;

void ThreadPool::Init(int threadCnt)
{
  LOG_SET_LOGGER_FILELOCAL;

  m_threadCnt = threadCnt;
  LOG("Pool {%1%} >> Initialized (thread cnt = %2%)", % this % m_threadCnt);
  while (threadCnt--) {
    m_threadGroup.create_thread(std::bind(&ThreadPool::ThreadRoutine, this));
  }


}

void ThreadPool::ThreadRoutine()
{
  LOG_SET_LOGGER_FILELOCAL;

  LOG("Pool {%1%} pthread_id: %2% >> Run", % this % boost::this_thread::get_id());
  for (;;) {
    PRunnable runnable;
    while(!m_runnablesQueue.GetBlock(runnable));
    if (!runnable) {
      LOG("Pool {%1%} pthread_id: %2% >> Halting...", % this % boost::this_thread::get_id());
      break;
    }
    LOG("Pool {%1%} pthread_id: %2% >> Run runnable: %3%", % this % boost::this_thread::get_id() % typeid(*runnable).name());
    try {
      runnable->Run();
      LOG("Pool {%1%} pthread_id: %2% >> Runnable completed : %3%", % this % boost::this_thread::get_id() % typeid(*runnable).name());
    } catch(ExceptionAssertFailed & e) {
      LOG_BASE(Log::GetLogicErrorLogger(), LOG_LEVEL_LOGICERROR, "Pool {%1%} pthread_id: %2% >> \n\t !!!!!! ASSERTION FAILED IN RUNNABLE %3%\n\t\t >> %4%",
          % this % boost::this_thread::get_id() % typeid(*runnable).name() % e.what());
    } catch (std::exception &e) {
      LOG_BASE(Log::GetLogicErrorLogger(), LOG_LEVEL_LOGICERROR, "Pool {%1%} pthread_id: %2% >> Uncaught std::exception while running runnable %3%, \n\t\t\twhat() == %4%",
               % this % boost::this_thread::get_id() % typeid(*runnable).name() % e.what());
    } catch(...) {
      LOG_BASE(Log::GetLogicErrorLogger(), LOG_LEVEL_LOGICERROR, "Pool {%1%} pthread_id: %2% >> Uncaught unknown exception while running runnable %3%",
               % this % boost::this_thread::get_id() % typeid(*runnable).name());
    }
  }
  LOG("Pool {%1%} pthread_id: %2% >> Halt", % this % boost::this_thread::get_id());
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

