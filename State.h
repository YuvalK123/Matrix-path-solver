//
// Created by yuval Kasner on 20/01/20.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_

#include "Point.h"
template <class T>
class State {
 private:
  double val = 0;
  T state{};
  State<T> *prevState = nullptr;
 public:
  /**
   * def constructor
   */
  explicit State<T>() = default;
  /**
   *
   * @param point state of state
   * @param value of state
   */
  explicit State<T>(T point, double value) : val(value),state(point) {}
  /**
 * copy constructor
 * @param elem to copy
 */
  explicit State<T>(State<T> *elem) : state(elem->getState()), val(elem->getVal()), prevState(elem->getParent()) {}
  State<T> &operator=(State<T> point) {
    this->state = point.getState();
    this->val = point.getVal();
    this->prevState = point.getParent();
    return *this;
  }
  /**
   * decrease states by states decrease.
   * @param point to dec from
   * @return new state
   */
  double operator-(State<T> point) { return this->state - point.getState(); }
  friend bool operator>(State<T> x, State<T> y) { return x.getVal() > y.getVal(); }
  friend bool operator<(State<T> x, State<T> y) { return x.getVal() < y.getVal(); }
  friend bool operator<=(State<T> x, State<T> y) { return x.getVal() <= y.getVal(); }
  friend bool operator==(State<T> x, State<T> y) { return x.getState() == y.getState(); }
  friend ostream &operator<<(ostream &os, State<T> &elem) {
    os << elem.getState();
    return os;
  }
  /**
   *
   * @param par parent of state
   */
  void setParent(State<T> *par) {
    this->prevState = par;
  }
  /**
   *
   * @return state's parent
   */
  State<T> *getParent() {
    return this->prevState;
  }
/**
 *
 * @return state
 */
  T getState() { return this->state; }
  /**
   *
   * @return value of state
   */
  double getVal() { return this->val; }

  string to_string(){return this->state.to_string();}
};

#endif //EX4__STATE_H_