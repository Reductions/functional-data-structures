#pragma once

#include <iostream>
#include <memory>

#include "lazy.h"

template <class T>
struct flow_node;

namespace fds
{
  template <class T>
  using flow = lazy<std::shared_ptr<flow_node<T>>>;

  template <class T>
  flow<T> empty_flow() {
    static auto ret = flow<T>([](){ return std::shared_ptr<flow_node<T>>(nullptr); });
    return ret;
  }

  template <class T>
  bool empty(flow<T> F){
    return !(F());
  }

  template <class T>
  flow<T> cons(T data, flow<T> F){
    return flow<T>([data, F](){
        return std::make_shared<flow_node<T>>(data, F); });
  }

  template <class T>
  T head (flow<T> F){
    return F()->head;
  }

  template <class T>
  flow<T> tail (flow<T> F){
    return F()->tail;
  }

  template <class T>
  flow<T> append (flow<T> first, flow<T> second){
    if(empty(first)){
      return second;
    }
    return cons(head(first),
                flow<T>([=](){ return append(tail(first), second)(); }));
  }

  template <class T>
  flow<T> reverse (flow<T> F){
    struct local{
      flow<T> helper(flow<T> F, flow<T> rev){
        if (empty(F)){
          return rev;
        }
        return helper(tail(F), cons(head(F), rev));
      }
    };
    return flow<T>([=](){ return local::helper(F, empty_flow()); })
  }
}

template <class T>
std::ostream& operator<< (std::ostream& out, fds::flow<T> F){
  out<<"(";
  if (F){
    out<<fds::head(F);
    F = fds::tail(F);
    while(F){
      out<<" ";
      out<<fds::head(F);
      F = fds::tail(F);
    }
  }
  out<<")";
  return out;
}

template <class T>
struct flow_node
{
  T head;
  fds::flow<T> tail;
  flow_node(T head, fds::flow<T> tail):
    head(head),
    tail(tail) {}
};
