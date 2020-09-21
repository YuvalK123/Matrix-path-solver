//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__OBJECTADAPTER_H_
#define EX4__OBJECTADAPTER_H_
#include "astar.h"
#include "Solver.h"

class ObjectAdapter: public Solver<matrix,string>{
private:
    Searcher<Point,string> *searcher = nullptr;
    Searchable<Point> *searchable = nullptr;
public:
    string solve(matrix *problem) override;
};

string ObjectAdapter::solve(matrix *problem) {
//  auto best = new BestFirstSearch();
  this->searcher = new astar<Point>();
//  this->searcher = new dfs<Point>(problem->getSize());
//     this->searcher = new bfs<Point>(problem->getSize());
     this->searchable = problem;
//     this->searchable = new matrix<string>(problem);
     string sol = searcher->search(searchable);
     return sol;
}

#endif //EX4__OBJECTADAPTER_H_
