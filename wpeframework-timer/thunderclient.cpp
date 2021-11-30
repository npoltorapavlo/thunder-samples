#include "thunderclient.h"

#define WARMING_UP_TIME_IN_SECONDS 5
#define RECONNECTION_TIME_IN_MILLISECONDS 5500
#define SUBSCRIBE_TIME_OUT 1000
#define ACTIVATE_TIME_OUT 2000
#define GET_STATUS_TIME_OUT 2000

using namespace std;
using namespace WPEFramework;

ThunderClient::ThunderClient(const string &serverDetails, const string &callsign, bool waitTimer)
  : m_subscribed(false)
  , m_serverDetails(serverDetails)
  , m_callsign(callsign)
  , m_waitTimer(waitTimer) {
  m_timer.connect(std::bind(&ThunderClient::onTimer, this));
}

ThunderClient::~ThunderClient() {
  printf("%s\n", __FUNCTION__);

  if (m_waitTimer) {
    Core::SafeSyncType<Core::CriticalSection> scopedLock(m_timedLock);
    printf("%s acquired lock\n", __FUNCTION__);
  }
}

void ThunderClient::Init(const std::list<string> &events) {
  m_subscribed = false;
  m_events = events;

  m_controller.Init(m_serverDetails);

  if (m_timer.isActive()) {
    m_timer.stop();
  }

  m_controller.Activate(ACTIVATE_TIME_OUT, m_callsign);

  if (nullptr == m_client) {
    Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), m_serverDetails);
    m_client = Core::ProxyType < WPEFramework::JSONRPC::LinkType <
               WPEFramework::Core::JSON::IElement >> ::Create(m_callsign + ".1", (m_callsign + ".1").c_str());
  }

  printf("Starting the timer\n");
  m_timer.start(RECONNECTION_TIME_IN_MILLISECONDS);
}

bool ThunderClient::subscribeForEvent(const string &eventName, const ThunderClientEventHandler& method) {
  bool result = false;

  printf("Attempting to subscribe for event: %s\n", eventName.c_str());

  uint32_t err = m_client->Subscribe<JsonObject>(SUBSCRIBE_TIME_OUT, eventName, method, this);
  if (err == Core::ERROR_NONE) {
    printf("Subscribed for %s\n", eventName.c_str());
    result = true;
  } else {
    printf("Failed to subscribe for %s with code %d\n", eventName.c_str(), err);
  }

  return result;
}

void ThunderClient::onTimer() {
  printf("%s\n", __FUNCTION__);

  Core::SafeSyncType<Core::CriticalSection> scopedLock(m_timedLock);
  printf("%s acquired lock\n", __FUNCTION__);

  bool pluginActivated = m_controller.IsActivated(GET_STATUS_TIME_OUT, m_callsign);
  if (!m_subscribed) {
    if (pluginActivated) {
      bool failed = false;
      for (auto const &i : m_events) {
        if (!subscribeForEvent(i, &ThunderClient::onEvent)) {
          failed = true;
          break;
        }
      }
      if (!failed) {
        m_subscribed = true;
        if (m_timer.isActive()) {
          m_timer.stop();
          printf("Timer stopped.\n");
        }
        printf("Subscription completed.\n");
        sleep(WARMING_UP_TIME_IN_SECONDS);
      }
    }
    if (!m_subscribed) {
      printf("Could not subscribe this time, one more attempt in %d msec. Plugin is %s\n",
             RECONNECTION_TIME_IN_MILLISECONDS, pluginActivated ? "ACTIVE" : "BLOCKED");
      if (!pluginActivated) {
        m_controller.Activate(ACTIVATE_TIME_OUT, m_callsign);
      }
    }
  } else {
    printf("Already subscribed. Stopping the timer.\n");
    if (m_timer.isActive()) {
      m_timer.stop();
    }
  }
}

void ThunderClient::onEvent(const JsonObject& parameters) {
  string message;
  parameters.ToString(message);
  printf("%s : %s\n", __FUNCTION__, message.c_str());
}
