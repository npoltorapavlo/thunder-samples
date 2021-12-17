#ifndef MODULE_NAME
#define MODULE_NAME JsonRpc_Test
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
    uint64_t Timed(const uint64_t scheduledTime);

  private:
    ThunderTimer *m_timer;
  };

public:
  ThunderTimer() : baseTimer(64 * 1024, "TestTimer"), m_timerJob(this), m_isActive(false), m_intervalInMs(-1) {}

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

  WPEFramework::Core::TimerType <TimerJob> baseTimer;
  TimerJob m_timerJob;
  bool m_isActive;
  int m_intervalInMs;

  std::function<void()> onTimeoutCallback;
};

struct Context {};

class ThunderClient {
private:
  ThunderClient &operator=(const ThunderClient &copy) = delete;

  ThunderClient(const ThunderClient &copy) = delete;

public:
  ThunderClient(const std::shared_ptr <Context> &context) : m_context(context) {
    m_timer.connect(std::bind(&ThunderClient::onTimer, this));
    m_timer.start(1000);
  }

  ~ThunderClient() {
//    Core::SafeSyncType<Core::CriticalSection> scopedLock(m_timedLock);
//    printf("%s acquired lock\n", __FUNCTION__);
  }

private:
  void onTimer() {
    Core::SafeSyncType <Core::CriticalSection> scopedLock(m_timedLock);
    printf("%s acquired lock\n", __FUNCTION__);

    sleep(2);

    printf("context %s expired\n", (m_context.expired() ? "is":"is not"));
  }

private:
  ThunderTimer m_timer;
  WPEFramework::Core::CriticalSection m_timedLock;
  std::weak_ptr<Context> m_context;
};

int main(int argc, char** argv) {
  {
    std::shared_ptr <Context> context(new Context);
    {
      ThunderClient client(context);

      sleep(2);
    }
  }

  sleep(2);

  return 0;
}
