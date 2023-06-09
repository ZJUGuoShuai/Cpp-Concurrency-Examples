#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class TaskQueue {
 private:
  mutable std::mutex mtx_;
  std::queue<T> q_;
  std::condition_variable cv_;
  bool shutdown_{false};

 public:
  TaskQueue() = default;
  void push(const T& item);
  bool pop(T& ret);
  void signal_for_kill();
};

template <typename T>
void TaskQueue<T>::push(const T& item) {
  {
    std::lock_guard lk{mtx_};
    q_.push(item);
  }
  cv_.notify_one();
}

template <typename T>
bool TaskQueue<T>::pop(T& ret) {
  std::unique_lock lk{mtx_};
  cv_.wait(lk, [this] { return !q_.empty() || shutdown_; });

  if (shutdown_)
    return false;

  ret = q_.front();
  q_.pop();
  return true;
}

template <typename T>
void TaskQueue<T>::signal_for_kill() {
  {
    std::lock_guard lk{mtx_};
    shutdown_ = true;
  }
  cv_.notify_all();
}
