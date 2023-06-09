#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue {
 private:
  mutable std::mutex mtx_;
  std::queue<T> q_;
  std::condition_variable cv_;

 public:
  ThreadSafeQueue() = default;
  ThreadSafeQueue(const ThreadSafeQueue& other);
  void push(const T& item);
  void pop(T& ret);
  bool try_pop(T& ret);
  bool empty() const;
};

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue& other) {
  std::lock_guard lk{other.mtx_};
  q_ = other.q_;
}

template <typename T>
void ThreadSafeQueue<T>::push(const T& item) {
  {
    std::lock_guard lk{mtx_};
    q_.push(item);
  }
  cv_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::pop(T& ret) {
  std::unique_lock lk{mtx_};
  cv_.wait(lk, [this] { return !q_.empty(); });
  ret = q_.front();
  q_.pop();
}

template <typename T>
bool ThreadSafeQueue<T>::try_pop(T& ret) {
  std::lock_guard lk{mtx_};
  if (q_.empty())
    return false;
  ret = q_.front();
  q_.pop();
  return true;
}

template <typename T>
bool ThreadSafeQueue<T>::empty() const {
  std::lock_guard lk{mtx_};
  return q_.empty();
}
