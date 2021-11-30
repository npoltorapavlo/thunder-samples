#pragma once

#include "Module.h"

#include "thundertimer.h"
#include "thundercontroller.h"

#include <list>

class ThunderClient {
private:
  ThunderClient() = delete;
  ThunderClient &operator=(const ThunderClient &copy) = delete;
  ThunderClient(const ThunderClient &copy) = delete;

public:
  ThunderClient(const string &serverDetails, const string &callsign, bool waitTimer);
  ~ThunderClient();

  void Init(const std::list<string> &events);

private:
  typedef void (ThunderClient::*ThunderClientEventHandler)(const JsonObject&);

  void onEvent(const JsonObject& parameters);
  bool subscribeForEvent(const string &eventName, const ThunderClientEventHandler& method);
  void onTimer();

private:
  ThunderController m_controller;
  ThunderTimer m_timer;
  bool m_subscribed;
  const string m_serverDetails;
  const string m_callsign;
  std::list<string> m_events;
  WPEFramework::Core::ProxyType<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement> > m_client;
  bool m_waitTimer;
  WPEFramework::Core::CriticalSection m_timedLock;
};
