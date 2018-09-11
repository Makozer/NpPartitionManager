#include "morphlarva.h"

MorphLarva::MorphLarva() {
    rng = new RNGesus();
    memoryStash = new VectorStash();

    rootStash = nullptr;
    solutionStash = new VectorStash();
    nsa = nullptr;
    timer = new Memento();

    success = false;
    cheatCoin = false;
    goal = 0;
    strategy = 0;
}

MorphLarva::MorphLarva(const MorphLarva &copyLarva) {
    this->overseer = copyLarva.overseer;
    this->rootStash = new VectorStash(*copyLarva.rootStash);
    this->memoryStash = new VectorStash();
    this->nsa = copyLarva.nsa;
    this->rng = new RNGesus();
    this->timer = new Memento();
    this->success = copyLarva.success;
    this->goal = copyLarva.goal;
    this->strategy = copyLarva.strategy;
}

void mt_search(MorphLarva &worker) {
    // Diese Funktion muss so sein, damit das Multithreading starten kann.
    worker.search();
}

bool MorphLarva::runCalc() {
    // Diese Funktion aus der GUI aufrufen zum starten der Berechnung!

    // Aufräumen bzw stoppen der Threads:
    if(qfs.size() > 0) {
        if (!qfs[0].isRunning()) {
            stopCalc();
        } else {
            stopCalc();
            return false; // bricht die Threads und den Vorgang ab wenn runCalc geclickt wird während er sucht.
        }
    }

    // Aufräumen falls im Prozess abgebrochen wurde
    removeCheatCoin();

    // Abklappern ob startbereit
    if (rootStash == nullptr || nsa == nullptr) {
        nsa->add("Error", "run konnte nicht gestartet werden aufgrund nullptr");
        return false;
    } else {
        timer->start();
        nsa->add("Start", "Berechnung wurde gestartet");        
    }

    // ANALYSE !!!!!!!!!
    // TODO
    qDebug("Analyse start");
    if (rootStash->size() < 2) {
        // Abbruch bei zu wenig Münzen.
        return false;
    }

    // ANALYSE ENDE !!!!!!!!!!

    this->rootStash->quickSortDesc();
    this->setOverseer(this);
    this->success = false;
    qDebug("Berechnung wurde gestartet");

    // Schatz Begradigung
    // Damit der Schatz gerade teilbar ist :)
    addCheatCoin();
    // Begradigung Ende

    this->setGoal(rootStash->sum() / 2);

    // Multi Threading ####################################################################################################################

    quint8 num_threads = 2;
    quint8 strat[] = { 1, 2 };
    qDebug() << "WorkerStart, overseer Data: size=" << rootStash->size() << "| sum=" << rootStash->sum() << "| goal=" << goal;
    for (quint8 i = 0; i < num_threads; i++) {
        workers.push_back(new MorphLarva());
        workers[i]->setOverseer(this);
        workers[i]->setGoal(this->getGoal());
        workers[i]->setStrategy(strat[i]);
        workers[i]->setRootStash(new VectorStash(*rootStash));

        qfs.push_back(QtConcurrent::run(mt_search, *workers[i]));
        //qf[i] = QtConcurrent::run(mt_search, *worker[i]);
    }

    qDebug() << "MT Start vollzogen, Zeit: " << QString::number(timer->getSeconds());
    // Multi Threading Ende #################################################################################################################

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
        this->timer->stop();
        removeCheatCoin();
        qDebug() << "Lösung wurde gesetzt, Dauer: " << QString::number(timer->getSeconds());
    }
    emit foundSolution();
    mutex.unlock();
}

VectorStash *MorphLarva::getSolutionStash() {
    return solutionStash;
}

bool MorphLarva::stopCalc() {
    success = true; // Fake Erfolg damit die Threads aufhören zu laufen... anders ging es nicht :D
    quint8 tCount = qfs.size();
    for(quint8 i = 0; i < tCount; i++) {
        qfs[i].waitForFinished();
    }
    qfs.clear();
    qDebug("Threads wurden abgebrochen/gelöscht.");
    success = false;
    return true;
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

void MorphLarva::debug() {
    qDebug() << "MorphLarva Data:\nrootSize: " << rootStash->size() << "| rootSum: " << rootStash->sum() << "| goal: " << goal;
}

void MorphLarva::searchChaosRandom() {
    qDebug("searchChaosRandom wurde gestartet");
    // Initialisierung
    this->debug();
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
    qDebug() << "searchOrderSort wurde gestartet";
    // Initialisierung
    this->debug();
    VectorStash* rootCopy = nullptr;
    // calcMax legt fest wie hoch der anfängliche memoryStash befüllt werden soll, damit der fehlende Rest gesucht werden kann.
    quint16 calcMax = (((rootStash->sum() / 2.00) / 100.00) * 95.00);
    qDebug() << "calcMax=" << calcMax;
    Coin* me = nullptr;
    Coin* coinSolution = nullptr;
    quint8 iCount = 0;

    while (overseer->hasSuccess() != true) {

        rootCopy = new VectorStash(*rootStash);
        me = nullptr;
        coinSolution = nullptr;
        iCount = 0;

        // Füllt den memoryStash erstmal so auf bis calcMax
        while (memoryStash->sum() < calcMax && iCount < rootCopy->size()) {
            me = rootCopy->takeCoinByPos(iCount);
            memoryStash->addCoin(me);
            iCount++;
        }

        // Für den zufälligen Fall, dass direkt via Zufall direkt die Lösung gefunden wurde ... hatte ich bereits! :D
        if (memoryStash->sum() == goal) {
            qDebug("RNGesus blessed you :D");
            overseer->setSolutionStash(this->memoryStash);
            break;
        }

        // Läuft solange Erfolg eintritt ODER der Schatz zu voll geworden ist.
        while (overseer->hasSuccess() != true) {

            // Sucht ob es eine exakt fehlende Münze gibt die man nur hinzufügen müsste um die Lösung zu finden.
            coinSolution = rootCopy->takeCoinByValue((goal - memoryStash->sum()));
            if (coinSolution != nullptr) {
                qDebug("coinsolution found!");
                memoryStash->addCoin(coinSolution);
            } else {                
                me = rootCopy->takeCoinByRNG();
                memoryStash->addCoin(me);
            }

            // Fallunterscheidung ob memory zu voll oder goal exakt gefunden
            if (memoryStash->sum() > goal) {
                memoryStash->clear();
                calcMax = ((calcMax / 100.00) * 95.00);
                if (calcMax < ((goal / 100.00) * 60.00)) { calcMax = (((rootCopy->sum() / 2) / 100.00) * 95.00);	}
                delete rootCopy;
                break;
            }
            if (memoryStash->sum() == goal) {
                overseer->setSolutionStash(this->memoryStash);
                break;
            }
        } // End while
    } // End while
}

bool MorphLarva::addCheatCoin() {
    if (rootStash->sum() % 2 > 0) {
        rootStash->addCoin(1);
        cheatCoin = true; // Damit man weiß, dass hinterher der eine Cheatcoin wieder entfernt werden muss :D
        qDebug("cheatCoin wurde hinzugefügt.");
        return true;
    }
    return false;
}

bool MorphLarva::removeCheatCoin(){
    if (cheatCoin == true && solutionStash->size() > 1) {
        // Falls ein Coin zur Begradigung eingesetzt wurde
        solutionStash->removeCoinByValue(1);
        cheatCoin = false;
        qDebug("cheatCoin wurde entfernt.");
        return true;
    }
    return false;
}

