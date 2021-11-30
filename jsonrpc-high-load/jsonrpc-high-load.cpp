#ifndef MODULE_NAME
#define MODULE_NAME Sample_JsonRpcHighLoad
#endif

#include <core/core.h>
#include <plugins/plugins.h>
#include <websocket/websocket.h>
#include <securityagent/SecurityTokenUtil.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace WPEFramework;

#define SERVER_DETAILS  "127.0.0.1:9998"
#define MAX_LENGTH 1024

#define VOICE_MESSAGE_FILE "./voice-message.json"
#define MAX_ITERATION 1000
#define JSONRPC_TIMEOUT 30000

int CreateToken(string &token) {
  unsigned char buffer[MAX_LENGTH] = {0};
  int tokenStatus = GetSecurityToken(MAX_LENGTH, buffer);
  if (tokenStatus > 0) {
    token = (char *) buffer;
  }
  return tokenStatus;
}

JsonObject ReadJsonFile(const string &filename) {
  JsonObject result;
  Core::File file(filename);
  if (file.Open(true))
    result.IElement::FromFile(file);
  return result;
}

typedef Core::ProxyType< JSONRPC::LinkType<Core::JSON::IElement> > Client;
typedef Core::JSON::ArrayType <PluginHost::MetaData::Service> StatusResult;

void InvokeJsonRpc(Client &plugin, uint32_t waitTime, const string &method, const JsonObject &params = JsonObject()) {
  Core::Time start = Core::Time::Now();

  string resultStr;
  uint32_t errCode;
  if (method.find('@') != string::npos) {
    StatusResult result;
    errCode = plugin->Get<StatusResult>(waitTime, method, result);
    result.ToString(resultStr);
  } else {
    JsonObject result;
    errCode = plugin->Invoke<JsonObject, JsonObject>(waitTime, method, params, result);
    result.ToString(resultStr);
  }

  printf("%s errCode: %d, result: '%s', time: %" PRIu64 " (timeout %u ms)\n",
         method.c_str(),
         errCode,
         resultStr.c_str(),
         (Core::Time::Now() - start).Ticks(),
         waitTime
  );
}

static string query;

class SendVoiceMessage : public Core::Thread {
public:
  SendVoiceMessage(const SendVoiceMessage &) = delete;
  SendVoiceMessage &operator=(const SendVoiceMessage &) = delete;

  SendVoiceMessage()
      : Core::Thread(), voiceControl(Client::Create("org.rdk.VoiceControl.1", nullptr, false, query)),
        voiceMessage(ReadJsonFile(VOICE_MESSAGE_FILE)) {
    Thread::Init();
  }

  virtual ~SendVoiceMessage() {
    Stop();
    Wait(Thread::STOPPED, Core::infinite);
  }

public:
  uint32_t Worker() override {
    for (uint32_t i = MAX_ITERATION; i > 0; i--) {
      InvokeJsonRpc(voiceControl, JSONRPC_TIMEOUT, "sendVoiceMessage", voiceMessage);
    }
    return (Core::infinite);
  }

private:
  Client voiceControl;
  JsonObject voiceMessage;
};

class FetchStatus : public Core::Thread {
public:
  FetchStatus(const FetchStatus &) = delete;
  FetchStatus &operator=(const FetchStatus &) = delete;

  FetchStatus()
      : Core::Thread(), controller(Client::Create("", nullptr, false, query)) {
    Thread::Init();
  }

  virtual ~FetchStatus() {
    Stop();
    Wait(Thread::STOPPED, Core::infinite);
  }

public:
  uint32_t Worker() override {
    for (uint32_t i = MAX_ITERATION; i > 0; i--) {
      InvokeJsonRpc(controller, JSONRPC_TIMEOUT, "status@org.rdk.VoiceControl");
    }
    return (Core::infinite);
  }

private:
  Client controller;
};

int main(int argc, char** argv) {

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));

  string token;
  if (CreateToken(token) > 0) {
    query = "token=" + token;
    printf("token is '%s'\n", token.c_str());
  }

  SendVoiceMessage sendVoiceMessage;
  FetchStatus fetchStatus;
  sendVoiceMessage.Run();
  fetchStatus.Run();
  sendVoiceMessage.Wait(Core::Thread::STOPPED, Core::infinite);
  fetchStatus.Wait(Core::Thread::STOPPED, Core::infinite);
  
  return 0;
}
