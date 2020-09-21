//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__SEARCHER_H_
#define EX4__SEARCHER_H_
#include "Searchable.h"

template <class T, class Solution>
class Searcher {
public:
    virtual Solution search(Searchable<T> *searchable) = 0;
    Searcher() = default;
    virtual ~Searcher() = default;
};

#endif //EX4__SEARCHER_H_
