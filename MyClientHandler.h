//
// Created by israela on 20/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "string"
#include <mutex>
#include <sys/socket.h>
#include <unistd.h>
#include "FileCacheManager.h"
#include "ObjectAdapter.h"
#include <functional>


class MyClientHandler : public ClientHandler {
private:

  Solver<matrix, string> *solver = nullptr;
    CacheManager<std::string, std::string> *cacheManager{};
public:
    void handleCLient(int socket) override;
    /**
     *
     * @param str to split
     * @param token to split by
     * @return  splitted str with vector stl
     */
     vector<string> split(string str, const string &token);
    explicit MyClientHandler() = default;
    /**
     *
     * @param s solver to set
     */

  void setSolver(Solver<matrix, string> *s){this->solver = s;}
  /**
   *
   * @param c cache to set
   */
  void setCache(CacheManager<std::string, std::string> *c){this->cacheManager = c;}
    ~MyClientHandler() = default;
  MyClientHandler* Copy() override;
};

/**
 *
 * @param str to split
 * @param token to split by
 * @return splitted string by vector
 */
vector<string> MyClientHandler::split(string str, const string &token) {
  vector<string> splitted;
  while (!str.empty()) {
    int index = str.find(token);
    if (index != string::npos) {
      splitted.push_back(str.substr(0, index));
      str = str.substr(index + token.size());
      if (str.empty()) {
        splitted.push_back(str);
      }
    } else {
      splitted.push_back(str);
      str = "";
    }
  }
  return splitted;
}

void MyClientHandler::handleCLient(int clientSocket) {
  double inf = numeric_limits<double >::infinity();
  mutex x;
  const std::lock_guard<std::mutex> lock(x);
    matrix *myMatrix;
    vector<vector<double>> tempMatrix;
    vector<double> line;
    bool stop = false;
    string fileName = "";
    while (!stop) {
        //gets message from the client
        int bufferSize = 1024;
        char *buff = new char[bufferSize];
        string str = "";
        memset(buff, 1, bufferSize);//clear buffer
        //wait for msg
        int byteRecv = recv(clientSocket, buff, bufferSize, 0);
        if (byteRecv == -1) {
            cerr << "connection issue" << endl;
            return;
        }
        if (byteRecv == 0) {
            cout << "client disconnected" << endl;
          return;
        }

        str += string(buff, 0, byteRecv);
      cout<<str<<" ";
        if (strstr(str.c_str(),"end") == nullptr) {
          vector<string> splitted = split(str,",");
          for(string s : splitted){
            double tmp = stod(s);
            if (tmp == -1){
              line.push_back(inf);
            } else{
              line.push_back(tmp);
            }
          }
            fileName += str;
            tempMatrix.push_back(line);
            line = {};
        } else {
            stop = true;
            string solution;
            cacheManager = new FileCacheManager();
          bool isProblemExist = false;
//            bool isProblemExist = cacheManager->isExist(fileName);
            if (isProblemExist) {
                cout << "the problem is already exist in the cache" << endl;
                solution = cacheManager->get(fileName);
                stop = true;
            } else {
                //solve the problem
                if(this->solver == nullptr){
                  solver = new ObjectAdapter();
                }

                double problem1 = tempMatrix[tempMatrix.size()-2][0];
                double problem2 = tempMatrix[tempMatrix.size()-2][1];
                double problem3 = tempMatrix[tempMatrix.size()-1][0];
                double problem4 = tempMatrix[tempMatrix.size()-1][1];
                Point start(problem1,problem2,tempMatrix[problem1][problem2]);
                Point goal(problem3,problem4,tempMatrix[problem3][problem4]);
                State<Point> p(goal,tempMatrix[problem3][problem4]);
                cout<<start<<"->"<<goal<<endl;
                tempMatrix.erase(tempMatrix.end()-2,tempMatrix.end());
                myMatrix = new matrix(tempMatrix);
                myMatrix->setProblem(State<Point>(start,tempMatrix[problem1][problem2]),
                        State<Point>(goal,tempMatrix[problem3][problem4]));
                solution = solver->solve(myMatrix);
                cout<<solution<<endl;
                cacheManager->insert(fileName, solution);
            }

            //send the solution to the client
            int byteSend = send(clientSocket, solution.c_str(), solution.length(), 0);
            if (byteSend == -1) {
//                cerr << "connection issue" << endl;
            }
            if (byteSend == 0) {
//                cout << "client disconnected" << endl;
            }
            close(clientSocket);
            delete[] buff;
        }
    }
}


MyClientHandler* MyClientHandler::Copy() {
  return new MyClientHandler();
}


#endif //EX4_MYCLIENTHANDLER_H
