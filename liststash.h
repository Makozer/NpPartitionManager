#ifndef LISTSTASH_H
#define LISTSTASH_H
#include <QDebug>
#include <QList>
#include <coin.h>
#include <rngesus.h>
#include <nsa.h>

class ListStash {
    typedef QList<Coin*> CoinList;
public:
    ListStash();
    ListStash(QVector<Coin*> *copyVector);
    quint32 sum();

    void addFront(Coin* coin);
    void addBack(Coin* coin);

    Coin* takeFirst();
    Coin* takeLast();

    Coin* searchntake(quint16 value); // https://youtu.be/StRVJO9Zq3o

    QVector<Coin*> *toVector();
private:
    CoinList coins;
    RNGesus* rng;
    NSA* nsa;

    // Variablen
    quint32 total; // Die Summe des gesamten Schatzes
};

#endif // LISTSTASH_H
