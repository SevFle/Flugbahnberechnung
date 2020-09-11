#ifndef C_WATCHDOG_H
#define C_WATCHDOG_H
#include <thread>
#include <atomic>
#include <chrono>
#include <functional>


namespace watchdog
  {
    typedef std::chrono::steady_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

  class C_watchdog
    {
  public:
    C_watchdog();
    ~C_watchdog();

  private:
    std::thread*              watchThread;
    std::thread*              _thread;
    unsigned int              _interval;
    std::atomic<unsigned int> _timer;
    std::atomic<bool>         _running;
    std::atomic<bool>         *stopCondition;
    std::function<void ()>    startFunc;
    std::function<void ()>    stopFunc;
    std::function<void ()>    restartFunc;

    Clock::time_point         lastPet;

  public:

    void pet();
    void start(unsigned int interval, std::atomic<bool> &stopCondition, std::thread *thread, std::function<void ()> startFunc);
    void start(unsigned int interval, std::atomic<bool> &stopCondition,std::thread *thread, std::function<void ()> startFunc,std::function<void ()> restartFunc);
    void stop();

    void setIntervall(unsigned int interval);

  private:
    void watch();
    void restartThread();

      };

  }


#endif // C_WATCHDOG_H
