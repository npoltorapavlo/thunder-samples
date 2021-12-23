#ifndef MODULE_NAME
#define MODULE_NAME Rpc_Test
#endif

#include <core/core.h>
#include <com/com.h>
#include <plugins/plugins.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

using namespace WPEFramework;

#define TICKS_IN_S 1000000

auto CreateToken(
    const string& payload,
    const string& name,
    const string& endpoint,
    string& token) -> uint32_t {

  uint32_t result = Core::ERROR_OPENING_FAILED;

  // < THREADPOOLCOUNT=1, STACKSIZE=0, MESSAGESLOTS=4 >
  auto engine = Core::ProxyType < RPC::InvokeServerType < 1, 0, 4 >> ::Create();

  auto client = Core::ProxyType<RPC::CommunicatorClient>::Create(
      Core::NodeId(endpoint.c_str()), Core::ProxyType<Core::IIPCServer>(engine));

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
  int repeat;

  Args(int argc, char **argv)
      : payload((argc > 1) ? argv[1] : "https://google.com"),
        name((argc > 2) ? argv[2] : "SecurityAgent"),
        endpoint((argc > 3) ? argv[3] : "/tmp/SecurityAgent/token"),
        repeat((argc > 4) ? atoi(argv[4]) : 1) {}
};

int main(int argc, char** argv) {

  const Args args(argc, argv);

  for (int i = 0; i < args.repeat; i++) {
    auto startTime = Core::Time::Now();

    string token;

    auto errCode = CreateToken(args.payload, args.name, args.endpoint, token);

    auto endTime = Core::Time::Now();
    auto timeDiff = (endTime - startTime).Ticks();

    printf("errCode: %u (%d), result: '%s' [time:%.6fs, params:%db, result:%db]\n",
           errCode,
           errCode,
           token.c_str(),
           timeDiff / double(TICKS_IN_S),
           args.payload.size(),
           token.size());
  }

  return 0;
}
