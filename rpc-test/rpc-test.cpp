#ifndef MODULE_NAME
#define MODULE_NAME Sample_WPEFrameworkRpcTest
#endif

#include <core/core.h>
#include <com/com.h>
#include <plugins/plugins.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace std;
using namespace WPEFramework;

#define AUTHENTICATE_CLASS "SecurityAgent"
#define AUTHENTICATE_ENDPOINT "/tmp/SecurityAgent/token"

bool CreateToken(const string& payload, string& token) {
  bool result = false;

  auto engine = Core::ProxyType < RPC::InvokeServerType<1, 0, 4>> ::Create();
  auto client = Core::ProxyType<RPC::CommunicatorClient>::Create(
      Core::NodeId(AUTHENTICATE_ENDPOINT), Core::ProxyType<Core::IIPCServer>(engine));

  if ((client.IsValid() == true) && (client->IsOpen() == false)) {
    PluginHost::IAuthenticate *interface =
        client->Open<PluginHost::IAuthenticate>(AUTHENTICATE_CLASS);

    printf("Interface is %p\n", interface);

    if (interface != nullptr) {
      uint32_t error = interface->CreateToken(payload.size(),
                                              (const uint8_t*)payload.data(), token);
      printf("CreateToken %u\n", error);

      if (error == Core::ERROR_NONE) {
        result = true;
      }

      interface->Release();
    }

    client.Release();
  } else {
    printf("Could not open client\n");
  }

  return result;
}

struct Args {
  const char *payload;

  Args(int argc, char **argv)
      : payload(((argc > 1) ? argv[1] : "https://google.com")) {
  }
};

int main(int argc, char** argv) {

  const Args args(argc, argv);

  string token;
  if (CreateToken(args.payload, token)) {
    printf("Token for '%s' is '%s'\n", args.payload, token.c_str());
  }

  return 0;
}
