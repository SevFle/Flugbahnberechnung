#include "watchdog.h"

using namespace watchdog;


C_watchdog::C_watchdog(int interval, std::atomic<bool> &stopCondition, std::thread *thread, std::function<void ()> startFunc)
  {
  this->start(interval, stopCondition, thread, startFunc);
  }
C_watchdog::C_watchdog(int interval, std::atomic<bool> &stopCondition,std::thread *thread, std::function<void ()> startFunc,std::function<void ()> restartFunc)
  {
  this->start(interval, stopCondition, thread, startFunc, restartFunc);
  }

C_watchdog::~C_watchdog()
  {
  this->stop();
  }

void C_watchdog::pet()
  {
  this->lastPet = Clock::now();
  }
void C_watchdog::restartThread()
  {
  //std::cout << "***BARK***" << ;
  this->stopCondition->store(true);
  delete(this->watchThread);
  if(this->restartFunc != nullptr)
    this->restartFunc();
  this->startFunc();
  }
void C_watchdog::start(unsigned int interval, std::atomic<bool> &stopCondition, std::thread *thread, std::function<void ()> startFunc)
  {
  this->_interval = interval;
  this->stopCondition = &stopCondition;
  this->watchThread = thread;
  this->startFunc = startFunc;
  this->restartFunc = nullptr;
  this->_thread = new std::thread(&C_watchdog::watch, this);
  }
void C_watchdog::start(unsigned int interval, std::atomic<bool> &stopCondition,std::thread *thread, std::function<void ()> startFunc,std::function<void ()> restartFunc)
  {
  this->_interval = interval;
  this->stopCondition = &stopCondition;
  this->watchThread = thread;
  this->startFunc = startFunc;
  this->restartFunc = restartFunc;
  this->_thread = new std::thread(&C_watchdog::watch, this);
  }
void C_watchdog::stop()
  {
  this->_running = false;
  this->_thread->join();
  }

void C_watchdog::watch()
  {
  Clock::time_point now;
  milliseconds      time;
  this->pet();
  while(this->_running)
    {
    now = Clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPet);
    if(time.count() > _interval)
      {
      this->restartThread();
      return;
      }
    }
  }

void C_watchdog::setIntervall(unsigned int interval)
  {
  this->_interval = interval;
  }
