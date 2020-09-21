//
// Created by israela on 12/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include <string.h>
#include <cstring>
#include "Solver.h"
#include <bits/stdc++.h>
#include <iostream>


//template <typename Problem,typename Solution>
class StringReverser : public Solver<std::string,std::string>{
public:
    std::string solve(std::string *problem) {
        /*std::reverse(problem.begin(),problem.end());
        std::cout << "reverse= " + problem << std::endl;*/
        return *problem;
     }
     StringReverser() = default;
};

#endif //EX4_STRINGREVERSER_H
