//
// Created by israela on 11/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class FileCacheManager : public CacheManager<string,string>{
  ~FileCacheManager() override = default;
    void insert(string problem,string solution){

        //insert the key to the files or update the file
        auto h = std::hash<std::string>{}(problem);
        int fileNameInt = h;
        string fileName = to_string(fileNameInt) + ".txt";

        ofstream out_file(fileName, ios::out);
        out_file << solution;
    }
    string get(string problem) {
        auto h = std::hash<std::string>{}(problem);
        int fileNameInt = h;
        string fileName = to_string(fileNameInt);
        string solution;
        string currentFile = fileName + ".txt";
        fstream in_file;
        in_file.open(currentFile,ios::in);
        if(!in_file){
            throw "The key does not exist";
        }
        in_file >> solution;
        return solution;
    }

    bool isExist(string problem){
        auto h = std::hash<std::string>{}(problem);
        int fileNameInt = h;
        string fileName = to_string(fileNameInt) + ".txt";

        ifstream in_file;
        in_file.open(fileName);
        if(!in_file){
            return false;
        }
        return true;
    }
};


#endif //EX4_FILECACHEMANAGER_H
