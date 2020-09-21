//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__BESTFIRSTSEARCH_H_
#define EX4__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "unordered_map"
#include "minHeap.h"
double costFunc(double cost, State<Point> a, State<Point> b);

class BestFirstSearch: public Searcher<Point,string>{
private:
    intPair size;
    //lambda function field of cost
    double(*lambda)(double,State<Point>,State<Point>) = [](double cost,State<Point> a,State<Point> b){ return costFunc(cost,a,b);};

    /**
     *
     * @param prev prev state
     * @param curr current state
     * @return if we moved left or not.
     */
    bool isLeft(Point prev, Point curr);
    /**
  *
  * @param prev prev state
  * @param curr current state
  * @return if we moved right or not.
  */
    bool isRight(Point prev, Point curr);
    /**
  *
  * @param prev prev state
  * @param curr current state
  * @return if we moved up or not.
  */
    bool isUp(Point prev, Point curr);
    /**
  *
  * @param prev prev state
  * @param curr current state
  * @return if we moved down or not.
  */
    bool isDown(Point prev, Point curr);

//    double costFunc(double cost, State<Point> a,State<Point>b);
    vector<State<Point>> bestFirstAlgo(Searchable<Point> *matrix);
public:

    /**
     *
     * @param f function to put lambda as.
     */
    void setLambda(double (*f)(double cost, State<Point>, State<Point>)){this->lambda = f;}
    /**
     * constructor
     */
    explicit BestFirstSearch() = default;
    ~BestFirstSearch() override = default;
    /**
     *
     * @param searchable struct to find solution to
     * @return solution for problem
     */
    string search(Searchable<Point> *searchable) override;
};

string BestFirstSearch::search(Searchable<Point> *searchable) {
    vector<State<Point>> solution = bestFirstAlgo(searchable);
    if(solution.empty()){
        return "{}";
    }
    string path;
    string left = "left", right = "right", up = "up", down = "down";
    long i = solution.size()-1;
    int cost;
    for(; i > 0 ;i--){
        Point curr = solution[i].getState();
        Point next = solution[i-1].getState();
        cost = int(solution[i-1].getVal());
        if(isUp(next,curr)){
            path += up;
        }
        else if(isDown(next,curr)){
            path += down;
        }
        else if(isLeft(next,curr)){
            path += left;

        } else if(isRight(next,curr)){
            path += right;
        }
        path += "(" + to_string(cost) + ")" ",";
    }
    path = path.substr(0, path.size()-1);
    return path;
}



vector<State<Point>> BestFirstSearch::bestFirstAlgo(Searchable<Point> *matrix) {
  double (*f)(double, State<Point>, State<Point>) = this->lambda;
  MinHeap<State<Point>> frontier;
  vector<State<Point>> path;
  ClosedSet<State<Point>> closed;
  State<Point> starter = matrix->getInitialState();
  frontier.push(starter.getVal(), starter);
  while (!frontier.empty()) {
    tuple<double, State<Point>> deq = frontier.top();
    State<Point> *dequed = new State<Point>(get<1>(deq));
    double cost = dequed->getVal();
    frontier.remove(get<1>(deq));
    closed.insert(*dequed);
    if (matrix->isGoalState(*dequed)) {
      path.push_back(*dequed);
      State<Point> *parent = dequed->getParent();
      while (parent != nullptr) {
        path.push_back(*parent);
        parent = parent->getParent();
      }
      return path;
    } else {
      vector<State<Point>> succs = matrix->getAllPossibleStates(*dequed);
      for (State<Point> child : succs) {
        double h = f(cost, *dequed, child);
        if (((!frontier.contains(child)) && (!closed.contains(child)))) {
          child.setParent(dequed);
          frontier.push(h, child);
        } else if (frontier.contains(child)) {
          if (child.getVal() < get<1>(frontier.getItem(child)).getVal()) {
            frontier.remove(child);
            child.setParent(dequed);
            frontier.push(h, child);
          }
        } else if (closed.contains(child)) {
          if (child.getVal() < closed.get(child)->getVal()) {
            closed.remove(child);
            child.setParent(dequed);
            frontier.push(h, child);
          }
        }
      }
    }
  }
  return path;
}

bool BestFirstSearch::isUp(Point prev, Point curr) {
    int x1 = curr.getPair().first, x2 = prev.getPair().first;
    int y1 = curr.getPair().second, y2 = prev.getPair().second;
    return (x2 + 1 == x1) && (y1 == y2);
}

bool BestFirstSearch::isDown(Point prev, Point curr) {
    int x1 = curr.getPair().first, x2 = prev.getPair().first;
    int y1 = curr.getPair().second, y2 = prev.getPair().second;
    return (x2 - 1 == x1) && (y1 == y2);
}

bool BestFirstSearch::isLeft(Point prev, Point curr) {
    int x1 = curr.getPair().first, x2 = prev.getPair().first;
    int y1 = curr.getPair().second, y2 = prev.getPair().second;
    return (x2 == x1) && (y1 == y2 + 1);
}

bool BestFirstSearch::isRight(Point prev, Point curr) {
    int x1 = curr.getPair().first, x2 = prev.getPair().first;
    int y1 = curr.getPair().second, y2 = prev.getPair().second;
    return (x2 == x1) && (y1 == y2 - 1);
}



/**
 *
 * @param cost of path so far
 * @param a prev state
 * @param b child state
 * @return cost evaluation
 */
double costFunc(double cost, State<Point> a, State<Point> b) {
    double inf = numeric_limits<double >::infinity();
    if(cost == inf || a.getVal() == inf || b .getVal() == inf){
        return inf;
    }
    return a.getVal() + b.getState().getVal();
}
#endif //EX4__BESTFIRSTSEARCH_H_