#include "liststash.h"

ListStash::ListStash() {
    total = 0;
}

ListStash::ListStash(QVector<Coin *> *copyVector) {
    // Erstellt einen ListStash mithilfe eines reinen Coin* Vectors
    total = 0;
    if (copyVector->size() > 0){
        for (quint16 i = 0; i < copyVector->size(); i++) {
            addBack(copyVector->at(i));
        }
    }
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
    total -= me->getValue();
    coins.removeFirst();
    return me;
}

Coin *ListStash::takeLast() {
    Coin* me = coins.last();
    total -= me->getValue();
    coins.removeLast();
    return me;
}

Coin *ListStash::searchntake(quint16 value) {
    Coin* output = nullptr;
    if (coins.size() > 0){
        for (Coin* me : coins) {
            if (me->getValue() == value) {
                output = me;
                total -= me->getValue();
                coins.removeOne(me);
                return output;
            }
        }
    }
    return output;
}

QVector<Coin *> *ListStash::toVector() {
    QVector<Coin*> *output = new QVector<Coin*>();
    if (!coins.isEmpty()){
        for (Coin* me : coins) {
            output->push_back(me);
        }
    }
    return output;
}
