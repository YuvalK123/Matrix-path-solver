//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_
#include "Searcher.h"
#include "classes.h"

template <class T>
class bfs: public Searcher<Point,string>{
private:
  ~bfs() override = default;
    intPair size;
    vector<State<T>> generatePath(State<T> dequed);
    vector<State<T>> bfsSearch(State<Point> start,Searchable<Point> *matrix);
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
public:
  /**
   * constructor
   * @param s size of searchable
   */
    explicit bfs(intPair s): size(s){}
  /**
   *
   * @param searchable struct to find solution to
   * @return solution for problem
   */
    string search(Searchable<T> *searchable) override ;

};
template<class T>
vector<State<T>> bfs<T>::bfsSearch(State<Point> start, Searchable<Point> *matrix) {
    vector<vector<double >> discovered;
    double inf = numeric_limits<double >::infinity();
    for(int i = 0; i <size.first; i++){
        vector<double> inner;
        for (int j = 0; j < size.second;j++){
            inner.push_back(inf);
        }
        discovered.push_back(inner);
    }
    State<T> *dest = nullptr;
    queue<State<T>> Q;
    vector<State<T>> path;
    cout<<start.getVal()<<endl;
    discovered[start.getState().getPair().first][start.getState().getPair().second] = start.getVal();
    Q.push(start);
    while (!Q.empty()){
        auto *current = new State<T>(Q.front());
      Q.pop();
        vector<State<T>> succs = matrix->getAllPossibleStates(*current);
        for(State<T> child : succs){
            intPair childPair = child.getState().getPair();
            double toCheck = child.getVal();
            double currDist = discovered[childPair.first][childPair.second];
            if(toCheck != inf && currDist >= toCheck){
                discovered[childPair.first][childPair.second] = toCheck;
                child.setParent(current);
                if(matrix->isGoalState(child)){
                  delete dest;
                    dest = new State<T>(child);
                    dest->setParent(current);
                }
                Q.push(child);
            }
        }
    }
    if(dest == nullptr){
        return vector<State<T>>();
    }
    path = generatePath(*dest);
    return path;
}
template<class T>
string bfs<T>::search(Searchable<T> *searchable) {

  vector<State<T>> solution = bfsSearch(searchable->getInitialState(), searchable);
  if (solution.empty()) {
    return "";
  }
  string path;
  string left = "left", right = "right", up = "up", down = "down";
  long i = solution.size() - 1;
  int cost;
  for (; i > 0; i--) {
    Point curr = solution[i].getState();
    Point next = solution[i - 1].getState();
    cost = int(solution[i-1].getVal());
    if (isUp(next, curr)) {
      path += up;
    } else if (isDown(next, curr)) {
      path += down;
    } else if (isLeft(next, curr)) {
      path += left;

    } else if (isRight(next, curr)) {
      path += right;
    }
    path += "(" + to_string(cost) + ")" ",";
  }
  path = path.substr(0, path.size() - 1);
  cout << endl << path << endl;
  return path;
}


template<class T>
bool bfs<T>::isUp(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 + 1 == x1) && (y1 == y2);
}
template<class T>
bool bfs<T>::isDown(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 - 1 == x1) && (y1 == y2);
}
template<class T>
bool bfs<T>::isLeft(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 == x1) && (y1 == y2 + 1);
}
template<class T>
bool bfs<T>::isRight(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 == x1) && (y1 == y2 - 1);
}

template<class T>
vector<State<T>> bfs<T>::generatePath(State<T> dequed){
  cout<<dequed<<dequed.getVal()<<endl;
    vector<State<T>> path;
    State<T> *parent = dequed.getParent();
    path.push_back(dequed);
    while (parent != nullptr){
        path.push_back(*parent);
        parent = parent->getParent();
    }
    return path;
}

#endif //EX4__BFS_H_