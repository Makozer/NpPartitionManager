#include "morphlarva.h"

MorphLarva::MorphLarva() {
    rng = new RNGesus();
}

void MorphLarva::run() {
    // ToDo :)
}

void MorphLarva::setRootStash(VectorStash *stash) {
    this->rootStash = stash;
}

void MorphLarva::setSolutionStash(VectorStash *stash) {
    this->solutionStash = stash;
}

void MorphLarva::setNSA(NSA *nsa) {
    this->nsa = nsa;
}
