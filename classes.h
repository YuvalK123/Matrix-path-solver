//
// Created by yuval Kasner on 13/01/20.
//

#ifndef EX4__CLASSES_H
#define EX4__CLASSES_H
#include <iostream>
#include <queue>
#include <utility>
#include "set"
#include "unordered_map"
#include "Searchable.h"
using namespace std;



template <class T>
class minHeap{
private:
    set<tuple<double,T>> priorityQ;

public:
    T getItem(T obj){
        auto it = this->priorityQ.cbegin();
        auto end = this->priorityQ.end();
        while (it != end) {
            T tmp = get<1>((*it));
            if (tmp == obj) {
                return get<1>((*it));
            }
            it++;
        }
    }

    explicit minHeap() = default;
    /**
     * remove element from minheap
     * @param obj to remove
     */
    void remove(T obj);
    /**
     *
     * @return min value of minHeap(the top)
     */
    tuple<double,T> top(){
        tuple<double,T> e = (*(this->priorityQ.begin()));
        return {get<0>(e),get<1>(e)};
    }
    /**
     * remove the top of min heap.
     */
    void pop(){this->priorityQ.erase(*(this->priorityQ.begin()));}
    /**
     *
     * @param obj to push to heap
     */
    void push(double priority,T obj){this->priorityQ.insert({priority,obj});}
    /**
     *
     * @return true if empty, false otherwise
     */
    bool empty(){ return this->priorityQ.empty();}
    /**
     *
     * @param obj to get value of
     * @return the value of T
     */
    double operator[](T obj);
    /**
     *
     * @param obj to check if contains
     * @return true if contains. false otherwise
     */
    bool contains(T obj);
};

template<class T>
void minHeap<T>::remove(T obj) {
    this->priorityQ.erase({operator[](obj),obj});

}

template<class T>
bool minHeap<T>::contains(T obj) {
    auto it = this->priorityQ.begin();
    auto end = this->priorityQ.end();
    while(it != end){
        T tmp = get<1>(*it);
        if(obj == tmp){
            return true;
        }
        it++;
    }
    return false;
//    try{
//        double h = operator[](obj);
//        return true;
//    }
//    catch (const char* e){
//        return false;
//    }
}
template<class T>
double minHeap<T>::operator[](T obj) {
    auto it = this->priorityQ.cbegin();
    auto end = this->priorityQ.end();
    while (it != end) {
        T tmp = get<1>((*it));
        if (tmp == obj) {
            return get<0>((*it));
        }
        it++;
    }
    throw "invalid obj ";
}




class matrix: public Searchable<Point> {
private:
    vector<vector<double>> mat;
    State<Point> start;
    State<Point> goal;

    /**
     *
     * @tparam N rows number
     * @tparam M colls number
     * @param str to get row or coll
     * @return row number or coll number of matrix
     */
    template<unsigned N, unsigned M>
    int getRowColl(double (&)[N][M], const string &str = "a");
public:
    explicit matrix() = default;
//  explicit matrix(double *mat[]);
    ~matrix() override = default;
    /**
     * constructor
     * @param m matrix to put
     */
    explicit matrix(vector<vector<double>> m);
    /**
     *
     * @return size of matrix
     */
    intPair getSize() { return {this->mat.size(), this->mat[0].size()}; }
    /**
     *
     * @return goal of problem
     */
    State<Point> getGoal() { return this->goal; }
    bool isGoalState(State<Point> element) override{return this->goal == element;}

    State<Point> getInitialState() override{
        return this->start;
    };

    vector<State<Point>> getAllPossibleStates(State<Point> state) override;
    /**
     *
     * @param line to add to matrix
     */
    void addLine(vector<double> line);
    /**
     *
     * @param start of problem
     * @param goal of problem
     */
    void setProblem(State<Point> start, State<Point> goal);
    /**
     *
     * @return size of matrix
     */
    intPair size() {
        int rows = this->mat.size();
        int colls = this->mat[0].size();
        return {rows, colls};
    }

    /**
     *
     * @param pair to get state from point
     * @return state of point
     */
    State<Point> get(Point pair);
};




void matrix::setProblem(State<Point> s,State<Point> g){
    this->start = s;
    this->goal = g;
}


//matrix::matrix(Point **mat) {
//  int rows = this->getRowColl(mat), colls = this->getRowColl(mat,"b");
//  for (int i = 0; i < rows; i++){        //creating row
//    this->mat.push_back(vector<Point>());
//  }
//
//  for (int n = 0; n < rows; n++){
//    for (int m = 0; m < colls; m++){
//      this->mat[m].push_back("");
//    }
//  }
//  for (int m = 0; m < colls; m++){
//    for (int n = 0; n < rows; n++){
//      this->mat[m][n] = mat[m][n];
//    }
//  }
//}

State<Point> matrix::get(Point pair) {
    intPair int_pair = pair.getPair();
    int i = int_pair.first, j = int_pair.second;
    if( i > this->mat.size() && j > this->mat[i].size()){
        throw "runtime err";
    }

    State<Point> elem(Point(i,j,this->mat[i][j]),this->mat[i][j]);
    return elem;
}

vector<State<Point>> matrix ::getAllPossibleStates(State<Point> state) {
    intPair ind = state.getState().getPair();
    double placement;
    double inf = numeric_limits<double >::infinity();
    int first = ind.first, second = ind.second;
    vector<State<Point>>  succ;
    if(first != 0){
        placement = this->mat[first-1][second];
        if(placement != inf){
            Point upper(first-1,second,this->mat[first-1][second]);
            State<Point> up(upper,upper.getVal() + state.getVal());
            succ.push_back(up);
        }

    }
    if(first != this->mat.size()-1){
        placement = this->mat[first+1][second];
        if(placement != inf) {
            Point downer(first + 1, second, this->mat[first + 1][second]);
            State<Point> down(downer, downer.getVal() + state.getVal());
            succ.push_back(down);
        }
    }
    if(second != 0){
        placement = this->mat[first][second-1];
        if(placement != inf) {
            Point lefter(first, second - 1, this->mat[first][second - 1]);
            State<Point> left(lefter, lefter.getVal() + state.getVal());
            succ.push_back(left);
        }
    }
    if(second != this->mat[first].size()-1){
        placement = this->mat[first][second+1];
        if(placement != inf) {
            Point righter(first, second + 1, this->mat[first][second + 1]);
            State<Point> right(righter, righter.getVal() + state.getVal());
            succ.push_back(right);
        }
    }
    return succ;
}


matrix::matrix(vector<vector<double>> m) {
    long size = m.size();
    for(long i =0; i < size;i++){
        long inSize = m[i].size();
        vector<double> inner;
        for(long j = 0;j<inSize;j++){
            inner.push_back(m[i][j]);
        }

        this->mat.push_back(inner);
    }
}

template<unsigned int N, unsigned int M>
int matrix::getRowColl(double (&)[N][M], const string &str) {
    if (str == "a") {
        return N;
    }
    return M;
}

void matrix::addLine(vector<double> line) {
    this->mat.push_back(line);
}

#endif //EX4__CLASSES_H