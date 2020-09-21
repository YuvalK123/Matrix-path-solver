//
// Created by israela on 11/01/2020.
//

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

using namespace std;

#define PORT 8081

void MySerialServer::open(int port,ClientHandler *c){
    start(port,c);
}

void MySerialServer::stop() {
    this->isDone = true;
}



void MySerialServer::start(int port,ClientHandler *c){
    int sockfd = createSocket(port);
    cout<<"start"<<endl;
    while (sockfd < 0){
      sockfd = createSocket(port);
    }
    cout<<"connected"<<endl;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int clientSocket;
    //accept a call
    while(!isDone){

        //timeout
        struct timeval tv;
        tv.tv_sec = 120;// 2 minutes
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);


        //char host[NI_MAXHOST];
        //char svc[NI_MAXHOST];
        clientSocket = accept(sockfd, (sockaddr *) &client, &clientSize);
        if (clientSocket == -1) {
            if (errno == EWOULDBLOCK){
                cout << "Time Out!" <<endl;
            }else{
                cerr << "problem with client conn";
            }
            //close(sockfd);
            stop();
            //return -4;
        }

        //c = MyTestClientHandler();
        c->handleCLient(clientSocket);
        close(clientSocket);
    }

    //close the listening socket
    close(sockfd);
}
int MySerialServer::createSocket(int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    close(sockfd);
    return -1;
  }

  //bind
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  inet_pton(AF_INET, "0.0.0.0", &address.sin_addr);
  if (bind(sockfd, (const struct sockaddr *) &address, (socklen_t) sizeof(address)) == -1) {
//    cerr << "error binding";
    close(sockfd);
    return -2;
  }

  //mark the socket
  if (listen(sockfd, 1) == -1) {
//    cerr << "cant mark";
    close(sockfd);
    return -3;
  }
  return sockfd;
}
