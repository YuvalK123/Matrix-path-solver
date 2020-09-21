//
// Created by yuval Kasner on 30/01/20.
//

#ifndef EX4__BOOT_H_
#define EX4__BOOT_H_

#include "MyParallelServer.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
namespace boot {
class Main {
 public:
  int main(string port);
};
int Main::main(string arg) {
  int port = stoi(arg);
  ClientHandler *c = new MyClientHandler();
  Server *s = new MyParallelServer();
  s->open(port,c);
  return 0;
}
}

#endif //EX4__BOOT_H_
