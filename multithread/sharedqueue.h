#ifndef SHAREDQUEUE_H
#define SHAREDQUEUE_H

#include <deque>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/noncopyable.hpp>

template <typename T, int WaitTimeSeconds = 1> class SharedQueue : public boost::noncopyable
{
  std::deque<T> m_queue;
  boost::mutex m_mutex;
  boost::condition_variable m_condVar;
public:

  void Put(const T& t)
  {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_queue.push_back(t);
    m_condVar.notify_one();
  }

  bool GetNonblock(T & t)
  {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    if (m_queue.empty()) {
      return false;
    }
    t = m_queue.front();
    m_queue.pop_front();
    return true;
  }

  bool GetBlock(T & t)
  {
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if (m_queue.empty()) {
      m_condVar.timed_wait(lock, boost::get_system_time() + boost::posix_time::seconds(WaitTimeSeconds));
    }

    if (!m_queue.empty())  {
      t = m_queue.front();
      m_queue.pop_front();
      return true;
    }

    return false;
  }

//  void Pop() {
//    boost::unique_lock<boost::mutex> lock(m_mutex);
//    assert(!m_queue.empty());
//    m_queue.pop_front();
//  }

  bool IsEmpty()
  {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    return m_queue.empty();
  }
};

#endif // SHAREDQUEUE_H
