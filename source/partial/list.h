#pragma once

#include <vector>
#include <memory>

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
      no_change = 0,
      next_change,
      data_change
    };

    struct node;

    struct change {
      union change_value {
        node* next;
        T data;
        change_value(node* next = nullptr):
          next(next) {}
        change_value(const T&):
          data(data) {}
      };


      int64 revision;
      change_type type;
      change_value value;

      change():
        type(no_change){}

      change(const T& value, int64 revision):
        type(data_change), value(value), revision(revision){}

      change(node* value, int64 revision):
        type(next_change), value(value), revision(revision){}

      void operator()(node*& next, T& data, int64 version) {
        if(revision <= version){
          if (type == next_change){
            next = value.next;
          } else if (type == data_change){
            data = value.data;
          }
        }
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

    struct list_root{
      node* root;
      int64 size;
    };

    vector<list_root> timeline;

  public:
    list(){
      timeline.push_back(list_root{nullptr, 0});
    }

    //update

    int64 push(const T& data){
      auto last = timeline.back();
      auto root = new node(data, last.root, nullptr);
      if (last.root){
        last.root->back = root;
      }
      timeline.push_back({root, last.size + 1});
      return timeline.size() - 1;
    }

    int64 pop(){
      auto last = timeline.back();
      auto root = last.root->next;
      if (root){
        root->back = nullptr;
      }
      timeline.push_back({root, last.size - 1});
      return timeline.size() - 1;
    }

    int64 update_first_found(const T& old_data, const T& new_data){
      auto current = timeline.back().root;
      auto next = current->next;
      auto data = root->data;
      auto version = timeline.size() - 1;
      while (current){
        current->change_set[0](next, data, version);
        current->change_set[1](next, data, version);
        if (data == item){
          break;
        }
        current = next;
      }
      if (current) {
        if(current->change_set[0] == no_change){
          current->change_set[0] = change(data, timeline.size());
          timeline.push_back(timeline.back());
        }
        else if (current->change_set[0] == no_change){
          current->change_set[1] = change(data, timeline.size());
          timeline.push_back(timeline.back());
        }
        else {
          // TODO
        }
      }
    }

    //query

    int64 size() const{
      return timeline.back().size;
    }

    int64 size(int64 version) const{
      return timeline[version].size;
    }

    int64 versions() const{
      return timeline.size();
    }

    bool has(int64 version, const T& item){
      auto root = timeline[version].root;
      while (root){
        auto next = root->next;
        T data = root->data;
        root->change_set[0](next, data, version);
        root->change_set[1](next, data, version);
        if (data == item){
          return true;
        }
        root = next;
      }
      return false;
    }

    //deleted methods and constructors

    list(const list<T>&) = delete;
    list<T>& operator= (const list<T>&) = delete;
  };
}
