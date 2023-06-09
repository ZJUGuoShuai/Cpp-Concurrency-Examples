# C++ Concurrency Examples

学习 C++11 多线程并发编程的过程中编写的一些 Demo，用于演示 C++11 标准线程库的用法。

- [spinlock/](spinlock/)：使用 `std::atomic_flag` 实现一个简单的**自旋锁**。
- [threadsafe_queue/](threadsafe_queue/)：使用 `std::mutex` 和 `std::condition_variable` 实现一个简单的**线程安全的队列**。
- [thread_pool/](thread_pool/)：使用 `std::packaged_task` 和 `std::future` 实现一个简单的**线程池**。
- [producer_consumer/](producer_consumer/)：基于有限阻塞队列实现**生产者消费者模型**。

编译环境：
- Ubuntu 22.04
- g++ 11.3.0
- C++17

主要参考资料：《C++ 并发编程实战》（第二版）。

## TODO

- [ ] 线程安全队列的无锁实现。