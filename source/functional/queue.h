#pragma once

#include "lazy.h"
#include "flow.h"

namespace fds{
  template <class T>
  struct queue{
    fds::flow<T> in;
    int size_in;
    fds::flow<T> out;
    int size_out;

    queue(list<T> _in = empty_flow<T>(), _size_in = 0,
          list<T> _out = empty_flow<T>(), _size_out = 0)
    {
      if (_size_in >= _size_out){
        size_in = _size_in;
        size_out = _size_out;
        in = _in;
        out = out;
      }
      else {
        size_in = 0;
        size_out = _size_in + _size_out;
        in = empty_flow();
        out = append(_out, reverse(_out));
      }
    }
  };

  template <class T>
  queue<T> empty_queue(){
    return queue<T>();
  };

  template <class T>
  bool empty (queue<T> q){
    return size_in == 0 && size_out == 0;
  }

  template <class T>
  queue<T> push(queue<T> q, T item){
    return queue(cons(item, q.in), q.size_in + 1, q.out , q.size_out);
  }

  template <class T>
  T front(queue<T> q){
    return head(q.out);
  }

  template <class T>
  queue<T> pop(queue<T>& q){
    return queue(q.in, q.size_in, tail(q.out), q.size_out - 1);
  }
}

template<class T>
ostream& operator<< (ostream& out, fds::queue<T> q){
  out<<"{\n"<<" ->"<<q.in<<"\n <-"<<q.out<<"\n}";
  return out;
}
