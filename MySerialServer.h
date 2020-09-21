//
// Created by israela on 11/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "Server.h"
using  namespace server_side;

class MySerialServer : public Server{
 private:
  /**
   * creates socket from port
   * @param port
   * @return socket
   */
  int createSocket(int port);
  bool isDone = false;
 public:
  ~MySerialServer() = default;
    void open(int port,ClientHandler *c) override;
    void  stop() override ;
    /**
     *
     * @param port of server
     * @param c client handler
     */
    void start(int port,ClientHandler *c);
};


#endif //EX4_MYSERIALSERVER_H
