#include "morphlarva.h"

MorphLarva::MorphLarva() {
    rng = new RNGesus();
}

void MorphLarva::run() {
    // keine Sorge, kommt noch, am Ende wird nichts anderes passieren, als dass der solution Stash halt inhalt hat und das wars für die GUI ;D
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
