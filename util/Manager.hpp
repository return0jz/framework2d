#pragma once
#include "Base.hpp"
#include <stack>

namespace jzj {
class Manager {
public:
    Manager() {}
    ~Manager() {
        while (!this->stackRecord.empty()) {
            delete stackRecord.top();
            stackRecord.pop();
        }
    }
    template <typename T> T *manage(T * const p) {
        stackRecord.push(dynamic_cast<Base*>(p));
        return p;
    }
private:
    std::stack<jzj::Base *> stackRecord;
};
}
