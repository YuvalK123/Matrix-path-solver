//
// Created by yuval Kasner on 30/01/20.
//

#ifndef EX4__POINT_H_
#define EX4__POINT_H_
#include "ostream"
#include "iostream"
#include "vector"
using namespace std;

typedef pair<int,int> intPair;

template <class T>
class ClosedSet{
 private:
  vector<T> closedSet;
 public:
  ~ClosedSet() = default;
  void remove(T obj){
    auto it = this->closedSet.begin();
    auto end = this->closedSet.end();
    while (it != end){
      if ((*it) == obj){
        this->closedSet.erase(it);
        return;
      }
      it++;
    }
  }

  /**
   * constructor
   */
  ClosedSet() = default;
  /**
   *
   * @param obj to return from set
   * @return object from set
   */
  T* get(T obj){
    auto it = this->closedSet.begin();
    auto end = this->closedSet.end();
    while (it != end){
      if ((*it) == obj){
        return &(*it);
      }
      it++;
    }
    return nullptr;
  }
/**
 *
 * @param obj to check
 * @return true if set contains, false otherwise.
 */
  bool contains(T obj){
    auto it = this->closedSet.begin();
    auto end = this->closedSet.end();
    while (it != end){
      T tmp = *it;
      if (tmp == obj){
        return true;
      }
      it++;
    }
    return false;
  }
  /**
   *
   * @param obj to insert
   */
  void insert(T obj){
    if(!contains(obj)) {
      this->closedSet.push_back(obj);
    }
  }
};

class Point{
 private:
  int x;
  int y;
  double value = 0;
 public:
  ~Point() = default;
  /**
   *
   * @return this point's value
   */
  double getVal(){ return this->value;}
  /**
   *
   * @param point to set this point by.
   */
  void setPoint(Point point){
    this->x = point.getPair().first;
    this->y = point.getPair().second;
  }
  /**
   * constructor
   */
  explicit Point() = default;
  /**
   *
   * @param a  x value
   * @param b y value
   * @param val value of point
   */
  explicit Point(int a, int b, double val): x(a), y(b), value(val){}
  /**
   *
   * @return x,y of point
   */
  intPair getPair() const { return  {this->x, this->y};}
  /**
   *
   * @param point to decrease from
   * @return dist
   */
  double operator -(Point point){
    intPair pair = point.getPair();
    int a = this->x - pair.first;
    int b = this->y - pair.second;
    return abs(a) + abs(b);
  }
  friend bool operator ==(Point a,Point b){
    intPair pointA = a.getPair();
    intPair pointb = b.getPair();
    return ((pointA.first == pointb.first) && (pointA.second == pointb.second));
  }
  Point& operator =(Point point){
    intPair pair = point.getPair();
    this->x = pair.first;
    this->y = pair.second;
    return *this;
  }
  friend ostream& operator<<(ostream& os, const Point& point)
  {
    intPair pair = {point.x,point.y};
    os << "(" << pair.first << "," << pair.second << ")";
    return os;
  }

  string to_string(){
    string s = "("+ std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    return s;
  }
};


#endif //EX4__POINT_H_
