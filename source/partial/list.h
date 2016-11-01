#pragma once

#include <vector>

#ifndef int64
#define int64 long long
#endif

using std::vector;

namespace ppds
{
  template <class T>
  class list
  {
    enum change_type {
      no_change,
      next_change,
      data_change
    };

    struct node;

    struct change {
      union change_value {
        int64 revision;
        node* next;
        T data;
        change_value(node* next = nullptr):
          revision(-1), next(next) {}
        change_value(const T& = data):
          revision(-1), data(data) {}
      };

      change_type type;
      change_value value;

      chnage():
        type(no_change){}

      chnage(const T& value):
        type(data_change), value(value){}

      chnage(node* value):
        type(next_change), value(value){
      }
    };

    struct node {
      node* next;
      T data;
      node* back;
      change change_set[2];

      node(const T& data, node* next, node* back):
        data(data), next(next), back(back) {}
    };

    vector<pair<node*, int64>> timeline;

  public:
    list(){
      timeline.push_back(pair(nullptr, 0));
    }
  };
}
