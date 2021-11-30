#pragma once

#include "Module.h"

class ThunderTimer {
private:
  ThunderTimer &operator=(const ThunderTimer &copy) = delete;
  ThunderTimer(const ThunderTimer &copy) = delete;

private:
  class TimerJob {
  private:
    TimerJob() = delete;
    TimerJob &operator=(const TimerJob &RHS) = delete;

  public:
    TimerJob(ThunderTimer *t) : m_timer(t) {}
    TimerJob(const TimerJob &copy) : m_timer(copy.m_timer) {}
    ~TimerJob() = default;

    inline bool operator==(const TimerJob &RHS) const {
      return (m_timer == RHS.m_timer);
    }

  public:
    uint64_t Timed(const uint64_t scheduledTime);

  private:
    ThunderTimer *m_timer;
  };

public:
  ThunderTimer();
  ~ThunderTimer();

  bool isActive();
  void stop();
  void start();
  void start(int msec);
  void setSingleShot(bool val);
  void setInterval(int msec);
  void connect(std::function<void()> callback);

private:

  void Timed();

  WPEFramework::Core::TimerType <TimerJob> baseTimer;
  TimerJob m_timerJob;
  bool m_isActive;
  bool m_isSingleShot;
  int m_intervalInMs;

  std::function<void()> onTimeoutCallback;
};
