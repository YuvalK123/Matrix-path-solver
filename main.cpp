//#include <iostream>
//#include "thread"
//#include "Server.h"
//#include "MyTestClientHandler.h"
#ifndef EX4_MAIN_CPP
#define EX4_MAIN_CPP
#include "boot.h"
using namespace std;


void server();

int main(int argc,char **argv) {
  boot::Main main = boot::Main();
  main.main(argv[argc - 1]);
}


#endif //EX4_SERVER_H
