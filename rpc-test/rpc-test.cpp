#ifndef MODULE_NAME
#define MODULE_NAME Rpc_Test
#endif

#include <core/core.h>
#include <com/com.h>
#include <plugins/plugins.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace WPEFramework;

auto CreateToken(
    const string& payload,
    const string& name,
    const string& endpoint,
    string& token) -> uint32_t {

  uint32_t result = Core::ERROR_OPENING_FAILED;

  auto engine = Core::ProxyType < RPC::InvokeServerType < 1, 0, 4 >> ::Create();
  auto client = Core::ProxyType<RPC::CommunicatorClient>::Create(
      Core::NodeId(endpoint), Core::ProxyType<Core::IIPCServer>(engine));

  if ((client.IsValid() == true) && (client->IsOpen() == false)) {
    PluginHost::IAuthenticate *interface =
        client->Open<PluginHost::IAuthenticate>(name);

    if (interface != nullptr) {
      result = interface->CreateToken(payload.size(),
                                      (const uint8_t *) payload.data(), token);
      interface->Release();
    }

    client.Release();
  }

  return result;
}

struct Args {
  string payload;
  string name;
  string endpoint;

  Args(int argc, char **argv)
      : payload((argc > 1) ? argv[1] : "https://google.com"),
        name((argc > 2) ? argv[2] : "SecurityAgent"),
        endpoint((argc > 3) ? argv[3] : "/tmp/SecurityAgent/token") {}
};

int main(int argc, char** argv) {

  const Args args(argc, argv);

  string token;

  if (CreateToken(args.payload, token) == Core::ERROR_NONE) {
    printf("Token for '%s' is '%s'\n", args.payload, token.c_str());
  }

  return 0;
}
