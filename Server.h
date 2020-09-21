//
// Created by israela on 11/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

//using namespace server_side;
namespace server_side {
    class Server {
    public:
      virtual ~Server() = default;
        virtual void open(int port,ClientHandler *c) = 0;
        virtual void  stop() = 0;
    };
}
#endif //EX4_SERVER_H
