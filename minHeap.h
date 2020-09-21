//
// Created by yuval Kasner on 01/02/20.
//

#ifndef EX4__MINHEAP_H_
#define EX4__MINHEAP_H_

#include "classes.h"
template <class T>
class MinHeap{
 private:
  vector<tuple<double,T>> priorityQ;

 public:
  ~MinHeap() = default;

  tuple<double,T> getItem(T obj){
    auto it = this->priorityQ.cbegin();
    auto end = this->priorityQ.end();
    while (it != end) {
      T tmp = get<1>((*it));
      if (tmp == obj) {
        return *it;
      }
      it++;
    }
    return tuple<double,T>();
  }

  explicit MinHeap() = default;
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
    tuple<double,T> e = find_lowest_cost();
    return e;
  }
  /**
   * remove the top of min heap.
   */
  void pop(){remove(top());}
  /**
   *
   * @param obj to push to heap
   */
  void push(double priority,T obj){this->priorityQ.push_back({priority,obj});}
  /**
   *
   * @return true if empty, false otherwise
   */
  bool empty(){
    return this->priorityQ.size() == 0;
  }
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
  tuple<double,T> find_lowest_cost();
};

template <class T>
tuple<double,T> MinHeap<T>::find_lowest_cost() {
  double inf = numeric_limits<double >::infinity();
  tuple<double,T> ret;
  auto it = this->priorityQ.cbegin();
  auto end = this->priorityQ.cend();
  double tmp = inf;
  while(it != end){
    if(get<0>(*it) < tmp ){
      tmp = get<0>(*it);
      ret = *it;
    }
    it++;
  }
  return ret;
}
template<class T>
bool MinHeap<T>::contains(T obj) {
  try{
    operator[](obj);
    return true;
  }
  catch (const char* e){
    return false;
  }
}
template<class T>
double MinHeap<T>::operator[](T obj) {
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
template<class T>
void MinHeap<T>::remove(T obj) {
  auto it = this->priorityQ.cbegin();
  auto end = this->priorityQ.end();
  while (it != end) {
    T tmp = get<1>((*it));
    if (tmp == obj) {
      this->priorityQ.erase(it);
      return;
    }
    it++;
  }
  return;
}

#endif //EX4__MINHEAP_H_
