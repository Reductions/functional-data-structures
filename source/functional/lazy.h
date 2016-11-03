#pragma once

#include <iostream>
#include <functional>
#include <memory>

template<typename T>
class lazy{
  std::function<T()> delayed;
  std::shared_ptr<T> value;
  std::shared_ptr<bool> memoaized;
public:
  lazy(std::function<T()> delayed)
    :delayed(delayed),
     value(std::make_shared<T>()),
     memoaized(std::make_shared<bool>(false)) {}

  T operator ()() {
    if (!*memoaized) {
      *value =delayed();
      *memoaized = true;
    }
    return *value;
  }
};
