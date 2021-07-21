#pragma once
#include "Base.hpp"

namespace jzj {

#define JZJQUICKIMPLEMENT(x) int main(int argc, const char * argv[]){x JZJAPPOBJECT;JZJAPPOBJECT.run();return 0;} 

class GameApp : public Base {
public:
    GameApp() : isRunning(true) {}
    ~GameApp() {}
    void run() {
        init();
        while(isRunning) {
            loop();
        }
        exit();
    }
protected:
    virtual void init() = 0;
    virtual void loop() = 0;
    virtual void exit() = 0;
    bool isRunning;
};
}

