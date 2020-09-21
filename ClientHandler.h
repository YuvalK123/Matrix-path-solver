//
// Created by israela on 11/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H


class ClientHandler {
public:
  virtual ~ClientHandler() = default;
  /**
   *
   * @return new copied client handler
   */
    virtual ClientHandler* Copy() = 0;
    /**
     *
     * @param socket client socket
     */
    virtual void handleCLient(int socket) = 0;
};


#endif //EX4_CLIENTHANDLER_H
