#include "vectorstash.h"

VectorStash::VectorStash() {
    rng = new RNGesus();
    total = 0;
}

VectorStash::VectorStash(VectorStash &copyStash) {
    this->rng = new RNGesus();
    this->coins = copyStash.deepCopy();
    this->total = copyStash.total;
}

VectorStash::VectorStash(QVector<Coin *> *copyVector) {
    total = 0;
    if (copyVector->size() > 0) {
        for (quint16 i = 0; i < copyVector->size(); i++) {
            addCoin(copyVector->at(i));
        }
    }
}

VectorStash::~VectorStash() {
    clear();
    coins.clear();
    delete rng;
}

quint16 VectorStash::size() {
    // Rückgabe der Anzahl der im VectorStash befindlichen Elemente
    return static_cast<quint16>(coins.size());
}

quint32 VectorStash::sum() {
    // Rückgabe der Summe aller im VectorStash befindlicher Elemente
    return total;
}

QString VectorStash::display() {
    QString output = "";
    quint16 max = static_cast<quint16>(coins.size());
    if (max > 0) {
        for(quint16 i = 0; i < max; i++) {
            output += QString::number(coins.at(i)->getValue()) + "\n";
        }
    } else {output += "Leerer Schatz.";}
    return output;
}

void VectorStash::clear() {
    // Resettet den VectorStash
    total = 0;
    if (coins.size() > 0) {
        for (quint16 i = 0; i < coins.size(); i++) {
            delete coins[i];
        }
    }
    coins.clear();
}

QVector<Coin *> *VectorStash::exportVector() {
    // Kopiert den Inhalt und übergibt ihn als Vector
    QVector<Coin*> *output = new QVector<Coin*>();
    if (coins.size() > 0) {
        for (quint16 i = 0; i < coins.size(); i++) {
            output->push_back(coins[i]);
        }
    }
    return output;
}

QVector<Coin*> VectorStash::deepCopy() {
    // Erstellt eine "tiefe" Kopie als QVector
    QVector<Coin*> output;
    if (coins.size() == 0) { return output; }
    for (quint16 i = 0; i < coins.size(); i++) {
        output.push_back(new Coin(*coins[i]));
    }
    return output;
}

void VectorStash::addCoin(Coin *pointer) {
    total += pointer->getValue();
    coins.push_back(pointer);
}

void VectorStash::addCoin(quint16 value) {
    total += value;
    coins.push_back(new Coin(value));
}

void VectorStash::addRngCoin(quint16 min, quint16 max) {
    if (min > 0 && max >= min) {
        this->addCoin(static_cast<quint16>(rng->getRng(static_cast<qint16>(min), static_cast<qint16>(max))));
    }
}

void VectorStash::fillRandom(quint16 size) {
    for (quint16 i = 0; i < size; i++) {
        this->addCoin(static_cast<quint16>(rng->getRng(1, static_cast<qint16>(size))));
    }
}

void VectorStash::fillRandom(quint16 size, quint16 min, quint16 max) {
    for (quint16 i = 0; i < size; i++) {
        this->addCoin(static_cast<quint16>(rng->getRng(static_cast<qint16>(min), static_cast<qint16>(max))));
    }
}

void VectorStash::fillAscending(quint16 size) {
    for (quint16 i = 1; i <= size; i++) {
        this->addCoin(i);
    }
}

Coin *VectorStash::getCoinByPos(quint16 pos) {
    return coins[pos];
}

Coin *VectorStash::getCoinByValue(quint16 value) {
    return searchCoinByValue(0, static_cast<quint16>(coins.size() - 1), value);
}

QString VectorStash::getQString() {
    // Zuständigkeit: Milan

    QString inhalt;
    for(quint16 i = 0; i < this->size(); i++) {


        //um das vorangehende Komma vor dem ersten Eintrag zu vermeiden wird diese Fallunterscheidung eingebaut:
        //QString::number(xxx) wird benoetigt, damit nicht das dem integer entsprechende Ascii angezeigt wird,
        //sondern die tatsaechliche zahl.
        if (inhalt == "") {
            inhalt += QString::number(this->getCoinByPos(i)->getValue());
        }
        else {
            inhalt += ",";
            inhalt += QString::number(this->getCoinByPos(i)->getValue());
        }
    }
    return inhalt;
}

