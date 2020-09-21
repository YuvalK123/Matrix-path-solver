//
// Created by israela on 11/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H


#include <string.h>
#include <cstring>
#include <string>
#include <list>
#include <unordered_map>

class unordered_set;
using namespace std;
template <class P, class S> class CacheManager{
protected:

    unordered_map <P,string> cacheMap;
public:
  virtual ~CacheManager() = default;
    virtual void insert(P problem,S solution) = 0;
    virtual S get(P problem) = 0;
    virtual bool isExist(P problem) = 0;
};


#endif //EX4_CACHEMANAGER_H
