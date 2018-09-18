/* Memento moriendum esse
 * Klasse, die als Stopuhr bzw Timer eingesetzt wird.
 * https://www.youtube.com/watch?v=U7-60tyLQhA
 */
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