QString VectorStash::getGuiQString() {
    // Zuständigkeit: Milan

    //stashInhalt in einem QString speichern:
    QString inhalt;
    for(quint16 i = 0; i < this->size(); i++) {


        //um das vorangehende Komma vor dem ersten Eintrag zu vermeiden wird diese Fallunterscheidung eingebaut:
        //QString::number(xxx) wird benoetigt, damit nicht das dem integer entsprechende Ascii angezeigt wird,
        //sondern die tatsaechliche zahl.
        if (inhalt == "") {
            inhalt += QString::number(this->getCoinByPos(i)->getValue());
        }
        else {
            inhalt += ", ";

            //Damit der angezeigte Inhalt nicht unnoetig viel Platz verschwendet:
            if (i == 100) {
                i = this->size();
                inhalt += "... (Um den kompletten Inhalt zu sehen bitte die Export-Funktion nutzen.)";
            }
            else {
                inhalt += QString::number(this->getCoinByPos(i)->getValue());
            }
        }
    }

    return inhalt;
}



Coin *VectorStash::takeCoinByValue(quint16 value) {
    Coin* me = searchCoinByValue(0, static_cast<quint16>(coins.size() - 1), value);
    if (me != nullptr) {
        this->removeCoinByPointer(me);
    }
    return me;
}

Coin *VectorStash::takeCoinByPos(quint16 pos) {
    Coin* me = coins[pos];
    me->setPos(pos);
    this->removeCoinByPointer(me);
    return me;
}

Coin *VectorStash::takeCoinByRNG() {
    // Wählt einen zufälligen Coin aus, legt diesen in den Zwischenspeicher, entfernt ihn aus der Menge und übergibt ihn
    quint16 rngCoin = static_cast<quint16>(rng->getRng(0, static_cast<qint16>(coins.size() - 1)));
    Coin* me = coins[rngCoin];
    me->setPos(rngCoin);
    this->removeCoinByPointer(me);
    return me;
}

bool VectorStash::removeCoinByPos(quint16 pos) {
    Coin* me = coins[pos];
    total -= me->getValue();
    coins.remove(pos);
    return true;
}

bool VectorStash::removeCoinByValue(quint16 value) {
    // ToDo: evtl performantere Suche.
    quint16 max = static_cast<quint16>(coins.size());

    for (quint16 i = 0; i < max; i++) {
        if (coins[i]->getValue() == value) {
            total -= coins[i]->getValue();
            coins.remove(i);
            return true;
        }
    }
    return false;
}

bool VectorStash::removeCoinByRNG() {
    // Löscht einen zufälligen Coin
    if (coins.size() > 0) {
        quint16 rngCoin = static_cast<quint16>(rng->getRng(0, static_cast<qint16>(coins.size() - 1)));
        this->removeCoinByPos(rngCoin);
        return true;
    } else {return false;}
}

bool VectorStash::removeCoinByIt(CoinList::iterator it) {
    if (it) {return false;}
    // Muss das sein? x_x
    return true;
}

bool VectorStash::removeCoinByPointer(Coin* pointer) {
    total -= pointer->getValue();
    coins.remove(pointer->getPos());
    return true;
}

void VectorStash::quickSortAsc() {
    if (coins.size() > 1) {
        std::sort(coins.begin(),coins.end(),[](Coin* a, Coin* b)->bool{return a->getValue() < b->getValue() ;});
    }
}

void VectorStash::quickSortDesc() {
    if (coins.size() > 1) {
        std::sort(coins.begin(),coins.end(),[](Coin* a, Coin* b)->bool{return a->getValue() > b->getValue() ;});
    }
}

bool VectorStash::isSortedAsc() {
    if (coins.size() > 1) {
        for (quint16 i = 1; i < coins.size(); i++) {
            if (coins[i]->getValue() < coins[i - 1]->getValue()) {
                return false;
            }
        }
    }
    return true;
}

bool VectorStash::isSortedDesc() {
    if (coins.size() > 1) {
        for (quint16 i = 1; i < coins.size(); i++) {
            if (coins[i]->getValue() > coins[i - 1]->getValue()) {
                return false;
            }
        }
    }
    return true;
}

Coin *VectorStash::searchCoinByValue(quint16 left, quint16 right, quint16 lookup) {
    // ACHTUNG! Das Array muss vorher Descending Sortiert sein!
    // Suchalgorithmus an QuickSort angelehnt :D
    quint16 pos = (left + right) / 2;
    quint16 pivot = coins[pos]->getValue();
    if (pivot == lookup) {
        Coin* me = coins.at(pos);
        me->setPos(pos); // Gibt dem Coin als Wert an welcher Stelle er "sitzt" :)
        return me;
    }
    if (left == right) { return nullptr; }
    if (pivot < lookup) { return searchCoinByValue(pos + 1, right, lookup); }
    if (pivot > lookup) { return searchCoinByValue(left, pos, lookup); }
    return nullptr;
}
