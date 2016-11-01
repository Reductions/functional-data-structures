#pragma once

#include <functional>

template<typename T>
class lazy{
  std::function<T()> delayed;
  T value;
  bool memoaized;
public:
  lazy(std::function<T()> initiator)
    :delayed(initiator),
     memoaized(false) {}

  lazy<T>& operator=(const lazy<T>& other) {
    delayed = other.delayed;
    memoaized = false;
    return *this;
  }

  T& get() {
    if (!memoaized) {
      value = delayed();
      memoaized = true;
    }
    return value;
  }

  T& operator ()() {
    return get();
  }
};
