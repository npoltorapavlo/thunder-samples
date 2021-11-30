#include "thundercontroller.h"

#include "thundersecuritytoken.h"

using namespace std;
using namespace WPEFramework;

void ThunderController::Init(const string &serverDetails) {
  string token;
  ThunderSecurityToken::getSecurityToken(token);
  string query = "token=" + token;

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), serverDetails);
  m_link = Core::ProxyType < WPEFramework::JSONRPC::LinkType <
           WPEFramework::Core::JSON::IElement >> ::Create("", "", false, query);
}

bool ThunderController::Activate(const uint32_t waitTime, const string &callSign) {
  bool result = false;

  JsonObject params, response;
  params.Set("callsign", callSign);

  if (!IsActivated(waitTime, callSign)) {
    printf("Activating %s\n", callSign.c_str());
    uint32_t status = m_link->Invoke<JsonObject, JsonObject>(waitTime, "activate", params, response);
    string strParams;
    string strResponse;
    params.ToString(strParams);
    response.ToString(strResponse);
    printf("Activate with params %s, status: %d, response: %s\n",
           strParams.c_str(), status, strResponse.c_str());
    if (status == Core::ERROR_NONE) {
      result = true;
    }
  } else {
    result = true;
  }

  return result;
}

bool ThunderController::IsActivated(const uint32_t waitTime, const string &callSign) {
  bool result = false;

  string method = "status@" + callSign;
  Core::JSON::ArrayType <PluginHost::MetaData::Service> response;
  uint32_t status = m_link->Get < Core::JSON::ArrayType < PluginHost::MetaData::Service > >
                    (waitTime, method.c_str(), response);

  if (status == Core::ERROR_NONE) {
    printf("Getting status for callSign %s, result: %s\n",
           callSign.c_str(), response[0].JSONState.Data().c_str());
    result = response[0].JSONState == PluginHost::IShell::ACTIVATED;
  } else {
    printf("Getting status for callSign %s, status: %d\n",
           callSign.c_str(), status);
  }

  return result;
}
