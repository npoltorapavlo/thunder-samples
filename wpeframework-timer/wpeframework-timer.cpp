#include "thunderclient.h"

#include <list>
#include <thread>
#include <chrono>
#include <stdlib.h>

struct Args {
  int clientRunMs;
  bool waitTimer;
  string callsign;
  std::list<string> events;

  Args(int argc, char **argv)
    : clientRunMs(atoi(argv[1]))
    , waitTimer(string(argv[2]) == "true")
    , callsign(argv[3]) {

    for (int i = 4; i < argc; i++) {
      events.emplace_back(argv[i]);
    }
  }
};

int main(int argc, char** argv) {
  const Args args(argc, argv);

  auto client = new ThunderClient("127.0.0.1:9998", args.callsign, args.waitTimer);
  client->Init(args.events);

  std::this_thread::sleep_for(std::chrono::milliseconds(args.clientRunMs));

  delete client;

  return 0;
}
