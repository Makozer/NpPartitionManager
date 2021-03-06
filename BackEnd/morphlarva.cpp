#include "morphlarva.h"

MorphLarva::MorphLarva() {
    rng = new RNGesus();
    memoryStash = new VectorStash();

    rootStash = nullptr;
    solutionStash = new VectorStash();
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
    this->rng = new RNGesus();
    this->timer = new Memento();
    this->success = copyLarva.success;
    this->goal = copyLarva.goal;
    this->strategy = copyLarva.strategy;
}

MorphLarva::~MorphLarva() {
    cleanup();
}

void mt_search(MorphLarva &worker) {
    // Diese Funktion muss so sein, damit das Multithreading starten kann.
    worker.search();
}

bool MorphLarva::runCalc() {
    // Diese Funktion aus der GUI aufrufen zum starten der Berechnung!

    // Aufräumen bzw stoppen der Threads:
    if (!cleanup()) { return false; }

    // Abklappern ob startbereit
    if (!readycheck()) { return false; }

    this->rootStash->quickSortDesc();
    this->setOverseer(this);
    this->success = false;
    this->setGoal(rootStash->sum() / 2);

    // Analyse
    qDebug("Analyse ...");
    if (!analysis()) { return false; }

    qDebug("Berechnung ...");

    // Schatz Begradigung -> Damit der Schatz gerade teilbar ist :)
    addCheatCoin();

    this->setGoal(rootStash->sum() / 2);

    // Multi Threading ####################################################################################################################

    quint8 num_threads = 4;
    quint8 strat[] = { 3, 2, 5, 1 };
    qDebug() << "WorkerStart, overseer Data: size=" << rootStash->size() << "| sum=" << rootStash->sum() << "| goal=" << goal;
    for (quint8 i = 0; i < num_threads; i++) {
        workers.push_back(new MorphLarva());
        workers[i]->setOverseer(this);
        workers[i]->setGoal(this->getGoal());
        workers[i]->setStrategy(strat[i]);
        workers[i]->setRootStash(new VectorStash(*rootStash));
    }
    for (quint8 i = 0; i < num_threads; i++) {
        qfs.push_back(QtConcurrent::run(mt_search, *workers[i]));
    }
    qDebug() << "MT Start vollzogen, Zeit: " << QString::number(timer->getSeconds());
    // Multi Threading Ende #################################################################################################################

    return true;
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
        emit foundSolution();
    }
    mutex.unlock();
}

void MorphLarva::setNoSolution() {
    mutex.lock();
    if (!this->hasSuccess()) {
        this->success = true; // Damit die anderen Threads gestoppt werden.
        this->timer->stop();
        removeCheatCoin();
        qDebug() << "searchFaculty() sagt, dass es keine Lösung gibt. Dauer: " << QString::number(timer->getSeconds());
        emit noSolution();
    }
    mutex.unlock();
}

void MorphLarva::setMessage(QString msg) {
    emit message(msg);
}

VectorStash *MorphLarva::getSolutionStash() {
    return solutionStash;
}

Memento *MorphLarva::getTimer() {
    return timer;
}

