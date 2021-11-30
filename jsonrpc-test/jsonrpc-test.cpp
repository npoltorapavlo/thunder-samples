#ifndef MODULE_NAME
#define MODULE_NAME Sample_WPEFrameworkErrcode
#endif

#include <core/core.h>
#include <websocket/websocket.h>
#include <securityagent/SecurityTokenUtil.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace std;
using namespace WPEFramework;

#define SERVER_DETAILS  "127.0.0.1:9998"
#define MAX_LENGTH 1024

int CreateToken(string &token) {
  unsigned char buffer[MAX_LENGTH] = {0};
  int tokenStatus = GetSecurityToken(MAX_LENGTH, buffer);

  if (tokenStatus > 0) {
    token = (char *) buffer;
  }

  printf("CreateToken, tokenStatus=%d, token=%s\n", tokenStatus, token.c_str());

  return tokenStatus;
}

string GetJsonObjectResultString(const JsonObject& jsonObject) {
  string result;
  jsonObject.ToString(result);
  return result;
}

struct Call {
  int timeout;
  string callsign;
  string method;
  JsonObject params;

  Call(int t, string designator, string p)
      : timeout(t), callsign(), method(), params(p) {
    size_t pos = designator.rfind('.');
    if (pos != string::npos) {
      callsign = designator.substr(0, pos);
      method = designator.substr(pos + 1);
    } else {
      method = designator;
    }
  }
};

struct Args {
  bool useToken;
  list<Call> calls;

  Args(int argc, char **argv)
      : useToken((argc > 1) && (string(argv[1]) == "true")) {
    for (int i = 2; i + 2 < argc; i += 3) {
      calls.emplace_back(atoi(argv[i]), argv[i + 1], argv[i + 2]);
    }
  }
};

typedef Core::ProxyType< JSONRPC::LinkType<Core::JSON::IElement> > Plugin;
typedef map<string, Plugin> PluginMap;

int main(int argc, char** argv) {

  const Args args(argc, argv);

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));

  string token, query;
  if (args.useToken) {
    if (CreateToken(token) > 0) {
      query = "token=" + token;
    }
  }

  PluginMap plugins;

  for (auto const &call : args.calls) {
    auto it = plugins.emplace(std::piecewise_construct,
        std::forward_as_tuple(call.callsign),
        std::forward_as_tuple());

    if (it.second == true) {
      it.first->second = Plugin::Create(call.callsign, nullptr, false, query);
    }

    JsonObject result;
    auto errCode = it.first->second->Invoke<JsonObject, JsonObject>(call.timeout, call.method, call.params, result);
    printf("errCode: %u (%d), result: '%s'\n", errCode, errCode,
           GetJsonObjectResultString(result).c_str());
  }

  return 0;
}
