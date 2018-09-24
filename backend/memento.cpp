#include "memento.h"

Memento::Memento() {

}

void Memento::start() {
    time = 0.0;
    begin = clock();
}

void Memento::stop() {
    time += clock() - begin;
    time = time / CLOCKS_PER_SEC;
}

double Memento::getSeconds() {
    time += clock() - begin;
    time = time / CLOCKS_PER_SEC;
    return time;
}
