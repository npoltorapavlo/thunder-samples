#pragma once

#include "Module.h"

class ThunderController {
private:
  ThunderController &operator=(const ThunderController &copy) = delete;
  ThunderController(const ThunderController &copy) = delete;

public:
  ThunderController() = default;

  void Init(const string &serverDetails);
  bool Activate(const uint32_t waitTime, const string &callSign);
  bool IsActivated(const uint32_t waitTime, const string &callSign);

private:
  WPEFramework::Core::ProxyType<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> m_link;
};
