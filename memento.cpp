#include "memento.h"

Memento::Memento() {

}

void Memento::start() {
    time = 0.0;
    begin = clock();
}

void Memento::stop() {
    time += clock() - begin;
    time = time / CLOCKS_PER_SEC;  // rescale to seconds
}

double Memento::getSeconds() {
    return time;
}
