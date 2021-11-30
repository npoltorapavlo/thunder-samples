#include "tokenfactory.h"

using namespace std;
using namespace WPEFramework;

template <class TOKEN_TYPE>
bool _iteration(TOKEN_TYPE & jwt, pid_t pid, const string &source) {
  bool result = false;

  string token;
  jwt.Encode(token,
             static_cast<uint16_t>(source.length()),
             reinterpret_cast<const uint8_t *>(source.c_str()));
  uint16_t load = jwt.PayloadLength(token);

  if (load != static_cast<uint16_t>(~0)) {
    uint8_t *payload = reinterpret_cast<uint8_t *>(ALLOCA(load));

    load = jwt.Decode(token, load, payload);

    if (load != static_cast<uint16_t>(~0)) {
      string decoded(reinterpret_cast<const TCHAR *>(payload), load);
      result = (decoded == source);
    }
  }

  printf("[pid:%ld] %s. Token : %s\n",
         (long) pid, (result ? "passed" : "failed"), token.c_str());

  return result;
}

void _thread(pid_t pid, const string &source, int numIterations) {
  auto jwt = JWTFactory::Instance().Element();

  for (int i = 0; i < numIterations; i++) {
    _iteration(*jwt, pid, source);
  }
}

void _process(pid_t pid, const string &source, int numThreads, int numIterations) {
  list<thread> threads;

  for (int i = 0; i < numThreads; i++) {
    threads.emplace_back([&] { _thread(pid, source, numIterations); });
  }

  for (auto &i : threads)
    i.join();
}

struct Args {
  const string source;
  const int numForks;
  const int numThreads;
  const int numIterations;

  Args(int argc, char **argv)
      : source((argc > 1) ? argv[1] : "http://google.com"), numForks((argc > 2) ? atoi(argv[2]) : 2),
        numThreads((argc > 3) ? atoi(argv[3]) : 2),
        numIterations((argc > 4) ? atoi(argv[4]) : 5) {
  }
};

int main(int argc, char** argv) {
  const Args args(argc, argv);

  printf("starting pid %ld payload=%s numForks=%d numThreads=%d numIterations=%d\n",
         (long) getpid(), args.source.c_str(), args.numForks, args.numThreads, args.numIterations);

  for (int i = 0; i < args.numForks; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      printf("forked child process pid %ld\n", (long) getpid());
      _process(getpid(), args.source, args.numThreads, args.numIterations);
      break;
    }
  }

  printf("ending pid %ld\n", (long) getpid());

  return 0;
}
