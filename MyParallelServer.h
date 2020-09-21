//
// Created by israela on 13/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "MySerialServer.h"
#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "thread"
#include <string.h>
#include "MyTestClientHandler.h"
#include "Server.h"
#include "vector"
using  namespace server_side;

class MyParallelServer: public Server {
 private:
  volatile bool isDone;
  vector<thread> threads;
 public:
  void open(int port,ClientHandler *c) override ;
  void  stop() override ;
  /**
   *starts the handler
   * @param sockfd of server
   * @param clientSocket
   * @param port of server
   * @param c client handle
   */
  static void start(int sockfd, int clientSocket, int port,ClientHandler *c);
};

void MyParallelServer::open(int port, ClientHandler *c) {
  int i = 0;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
      close(sockfd);
//      cerr << "server can't create a socket" << endl;
      //return -1;
    }

    //bind
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &address.sin_addr);
    if (bind(sockfd, (const struct sockaddr *) &address, (socklen_t) sizeof(address)) == -1) {
//      cerr << "error binding";
      close(sockfd);
      //return -2;
    }
  while (!isDone) {
    //mark the socket
    if (listen(sockfd, 1) == -1) {
//      cerr << "cant mark";
      close(sockfd);
      //return -3;
    }
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int clientSocket;
    //accept a call
    //timeout
    struct timeval tv;
    tv.tv_sec = 120;// 2 minutes
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);


    //char host[NI_MAXHOST];
    //char svc[NI_MAXHOST];
    clientSocket = accept(sockfd, (sockaddr *) &client, &clientSize);
    if (clientSocket == -1) {
      if (errno == EWOULDBLOCK){
//        cout << "Time Out!" <<endl;
      }else{
//        cerr << "problem with client conn";
      }
    }

    this->threads.emplace_back(thread(MyParallelServer::start, sockfd, clientSocket, port, c));
  }
  close(sockfd);
}

void MyParallelServer::stop() {
  this->isDone = true;
}

void MyParallelServer::start(int sockfd, int clientSocket, int port, ClientHandler *c) {
    //c = MyTestClientHandler();
  ClientHandler *copy = c->Copy();
  copy->handleCLient(clientSocket);
    close(clientSocket);
}


#endif //EX4_MYPARALLELSERVER_H
