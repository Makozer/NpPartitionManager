/* Memento moriendum esse
 * Klasse, die als Stopuhr bzw Timer eingesetzt wird.
 * https://www.youtube.com/watch?v=U7-60tyLQhA
 * Zuständigkeit: Martin
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
    double time;                                 // Gespeicherte Zeitdauer
    double begin;                                // Wann die Messung began
};

#endif // MEMENTO_H
