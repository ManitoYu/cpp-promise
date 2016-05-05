#ifndef PROMISE_H
#define PROMISE_H

#include <functional>

template<typename T>
class Promise {
  public:
    typedef std::function<void (T)> Func;
    typedef std::function<void (Func, Func)> InitFunc;

    Promise(InitFunc func) {
      func(std::bind(&Promise::resolve, this, std::placeholders::_1), std::bind(&Promise::reject, this, std::placeholders::_1));
    }

    ~Promise() {

    }

    void resolve(T t) {
      value_ = t;
      status_ = 1;
    }

    void reject(T t) {
      error_ = t;
      status_ = 2;
    }

    void then(Func success, Func failure) {
      while (status_ != 1);
      if (status_ == 1) success(value_);
      if (status_ == 2) failure(error_);
    }

  private:
    int status_ = 0;
    T value_;
    T error_;
};

#endif // PROMISE_H
