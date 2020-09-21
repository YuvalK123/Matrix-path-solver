//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__ATSAR_H_
#define EX4__ATSAR_H_
#include "bestFirstSearch.h"
//endpoint for heuristic function
State<Point> endState;
/**
 *
 * @param cost of path so far
 * @param a prev state
 * @param b child state
 * @return heuristic evaluation
 */
double heuristic(double cost,State<Point> a, State<Point> b);

template <class T>
class astar: public Searcher<T,string>{

public:
~astar() override = default;
  /**
   * constructor method
   * @param end initiate end point
   */
    explicit astar(State<T> end){endState = end;};
    /**
     *
     * @param searchable struct to find solution to
     * @return solution for problem
     */
    string search(Searchable<T> *searchable);
    astar() = default;
};


template<class T>
string astar<T>::search(Searchable<T> *searchable) {
    BestFirstSearch best;
    best.setLambda(&(heuristic));
    return best.search(searchable);
}


double heuristic(double cost,State<Point> a, State<Point> b) {
    return b.getVal() + (endState - b);
}
#endif //EX4__ATSAR_H_