#ifndef MEMENTO_H
#define MEMENTO_H
#include <time.h>

class Memento {
public:
    Memento();
    void start();
    void stop();
    double getSeconds();
private:
    double time;
    double begin;
};

#endif // MEMENTO_H
