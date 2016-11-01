#pragma once

#include <iostream>
#include <memory>
#include <list>

using std::ostream;

template <class T>
struct list_node;

namespace fds
{
  template <class T>
  using list = std::shared_ptr<const list_node<T>>;

  template <class T>
  const list<T> empty_list(nullptr);

  template <class T>
  bool empty(list<T> l) {
    return !l;
  }

  template <class T>
  list<T> cons(T data, list<T> list){
    return list<T>(new list_node<T>(data, l));
  }

  template <class T>
  T head (list<T> l){
    return l->head;
  }

  template <class T>
  list<T> tail (list<T> l){
    if (l)
      return l->tail;
    return l;
  }

  template <class T>
  list<T> reverse (list<T> l){
    struct local{
      static list<T> helper(list<T> l, list<T> rev){
        if(!l){
          return rev;
        }
        return helper(tail(l), (head(l), rev));
      }
    };
    return local::helper(l, empty_list<T>);
  }

  template <class T>
  list<T> append (list<T> first, list<T> second){
    if(!first){
      return second;
    }
    return (head(first), append(tail(first), second));
  }
}

template <class T>
fds::list<T> operator, (T data, fds::list<T> l){
  return fds::list<T>(new list_node<T>(data, l));
}

template <class T>
fds::list<T> operator|= (T data, fds::list<T> l){
  return fds::list<T>(new list_node<T>(data, l));
}

template <class T>
std::ostream& operator<< (std::ostream& out, fds::list<T> l){
  out<<"(";
  if (l){
    out<<fds::head(l);
    l = fds::tail(l);
    while(l){
      out<<" ";
      out<<fds::head(l);
      l = fds::tail(l);
    }
  }
  out<<")";
  return out;
}

template <class T>
struct list_node
{
  T head;
  fds::list<T> tail;
  list_node(T head, fds::list<T> tail):
    head(head),
    tail(tail) {}
};
