//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_
#include "Searcher.h"
#include "classes.h"
#include "stack"
template <class T>
class dfs: public Searcher<Point,string>{
private:
    intPair size;
    Searchable<Point> *matrix = nullptr;
    vector<State<T>> generatePath(State<T> dequed);
    bool isLeft(Point prev, Point curr);
    bool isRight(Point prev, Point curr);
    bool isUp(Point prev, Point curr);
    bool isDown(Point prev, Point curr);
public:
  ~dfs() override = default;
    explicit dfs(intPair graphS):size(graphS){}
    string search(Searchable<Point> *searchable) override ;
    vector<State<Point>> dfsSearch(State<Point> start, vector<vector<double>> discovered);
};

template<class T>
vector<State<T>> dfs<T>::generatePath(State<T> dequed){
    vector<State<T>> path;
    State<T> *parent = dequed.getParent();
    path.push_back(dequed);
    while (parent != nullptr){
        path.push_back(*parent);
        parent = parent->getParent();
    }
    return path;
}

template<class T>
string dfs<T>::search(Searchable<Point> *searchable) {
    this->matrix = searchable;
    double inf = numeric_limits<double >::infinity();
    vector<vector<double >> discovered;
    for(int i = 0; i <size.first; i++){
        vector<double> inner;
        for (int j = 0; j < size.second;j++){
            inner.push_back(inf);
        }
        discovered.push_back(inner);
    }
    vector<State<T>> solution = dfsSearch(searchable->getInitialState(),discovered);
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
  cout<<endl<<path<<endl;
  return path;
}
#endif //EX4__DFS_H_
template<class T>
vector<State<Point>> dfs<T>:: dfsSearch(State<Point> start, vector<vector<double>> discovered) {
    vector<State<Point>> path;
    if (matrix->isGoalState(start)) {
        path.push_back(start);
        return path;
    }
    stack<State<Point>> s;
    s.push(start);
    discovered[start.getState().getPair().first][start.getState().getPair().second] = start.getVal();
    while (!s.empty()) {
        State<Point> *curr = new State<T>(s.top());
        s.pop();
        intPair currentPair = curr->getState().getPair();
        vector<State<Point>> succs = matrix->getAllPossibleStates(*curr);
        for (State<Point> child :succs) {
            intPair childPair = child.getState().getPair();
            double currDist = discovered[currentPair.first][currentPair.second];
            if (discovered[childPair.first][childPair.second] > currDist + child.getVal()) {
                discovered[childPair.first][childPair.second] = currDist + child.getVal();
                if (matrix->isGoalState(child)) {
                    child.setParent(curr);
                    path = generatePath(child);
                    return path;
                }
                child.setParent(curr);
                s.push(child);
            }
        }
    }
}

template<class T>
bool dfs<T>::isUp(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 + 1 == x1) && (y1 == y2);
}
template<class T>
bool dfs<T>::isDown(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 - 1 == x1) && (y1 == y2);
}
template<class T>
bool dfs<T>::isLeft(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 == x1) && (y1 == y2 + 1);
}
template<class T>
bool dfs<T>::isRight(Point prev, Point curr) {
  int x1 = curr.getPair().first, x2 = prev.getPair().first;
  int y1 = curr.getPair().second, y2 = prev.getPair().second;
  return (x2 == x1) && (y1 == y2 - 1);
}