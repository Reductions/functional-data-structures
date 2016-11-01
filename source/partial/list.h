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

    class proxy {
      friend list;
      list* in;
      node** to;

      proxy(node* _to, list* _in){
        in = _in;
        to = new node*(_to);
      }
    public:
      int64 operator= (const T& data){
        return (*in).update_at(*this, data);
      }

      ~proxy(){
        *to = nullptr;
        delete to;
      }
    };

    struct list_root{
      node* root;
      int64 size;
    };

    vector<pair<node*, int64>> timeline;
    vector<proxy> given;

  public:
    list(){
      timeline.push_back(pair(nullptr, 0));
    }

    //update

    int64 push(const T& data){
      auto last = timeline.back();
      auto root = new node(data, last.first, nullptr);
      last.first->back = root;
      timeline.push_back({root, last.second + 1});
      given.clear();
      return timeline.size();
    }

    int64 pop(){
      auto last = timeline.back();
      auto root = last.first->next;
      root->back = nullptr;
      timeline.push_back({root, last.second - 1});
      given.clear();
      return timeline.size();
    }

    int64 update_at(const proxy& at, const T& data){
      
    }

    //query

    int64 size(){
      return timeline.back().second;
    }

    int64 size(int64 version){
      return timeline[version].second;
    }

    //deleted methods and constructors

    list(const list<T>&) = delete;
    list<T>& operator= (const list<T>&) = delete;
  };
}
