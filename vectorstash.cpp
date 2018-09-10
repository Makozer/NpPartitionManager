#include "vectorstash.h"

VectorStash::VectorStash() {
    // reserve ToDo
    rng = new RNGesus();
    total = 0;
}

VectorStash::VectorStash(const VectorStash &copyStash) {
    this->rng = new RNGesus();
    this->nsa = copyStash.nsa;
    this->coins = QVector<Coin*>(copyStash.coins);
    this->total = copyStash.total;
}

VectorStash::~VectorStash() {
    coins.clear();
    delete rng;
}

void VectorStash::setNSA(NSA *nsa) {
    this->nsa = nsa;
}

NSA *VectorStash::getNSA() {
    return nsa;
}

quint16 VectorStash::size() {
    return coins.size();
}

quint32 VectorStash::sum() {
    return total;
}

QString VectorStash::display() {
    QString output = "";
    quint16 max = coins.size();
    if (max > 0) {
        for(quint16 i = 0; i < max; i++) {
            output += QString::number(coins.at(i)->getValue()) + "\n";
        }
    } else {output += "Leerer Schatz.";}
    return output;
}

void VectorStash::clear() {
    total = 0;
    coins.clear();
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
    if (min > 0 && max > min) {
        this->addCoin(rng->getRng(min, max));
    }
}

void VectorStash::fillRandom(quint16 size) {
    for (quint16 i = 0; i < size; i++) {
        this->addCoin(rng->getRng(1, size));
    }
}

void VectorStash::fillRandom(quint16 size, quint16 min, quint16 max) {
    for (quint16 i = 0; i < size; i++) {
        this->addCoin(rng->getRng(min, max));
    }
}

void VectorStash::fillAscending(quint16 size) {
    for (quint16 i = 1; i <= size; i++) {
        this->addCoin(i);
    }
}

Coin *VectorStash::getCoinByPos(quint16 pos) {
    return coins.at(pos);
}

Coin *VectorStash::getCoinByValue(quint16 value) {
    return searchCoinByValue(coins, 0, coins.size() - 1, value);
}

QString VectorStash::getQString() {

    QString inhalt;
    for(int i = 0; i < this->size(); i++) {


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

    //stashInhalt in einem QString speichern:
    QString inhalt;
    for(int i = 0; i < this->size(); i++) {


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
    Coin* me = searchCoinByValue(coins, 0, coins.size() - 1, value);
    if (me != nullptr) { this->removeCoinByPointer(me); }
    return me;
}

Coin *VectorStash::takeCoinByPos(quint16 pos) {
    Coin* me = coins.at(pos);
    me->setPos(pos);
    this->removeCoinByPointer(me);
    return me;
}

Coin *VectorStash::takeCoinByRNG() {
    quint16 rngCoin = rng->getRng(0, (coins.size() - 1));
    //qDebug() << "takeCoinByRNG Data: size=" << coins.size() << "| rngCoin=" << rngCoin;
    Coin* me = coins.at(rngCoin);
    me->setPos(rngCoin);
    this->removeCoinByPointer(me);
    return me;
}

bool VectorStash::removeCoinByPos(quint16 pos) {
    Coin* me = coins.at(pos);
    total -= me->getValue();
    if (coins.size() <= pos) {
        qDebug() << "removeCoinByPos() | stash size: " << coins.size() << "; pos: " << pos;
    }
    coins.remove(pos);
    return true;
}

bool VectorStash::removeCoinByValue(quint16 value) {
    // ToDo: evtl performantere Suche.
    quint16 max = coins.size();

    for (quint16 i = 0; i < max; i++) {
        if (coins[i]->getValue() == value) {
            total -= coins[i]->getValue();
            if (coins.size() <= i) {
                qDebug() << "removeCoinByValue() | stash size: " << coins.size() << "; pos: " << i;
            }
            coins.remove(i);
            return true;
        }
    }
    return false;
}

bool VectorStash::removeCoinByIt(CoinList::iterator it) {
    // Muss das sein? x_x
    return true;
}

bool VectorStash::removeCoinByPointer(Coin *pointer) {
    total -= pointer->getValue();
    if (coins.size() <= pointer->getPos()) {
        qDebug() << "removeCoinByPointer() | stash size: " << coins.size() << "; pos: " << pointer->getPos();
    }
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

Coin *VectorStash::searchCoinByValue(VectorStash::CoinList coins, quint16 left, quint16 right, quint16 lookup) {
    // ACHTUNG! Das Array muss vorher Descending Sortiert sein!
    int pos = (left + right) / 2;
    int pivot = coins[pos]->getValue();
    if (pivot == lookup) {
        Coin* me = coins.at(pos);
        me->setPos(pos);
        return me;
    }
    if (left == right) { return nullptr; }
    if (pivot < lookup) { return searchCoinByValue(coins, pos + 1, right, lookup); }
    if (pivot > lookup) { return searchCoinByValue(coins, left, pos, lookup); }
    return nullptr;
}
