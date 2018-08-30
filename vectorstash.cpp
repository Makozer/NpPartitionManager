#include "vectorstash.h"

VectorStash::VectorStash() {

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
    for(quint16 i = 0; i < max; i++) {
        output += QString::number(coins.at(i)->getValue()) + "\n";
    }
    return output;
}

void VectorStash::clear() {
    coins.clear();
}

void VectorStash::addCoin(Coin *pointer) {
    coins.push_back(pointer);
}

void VectorStash::addCoin(quint16 value) {
    coins.push_back(new Coin(value));
}

void VectorStash::fillRandom(quint16 size) {
    for (quint16 i = 0; i < size; i++) {
        this->addCoin(rng.getRng(1, size));
    }
}

void VectorStash::fillAscending(quint16 size) {
    // Falls mans noch iwann mal brauch ToDo, ansonsten rausstreichen, Random erfüllt den Job genauso :)
}

Coin *VectorStash::getCoinByPos(quint16 pos) {
    return coins.at(pos);
}

Coin *VectorStash::getCoinByValue(quint16 value) {
    return searchCoinByValue(coins, 0, coins.size() - 1, value);
}

Coin *VectorStash::takeCoinByValue(quint16 value) {
    Coin* me = searchCoinByValue(coins, 0, coins.size() - 1, value);
    if (me != nullptr) { this->removeCoinByPointer(me); }
    return me;
}

Coin *VectorStash::takeCoinByPos(quint16 pos) {
    Coin* me = coins.at(pos);
    this->removeCoinByPointer(me);
    return me;
}

Coin *VectorStash::takeCoinByRNG() {
    quint16 rngCoin = rng.getRng(0, coins.size());
    Coin* me = coins.at(rngCoin);
    me->setPos(rngCoin);
    this->removeCoinByPointer(me);
    return me;
}

bool VectorStash::removeCoinByPos(quint16 pos) {
    Coin* me = coins.at(pos);
    total -= me->getValue();
    coins.remove(pos);
    return true;
}

bool VectorStash::removeCoinByValue(quint16 value) {
    // ToDo falls es gebraucht wird ... SHIT
    return true;
}

bool VectorStash::removeCoinByIt(CoinList::iterator it) {
    // Muss das sein? x_x
    return true;
}

bool VectorStash::removeCoinByPointer(Coin *pointer) {
    total -= pointer->getValue();
    coins.remove(pointer->getPos());
    return true;
}

void VectorStash::quickSortAsc() {
    if (coins.size() > 1) {
        quickSortAsc(0, (coins.size() - 1));
    }
}

void VectorStash::quickSortDesc() {
    if (coins.size() > 1) {
        quickSortDesc(0, (coins.size() - 1));
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

void VectorStash::quickSortAsc(quint16 leftpos, quint16 rightpos) {
    quint16 i = leftpos , j = rightpos;
    Coin* tmp;

    int pivot = coins[(leftpos + rightpos) / 2]->getValue();

    while (i <= j) {
        while (coins[i]->getValue() < pivot) { i++; }
        while (coins[j]->getValue() > pivot) { j--; }
        if (i <= j) {
            tmp = coins[i];
            coins[i] = coins[j];
            coins[j] = tmp;
            i++;
            j--;
        }
    };

        /* recursion */
    if (leftpos < j) { quickSortAsc(leftpos, j); }
    if (i < rightpos) { quickSortAsc(i, rightpos); }
}

void VectorStash::quickSortDesc(quint16 leftpos, quint16 rightpos) {
    quint16 i = leftpos, j = rightpos;
    Coin* tmp;

    int pivot = coins[(leftpos + rightpos) / 2]->getValue();

    while (i <= j) {
        while (coins[i]->getValue() > pivot) { i++; }
        while (coins[j]->getValue() < pivot) { j--; }
        if (i <= j) {
            tmp = coins[i];
            coins[i] = coins[j];
            coins[j] = tmp;
            i++;
            j--;
        }
    };
    /* recursion */
    if (leftpos < j) { quickSortDesc(leftpos, j); }
    if (i < rightpos) { quickSortDesc(i, rightpos); }
} // end quickSortDesc

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
