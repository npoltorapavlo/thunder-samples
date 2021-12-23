#ifndef MODULE_NAME
#define MODULE_NAME Core_Timer
#endif

#include <core/core.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace WPEFramework;

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
    uint64_t Timed(const uint64_t scheduledTime) {
      if (m_timer != nullptr) {
        m_timer->Timed();
      }

      return 0;
    }

  private:
    ThunderTimer *m_timer;
  };

public:
  ThunderTimer()
      : baseTimer(64 * 1024 /* pthread stacksize */, "TestTimer"),
        m_timerJob(this),
        m_isActive(false),
        m_intervalInMs(-1) {}

  ~ThunderTimer() {
    stop();
  }

  bool isActive() {
    return m_isActive;
  }

  void stop() {
    baseTimer.Revoke(m_timerJob);
    m_isActive = false;
  }

  void start() {
    baseTimer.Revoke(m_timerJob);
    baseTimer.Schedule(Core::Time::Now().Add(m_intervalInMs), m_timerJob);
    m_isActive = true;
  }

  void start(int msec) {
    setInterval(msec);
    start();
  }

  void setInterval(int msec) {
    m_intervalInMs = msec;
  }

  void connect(std::function<void()> callback) {
    onTimeoutCallback = callback;
  }

private:

  void Timed() {
    if (onTimeoutCallback != nullptr) {
      onTimeoutCallback();
    }

    if (m_isActive) {
      start();
    }
  }

  Core::TimerType <TimerJob> baseTimer;
  TimerJob m_timerJob;
  bool m_isActive;
  int m_intervalInMs;

  std::function<void()> onTimeoutCallback;
};

Core::Event timerEvent(false, true);

class ThunderClient {
private:
  ThunderClient &operator=(const ThunderClient &copy) = delete;

  ThunderClient(const ThunderClient &copy) = delete;

public:
  ThunderClient() {
    m_timer.connect(std::bind(&ThunderClient::onTimer, this));
    m_timer.start(100);
  }

private:
  void onTimer() {
    printf("timer callback start\n");

    timerEvent.SetEvent();

    sleep(1);

    printf("timer callback end\n");
  }

private:
  ThunderTimer m_timer;
};

int main() {
  {
    ThunderClient client;

    printf("waiting for timer\n");

    timerEvent.Lock();

    printf("timer will destroy\n");
  }

  printf("timer has been destroyed\n");

  return 0;
}
