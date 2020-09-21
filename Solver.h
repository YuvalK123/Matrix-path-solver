//
// Created by israela on 11/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <typename Problem,typename Solution>
class Solver{
public:
     virtual Solution solve(Problem *problem) = 0;
     Solver() = default;
     virtual ~Solver() = default;
};


#endif //EX4_SOLVER_H