bool MorphLarva::stopCalc() {
    success = true; // Fake Erfolg damit die Threads aufhören zu laufen... anders ging es nicht :D
    quint8 tCount = static_cast<quint8>(qfs.size());
    for(quint8 i = 0; i < tCount; i++) {
        qfs[i].waitForFinished();
    }
    qfs.clear();
    qDebug("Threads wurden abgebrochen/gelöscht und bereinigt ...");
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

void MorphLarva::setGoal(quint32 goal) {
    this->goal = goal;
}

quint32 MorphLarva::getGoal() {
    return goal;
}

void MorphLarva::search() {
    // startet den jeweiligen Suchalgorithmus
    this->debug();
    switch (this->strategy) {
        case 0:
            break;
        case 1:
            this->searchChaosRandom();
            break;
        case 2:
            this->searchOrderSort();
            break;
        case 3:
            this->searchDanceJinJang();
            break;
        case 4:
            this->searchDanceS();
            break;
        case 5:
            this->searchFaculty();
            break;
    }
}

void MorphLarva::debug() {
    qDebug() << "MorphLarva Data: | strategy: " << strategy << "| rootSize: " << rootStash->size() << "| rootSum: " << rootStash->sum() << "| goal: " << goal;
}

bool MorphLarva::cleanup() {
    if(qfs.size() > 0) {
        qDebug() << "cleanup: size > 0";
        if (!qfs[0].isRunning()) {
            qDebug() << "Threads nicht am laufen.";
            stopCalc();
        } else {
            stopCalc();
            overseer->setMessage("Der laufende Vorgang wurde abgebrochen.");
            return false; // bricht die Threads und den Vorgang ab wenn runCalc geclickt wird während er sucht.
        }
    }
    timer->stop();
    removeCheatCoin();
    return true;
}

bool MorphLarva::readycheck() {
    if (rootStash == nullptr) {
        qDebug("run konnte nicht gestartet werden aufgrund nullptr");
        return false;
    } else {
        timer->start();
        qDebug("Vorgang gültig, starten der Prozesse ...");
        return true;
    }
}

bool MorphLarva::analysis() {
    if (rootStash->size() < 2) {
        // Abbruch bei zu wenig Münzen.
        overseer->setMessage("Zu wenig Werte im Schatz!");
        qDebug("Error: zu wenig Münzen");
        return false;
    }
    if (rootStash->getCoinByPos(0)->getValue() > goal) {
        // Abbruch falls eine Münze größer ist als die gesuchte Hälfte
        overseer->setMessage("Ein Wert ist größer als die gesuchte Hälfte!");
        qDebug("Error: erster Coin größer als gesuchte Hälfte");
        return false;
    }
    return true;
}

void MorphLarva::searchChaosRandom() {
    // Initialisierung
    Coin* me = nullptr;
    quint16 loopmax = rootStash->size() - 1; // Setzt das Schleifenmaximum fest
    VectorStash* rootCopy;

    while (overseer->hasSuccess() != true) {

        rootCopy = new VectorStash(*rootStash); // Kopiert den rootStash

        for (int i = 0; i < loopmax; i++) {
            // Die Schleife fügt solange zufällige Elemente zusammen bis keine Elemente mehr vorhanden sind oder das Ergebnis gefunden wurde
            me = rootCopy->takeCoinByRNG();
            memoryStash->addCoin(me);

            if (memoryStash->sum() > goal) {
                // Falls der memoryStash größer als die gesuchte Menge ist
                memoryStash->clear();
                delete rootCopy;
                break;
            }
            if (memoryStash->sum() == goal) {
                // Ergebnis gefunden! :)
                overseer->setSolutionStash(this->memoryStash);
                qDebug("searchChaosRandom war Erfolgreich!");
                break;
            } // End Success = True
        } // End for
    } // End while
}

void MorphLarva::searchOrderSort() {
    // Initialisierung
    VectorStash* rootCopy = nullptr;
    // calcMax legt fest wie hoch der anfängliche memoryStash per Zufall befüllt werden soll, damit der fehlende Rest gesucht werden kann.
    quint16 calcMax = static_cast<quint16>((((rootStash->sum() / 2.00) / 100.00) * 95.00));
    Coin* me = nullptr;
    Coin* coinSolution = nullptr;
    quint16 iCount = 0;

    while (overseer->hasSuccess() != true) {
        // Läuft solange bis das Ergebnis gefunden wurde

        rootCopy = new VectorStash(*rootStash); // Erstellt eine Kopie des rootStashs
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

            // Fallunterscheidung ob memory zu voll oder goal exakt gefunden
            if (memoryStash->sum() > goal) {
                // Kontrolle ob noch Coins in der rootCopy sind und ob der verbleibende Rest größer ist als die gesuchte Hälfte.
                if (rootCopy->size() > 0 && rootCopy->sum() > (goal - memoryStash->sum())) {
                    while (memoryStash->sum() > goal) {
                        memoryStash->removeCoinByRNG();
                    }
                } else {
                    // Aufräumen, Reset und neu anfangen
                    memoryStash->clear();
                    calcMax = static_cast<quint16>((calcMax / 100.00) * 95.00);
                    if (calcMax < ((goal / 100.00) * 60.00)) { calcMax = static_cast<quint16>(((rootCopy->sum() / 2) / 100.00) * 95.00);	}
                    delete rootCopy;
                    break;
                }
            }

            if (memoryStash->sum() == goal) {
                // Ergebnis gefunden :)
                qDebug() << "searchOrderSort() war erfolgreich!";
                overseer->setSolutionStash(this->memoryStash);
                break;
            }

            // Sucht ob es eine exakt fehlende Münze gibt die man nur hinzufügen müsste um die Lösung zu finden.
            coinSolution = rootCopy->takeCoinByValue(static_cast<quint16>(goal - memoryStash->sum()));
            if (coinSolution != nullptr) {
                 memoryStash->addCoin(coinSolution);
            } else {
                 me = rootCopy->takeCoinByRNG();
                 memoryStash->addCoin(me);
            }
        } // End while
    } // End while
}

void MorphLarva::searchDanceJinJang() {
    // Schneller performanter Suchalgorithmus der zwei gleichgroße Mengen bildet und solange Coins hin und her schmeißt, bis die Lösung da ist
    ListStash* jin = new ListStash(rootStash->exportVector());
    ListStash* jang = new ListStash();
    quint32 i = 0;
    quint32 lMax = rootStash->size() * 2;

    while (jin->sum() != jang->sum() && overseer->hasSuccess() != true) {

        for (i = 0; i <= lMax; i++) { // Schleife, damit nicht so oft der overseer auf success abgefragt wird
            if (jin->sum() > jang->sum())  { jang->addBack(jin->takeFirst()); }
            if (jin->sum() < jang->sum())  { jin->addBack(jang->takeFirst()); }
            if (jin->sum() == jang->sum()) {
                qDebug() << "searchDanceJinJang() war erfolgreich!";
                overseer->setSolutionStash(new VectorStash(jin->toVector()));
                break; }
        }
        jin->shuffle();     // after going through the whole circle twice it needs to be shuffled
        jang->shuffle();    // after going through the whole circle twice it needs to be shuffled ... this guy, too :)
    }
}

