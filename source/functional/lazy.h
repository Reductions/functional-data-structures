#pragma once

#include <functional>

template<typename T>
class lazy{
  std::function<T()> delayed;
  T value;
  bool memoaized;
public:
  lazy(std::function<T()> delayed)
    :delayed(delayed),
     memoaized(false) {}

  lazy<T>& operator=(const lazy<T>& other) {
    delayed = other.delayed;
    memoaized = false;
    return *this;
  }

  T& operator ()() {
    if (!memoaized) {
      value = delayed();
      memoaized = true;
    }
    return value;
  }
};
