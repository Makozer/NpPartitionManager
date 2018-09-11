#include "liststash.h"

ListStash::ListStash() {
    total = 0;
}

quint32 ListStash::sum()  {
    return total;
}

void ListStash::addFront(Coin *coin) {
    total += coin->getValue();
    coins.push_front(coin);
}

void ListStash::addBack(Coin *coin) {
    total += coin->getValue();
    coins.push_back(coin);
}

Coin *ListStash::takeFirst() {
    Coin* me = coins.first();
    coins.removeFirst();
    return me;
}

Coin *ListStash::takeLast() {
    Coin* me = coins.last();
    coins.removeLast();
    return me;
}

QVector<Coin *> ListStash::toVector() {

}
