//
// Created by israela on 11/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "string"

class MyTestClientHandler : public ClientHandler{
private:
    Solver<std::string, std::string> *solver;
    CacheManager<std::string, std::string> *cacheManager;
public:
    void handleCLient(int socket) override;
    explicit MyTestClientHandler() = default;
    ~MyTestClientHandler() override = default;
};

#endif //EX4_MYTESTCLIENTHANDLER_H
