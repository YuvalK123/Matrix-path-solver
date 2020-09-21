//
// Created by israela on 11/01/2020.
//

#include "MyTestClientHandler.h"
#include <iostream>
#include <mutex>
#include <sys/socket.h>
#include <vector>
#include <unistd.h>
#include "StringReverser.h"
#include <string.h>
#include "FileCacheManager.h"
using namespace std;

void MyTestClientHandler::handleCLient(int clientSocket) {
    cout << "handler!!" << endl;
    //gets message from the client
    int bufferSize = 1024;
    char *buff = new char[bufferSize];
    mutex x;
    string str = "";
    const std::lock_guard<std::mutex> lock(x);
    memset(buff, 1, bufferSize);//clear buffer
    //wait for msg
    int byteRecv = recv(clientSocket, buff, bufferSize, 0);
    if (byteRecv == -1) {
        cerr << "connection issue" << endl;
    }
    if (byteRecv == 0) {
        cout << "client disconnected" << endl;
    }
    str += string(buff, 0, byteRecv);
    cout << "str -> " + str << endl;

    string solution;
    cacheManager = new FileCacheManager();
    bool isProblemExist = cacheManager->isExist(str);
    if(isProblemExist){
        solution = cacheManager->get(str);
    }else{
        //solve the problem
        solver = new StringReverser();
        solution = solver->solve(&str);
        cacheManager->insert(str,solution);
    }

    //send the solution to the client
    int byteSend = send(clientSocket, solution.c_str(), solution.length(), 0);
    if (byteSend == -1) {
        cerr << "connection issue" << endl;
    }
    if (byteSend == 0) {
        cout << "client disconnected" << endl;
    }

    close(clientSocket);
    delete[] buff;
}