void MorphLarva::searchDanceS() {
    // To Do ... bzw hats leider nicht in die Finale Version geschafft bzw wurde schon im anderen übernommen, hier könnte nach der Bewertung noch neues entstehen
    // Das Projekt werde ich noch weiter verbessern :)
}

void MorphLarva::searchFaculty() {
    // Die Funktion wird bis maximale Fakultät von 2 - fMax ausgeführt, maximal 256 aufgrund von quint8
    if (rootStash->size() < fMax && rootStash->size() > 2) {
        qDebug() << "searchFaculty wird ausgeführt";

        for (quint8 i = 0; i < rootStash->size(); i++) {
            QVector<quint8> *picked = new QVector<quint8>;
            picked->push_back(i);
            searchFaculty(1, picked);
            delete picked;
        }

        if (!overseer->hasSuccess()) {
            // Wenn die Fakultät komplett durchgelaufen ist und nichts gefunden wurde, dann wird das Signal gegeben, dass keine Lösung möglich ist.
            // Andernfalls ist overseer auf success und dies wird nicht ausgeführt
            overseer->setNoSolution();
        }
    } else {
        qDebug("searchFaculty wurde nicht gestartet: Coin Anzahl > fMax");
    }
}

void MorphLarva::searchFaculty(quint8 pos, QVector<quint8> *picked) {
    // Rekursiver Aufruf zum durchtesten von allen Kombinationen

    // Berechnen bisheriger Summe
    quint32 tempSum = 0;
    for (quint8 i = 0; i < picked->size(); i++) {
            tempSum += rootStash->getCoinByPos((*picked)[i])->getValue();
    }

    // Folgender Verschachtlungshorror überprüft erst ob die aktuelle Summe unter dem Ziel liegt, falls ja, dann wird weiter gesucht, falls exakt Ergebnis -> Abbruch mit Lösungsübergabe
    // Falls die tempSum über dem Ziel ist wird nichts getan, weil ... wozu weiter berechnen? :D
    // In der Theorie wären damit alle weiterfolgenden Möglichkeiten abgedeckt und unnötig, da keine davon eine Lösung ergeben könnte.
    if (tempSum < goal) {
        for (quint8 i = pos; i < rootStash->size(); i++) {
            if (!picked->contains(i)) { // Überprüft ob die Position bereits genommen wurde um jede Kombination nur einmal zu überprüfen
                // Befüllen des neuen Arrays
                QVector<quint8> *pickedNew = new QVector<quint8>;
                for (quint8 j = 0; j < pos; j++) {
                        pickedNew->push_back((*picked)[j]);
                }
                pickedNew->push_back(i);
                searchFaculty(pos + 1, pickedNew);
                delete pickedNew;
            }
        }
    } else {
        if (tempSum == goal) {
            if (!overseer->hasSuccess()) {
                VectorStash *solution = new VectorStash();
                for (quint8 i = 0; i < picked->size(); i++) {
                    solution->addCoin(rootStash->getCoinByPos(picked->at(i)));
                }
                qDebug("searchFaculty() fand eine Lösung.");
                overseer->setSolutionStash(solution);
            }
        }
    }
}

void MorphLarva::searchPseudoPoly() {
    // Quelle: https://en.wikipedia.org/wiki/Partition_problem#Methods
    // To Do!!! bzw nein, wird nicht in die zu bewertende Version aufgenommen.
    // Grund: dies wäre Fremdleistung, wir wollen nur zu 100% unsere eigene Leistung abgeben.
    // Nach der Abgabe würden wir hier aber weiter arbeiten und uns anschauen wie schnell dies ist um den Bereich der nicht entscheidbaren Fälle besser abzudecken.
    /*
     * INPUT:  A list of integers S
       OUTPUT: True if S can be partitioned into two subsets that have equal sum
       function find_partition(S):
            n ← |S| // Anzahl der Elemente
            K ← sum(S)
            P ← empty boolean table of size ([K/2] + 1) by (n + 1)
            initialize top row (P(0,x)) of P to True
            initialize leftmost column (P(x, 0)) of P, except for P(0, 0) to False
            for i from 1 to [K/2]
                for j from 1 to n
                    if (i-S[j]) >= 0
                        P(i, j) ← P(i, j-1) or P(i-S[j], j-1)
                    else
                        P(i, j) ← P(i, j-1)
            return P([K/2] , n)
     */
}


bool MorphLarva::addCheatCoin() {
    if (rootStash->sum() % 2 > 0) {
        qDebug() << "cheatCoin wird hinzugefügt, ursprüngliche root sum: " << rootStash->sum();
        rootStash->addCoin(1);
        cheatCoin = true; // Damit man weiß, dass hinterher der eine Cheatcoin wieder entfernt werden muss :D
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
