
//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
#include "State.h"
#include "vector"
template <class T>
class Searchable {
public:
    virtual State<T> getInitialState() = 0;
    virtual bool isGoalState(State<T> element) = 0;
    virtual vector<State<T>> getAllPossibleStates(State<T> state){
        vector<State<T>> vec;
        vec.push_back(state);
        return vec;
    }
    Searchable() = default;
    virtual ~Searchable(){};
};

#endif //EX4__SEARCHABLE_H_