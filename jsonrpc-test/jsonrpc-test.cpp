#ifndef MODULE_NAME
#define MODULE_NAME JsonRpc_Test
#endif

#include <core/core.h>
#include <websocket/websocket.h>
#include <securityagent/SecurityTokenUtil.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace WPEFramework;

#define SERVER_DETAILS "127.0.0.1:9998"
#define MAX_LENGTH 1024
#define NS_IN_S 1000000000

int CreateToken(string &token) {
  unsigned char buffer[MAX_LENGTH] = {0};
  int tokenStatus = GetSecurityToken(MAX_LENGTH, buffer);

  if (tokenStatus > 0) {
    token = (char *) buffer;
  }

  printf("CreateToken, tokenStatus=%d, token=%s\n", tokenStatus, token.c_str());

  return tokenStatus;
}

string CallsignFromDesignator(const string &designator) {
  size_t pos = designator.rfind('.');

  return ((pos != string::npos) ? designator.substr(0, pos) : "");
}

string MethodFromDesignator(const string &designator) {
  size_t pos = designator.rfind('.');

  return ((pos != string::npos) ? designator.substr(pos + 1) : designator);
}

struct Call {
  int timeout;
  string callsign;
  string method;
  string params;
  int repeat;

  Call(int waitTime, const string &designator, const string &parameters, int count)
      : timeout(waitTime),
        callsign(CallsignFromDesignator(designator)),
        method(MethodFromDesignator(designator)),
        params(parameters),
        repeat(count) {}
};

struct Args {
  bool token;
  std::list <Call> calls;

  Args(int argc, char **argv)
      : token((argc > 1) && (string(argv[1]) == "true")) {
    for (int i = 2; i + 3 < argc; i += 4) {
      calls.emplace_back(atoi(argv[i]), argv[i + 1], argv[i + 2], atoi(argv[i + 3]));
    }
  }
};

typedef Core::ProxyType< JSONRPC::LinkType<Core::JSON::IElement> > Plugin;
typedef std::map<string, Plugin> PluginMap;

int main(int argc, char** argv) {

  const Args args(argc, argv);

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)), false /* forced=false */);

  string token, query;
  if (args.token) {
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

    JsonObject params(call.params);

    for (int i = 0; i < call.repeat; i++) {
      JsonObject result;

      auto startTime = Core::Time::Now();

      auto errCode = it.first->second->Invoke<JsonObject, JsonObject>(
          call.timeout, call.method, params, result);

      auto endTime = Core::Time::Now();
      auto timeDiff = (endTime - startTime).Ticks();

      string str;
      result.ToString(str);

      printf("errCode: %u (%d), result: '%s' [time:%.6fs, params:%db, result:%db]\n",
             errCode,
             errCode,
             str.c_str(),
             timeDiff / double(NS_IN_S),
             call.params.size(),
             str.size());
    }
  }

  return 0;
}
