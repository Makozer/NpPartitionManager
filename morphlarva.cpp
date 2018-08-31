#include "morphlarva.h"

MorphLarva::MorphLarva() {
    rng = new RNGesus();
    memoryStash = new VectorStash();

    rootStash = nullptr;
    solutionStash = new VectorStash();
    nsa = nullptr;

    success = false;
    goal = 0;
    strategy = 0;
}

    // Diese Funktion aus der GUI aufrufen zum starten der Berechnung!
bool MorphLarva::run() {

    // Abklappern ob startbereit
    if (rootStash == nullptr || nsa == nullptr) {
        nsa->add("Error", "run konnte nicht gestartet werden aufgrund nullptr");
        return false;
    } else {
        nsa->add("Start", "Berechnung wurde gestartet");
    }

    this->rootStash->quickSortDesc();
    this->setOverseer(this);
    this->success = false;


    // Damit der Schatz gerade ist !!! TODO!!!!
    quint16 wi = 1;
    while (this->rootStash->sum() % 2 > 0) {
        this->rootStash->addCoin(1);
        wi += 1;
        if (this->rootStash->sum() % 2 == 0) {
            nsa->add("Error", "Error! Schatz ungerade, es wurden weitere Münzen hinzugefügt.");
        }
    }

    this->setGoal(rootStash->sum() / 2);
    nsa->add("Data", "goal wurde auf " + QString::number(getGoal()) + " gesetzt");
    // SCHATZ BEGRADIGUNG ENDE

    search();
    return true;
}

void MorphLarva::setNSA(NSA *nsa) {
    this->nsa = nsa;
}


void MorphLarva::setRootStash(VectorStash *stash) {
    this->rootStash = stash;
}

void MorphLarva::setSolutionStash(VectorStash *stash) {
    this->success = true;
    this->solutionStash = stash;
}

VectorStash *MorphLarva::getSolutionStash() {
    return solutionStash;
}

void MorphLarva::setOverseer(MorphLarva *overseer) {
    this->overseer = overseer;
}

MorphLarva* MorphLarva::getOverseer() {
    return overseer;
}

bool MorphLarva::hasSuccess() {
    return success;
}

void MorphLarva::setStrategy(quint8 strategy) {
    this->strategy = strategy;
}

quint8 MorphLarva::getStrategy() {
    return strategy;
}

void MorphLarva::setGoal(quint16 goal) {
    this->goal = goal;
}

quint16 MorphLarva::getGoal() {
    return goal;
}

// DÖDÖDÖDÖDÖM WICHTIGSTE FUNKTION
void MorphLarva::search() {
    // ToDo
    nsa->add("Start", "search wurde gestartet");
    searchChaosRandom();

}

void MorphLarva::searchChaosRandom() {
    nsa->add("start", "searchChaosRandom gestartet");
    Coin* me = nullptr;
    quint16 loopmax = rootStash->size() - 1;
    VectorStash* rootCopy;
    //QString boolText = overseer->hasSuccess() ? "true" : "false";

    while (overseer->hasSuccess() != true) {

        rootCopy = new VectorStash((*rootStash)); // Kopiert den rootStash

        for (int i = 0; i < loopmax; i++) {

            me = rootCopy->takeCoinByRNG();
            memoryStash->addCoin(me);
            //delete me;
            if (memoryStash->sum() > goal) {
                memoryStash->clear();
                delete rootCopy;
                break;
            }
            if (memoryStash->sum() == goal) {
                overseer->setSolutionStash(this->memoryStash);
                nsa->add("finish","searchChaosRandom war Erfolgreich!");
                break;
            } // End Success = True
        } // End for
    } // End while
}

