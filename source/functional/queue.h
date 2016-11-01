#pragma once

#include "lazy.h"
#include "list.h"

namespace fds{
  template <class T>
  struct queue{
    fds::list<T> in;
    fds::list<T> out;
    lazy<list<T>> reverser;

    queue(list<T> in = empty_list<T>, list<T> out = empty_list<T>):
      in(in),
      out(out),
      reverser(lazy<list<T>>([in](){
            return reverse(in);
          })) {}
  };

  template <class T>
  const queue<T> empty_queue(empty_list<T>, empty_list<T>);

  template <class T>
  bool empty (queue<T> q){
    return empty(q.in) && empty(q.out);
  }

  template <class T>
  queue<T> push(queue<T> q, T el){
    queue<T> new_queue = q;
    if (empty(q)){
      return queue<T>(q.in, (el, q.in));
    } else {
      return queue<T>((el, q.in), q.out);
    }
  }

  template <class T>
  T front(queue<T> q){
    return head(q.out);
  }

  template <class T>
  queue<T> pop(queue<T>& q){
    queue<T> new_queue = q;
    if(empty(tail(q.out))){
      return queue<T>(empty_list<T>, q.reverser());
    } else {
      return queue<T>(q.in, tail(q.out));
    
  }
}

template<class T>
ostream& operator<< (ostream& out, fds::queue<T> q){
  out<<"{\n"<<" ->"<<q.in<<"\n <-"<<q.out<<"\n}";
  return out;
}
