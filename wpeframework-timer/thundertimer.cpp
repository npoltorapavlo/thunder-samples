#include "thundertimer.h"

using namespace std;
using namespace WPEFramework;

ThunderTimer::ThunderTimer()
  : baseTimer(64 * 1024, "TestTimer")
  , m_timerJob(this)
  , m_isActive(false)
  , m_isSingleShot(false)
  , m_intervalInMs(-1) {
}

ThunderTimer::~ThunderTimer() {
  stop();
}

bool ThunderTimer::isActive() {
  return m_isActive;
}

void ThunderTimer::stop() {
  baseTimer.Revoke(m_timerJob);
  m_isActive = false;
}

void ThunderTimer::start() {
  baseTimer.Revoke(m_timerJob);
  baseTimer.Schedule(Core::Time::Now().Add(m_intervalInMs), m_timerJob);
  m_isActive = true;
}

void ThunderTimer::start(int msec) {
  setInterval(msec);
  start();
}

void ThunderTimer::setSingleShot(bool val) {
  m_isSingleShot = val;
}

void ThunderTimer::setInterval(int msec) {
  m_intervalInMs = msec;
}

void ThunderTimer::connect(std::function< void() > callback) {
  onTimeoutCallback = callback;
}

void ThunderTimer::Timed() {
  if (onTimeoutCallback != nullptr) {
    onTimeoutCallback();
  }

  if (m_isActive) {
    if (m_isSingleShot) {
      stop();
    } else {
      start();
    }
  }
}

uint64_t ThunderTimer::TimerJob::Timed(const uint64_t scheduledTime) {
  if (m_timer) {
    m_timer->Timed();
  }
  return 0;
}
