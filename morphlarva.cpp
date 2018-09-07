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

MorphLarva::MorphLarva(const MorphLarva &copyLarva) {
    this->overseer = copyLarva.overseer;
    this->rootStash = new VectorStash(*copyLarva.rootStash);
    this->memoryStash = new VectorStash();
    this->nsa = copyLarva.nsa;
    this->rng = new RNGesus();
    this->success = copyLarva.success;
    this->goal = copyLarva.goal;
    this->strategy = copyLarva.strategy;
}

void mt_search(MorphLarva &worker) {
    qDebug("mt_search wurde ausgeführt");
    worker.search();
}

    // Diese Funktion aus der GUI aufrufen zum starten der Berechnung!
bool MorphLarva::runCalc() {

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


    // Multi Threading ########################################################################

    quint8 num_threads = 1;
    quint8 strat[] = { 1, 1 };
    QString qds = "goal wurde auf " + QString::number(getGoal()) + " gesetzt";
    qDebug() << qds;
    qDebug("worker werden gestartet");
    for (quint8 i = 0; i < num_threads; i++) {
        worker[i] = new MorphLarva();
        worker[i]->setOverseer(this);
        worker[i]->setGoal(this->getGoal());
        worker[i]->setStrategy(strat[i]);
        worker[i]->setRootStash(new VectorStash((*rootStash)));
        qDebug() << "worker[" << i << "] data: goal: " << worker[i]->getGoal() << "; strategy: "  << worker[i]->getStrategy();
        //threads[i] = new std::thread(multithread_search, std::ref(*worker[i]));
        qf[i] = QtConcurrent::run(mt_search, *worker[i]);
    }

    // Warteschleife

    /*
    while (this->success != true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }


    // Join nachdem Lösung gefunden wurde

    qDebug("waitForFinished");
    for (quint8 i = 0; i < num_threads; i++) {
        //threads[i]->join();
        //delete worker[i];
        //delete threads[i];
        //qf[i].waitForFinished();
    }
    */
    qDebug("MT ENDE");
    // Multi Threading Ende #################################################################################################################



    //search();
    return true;
}

void MorphLarva::setNSA(NSA *nsa) {
    this->nsa = nsa;
}


void MorphLarva::setRootStash(VectorStash *stash) {
    this->rootStash = stash;
}

void MorphLarva::setSolutionStash(VectorStash *stash) {
    mutex.lock();
    if (!this->hasSuccess()) {
        this->success = true;
        this->solutionStash = stash;
        qDebug("Lösung wurde gesetzt");
    }
    mutex.unlock();
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

void MorphLarva::setSuccess(bool success) {
    this->success = success;
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

void MorphLarva::search() {
    qDebug("search() wurde ausgeführt");
    switch (this->strategy) {
        case 0:
            break;
        case 1:
            this->searchChaosRandom();
            break;
        case 2:
            this->searchOrderSort();
            break;
    }
}

void MorphLarva::searchChaosRandom() {
    qDebug("searchChaosRandom wurde gestartet");
    Coin* me = nullptr;
    quint16 loopmax = rootStash->size() - 1;
    VectorStash* rootCopy;

    while (overseer->hasSuccess() != true) {

        rootCopy = new VectorStash(*rootStash); // Kopiert den rootStash

        for (int i = 0; i < loopmax; i++) {

            me = rootCopy->takeCoinByRNG();
            memoryStash->addCoin(me);

            if (memoryStash->sum() > goal) {
                memoryStash->clear();
                delete rootCopy;
                break;
            }
            if (memoryStash->sum() == goal) {
                overseer->setSolutionStash(this->memoryStash);
                qDebug("searchChaosRandom war Erfolgreich!");
                //nsa->add("finish","searchChaosRandom war Erfolgreich!");
                break;
            } // End Success = True
        } // End for
    } // End while
}

void MorphLarva::searchOrderSort() {

    VectorStash* rootCopy = nullptr;
    quint16 calcMax = (((rootStash->sum() / 2) / 100) * 95);
    Coin* me = nullptr;
    Coin* coinSolution = nullptr;
    quint8 iCount = 0;

    while (overseer->hasSuccess() != true) {

        rootCopy = new VectorStash(*rootStash);
        me = nullptr;
        coinSolution = nullptr;
        iCount = 0;

        while (memoryStash->size() < calcMax) {
            me = rootCopy->takeCoinByPos(iCount);
            memoryStash->addCoin(me);

            //iCount++;
        }


        while (overseer->hasSuccess() != true) {

            coinSolution = rootCopy->takeCoinByValue((goal - memoryStash->size()));

            if (coinSolution != nullptr) {
                memoryStash->addCoin(coinSolution);
            } else {
                me = rootCopy->takeCoinByRNG();
                memoryStash->addCoin(me);
            }

            if (memoryStash->size() > goal) {
                memoryStash->clear();
                calcMax = ((calcMax / 100) * 95);
                if (calcMax < ((goal / 100) * 60)) { calcMax = (((rootCopy->sum() / 2) / 100) * 95);	}
                delete rootCopy;
                break;
            }
            if (memoryStash->size() == goal) {
                overseer->setSolutionStash(this->memoryStash);
                break;
            }
        }
    } // End while
}

