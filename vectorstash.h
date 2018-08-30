#ifndef VECTORSTASH_H
#define VECTORSTASH_H
// Vererbung?
#include <QVector>
#include <QString>
#include "coin.h"
#include "rngesus.h"
#include "nsa.h"

class VectorStash {
    typedef QVector<Coin*> CoinList;
public:
    VectorStash();
    VectorStash(const VectorStash &copyStash);// Copy Konstruktor?

    // Überwachung
    void setNSA(NSA* nsa);
    NSA* getNSA();

    // Generelle Schatzfunktionen
    quint16 size();
    quint32 sum();
    QString display();
    void clear();

    // Hinzufügen von Werten
    void addCoin(Coin* pointer);
    void addCoin(quint16 value);
    void addRngCoin(quint16 min, quint16 max);
    void fillRandom(quint16 size);
    void fillRandom(quint16 size, quint16 min, quint16 max);
    void fillAscending(quint16 size);

    // Lesen von Werten
    Coin* getCoinByPos(quint16 pos);
    Coin* getCoinByValue(quint16 value);

    // Nehmen von Werten ( entfernt nach Übergabe )
    Coin* takeCoinByValue(quint16 value);
    Coin* takeCoinByPos(quint16 pos);
    Coin* takeCoinByRNG();

    // Entfernen von Werten
    bool removeCoinByPos(quint16 pos);
    bool removeCoinByValue(quint16 value);
    bool removeCoinByIt(CoinList::iterator it);
    bool removeCoinByPointer(Coin* pointer);

    // Sortierung
    void quickSortAsc();
    void quickSortDesc();
    bool isSortedAsc();
    bool isSortedDesc();
private:
    // Funktionen
    void quickSortAsc(quint16 leftpos, quint16 rightpos);
    void quickSortDesc(quint16 leftpos, quint16 rightpos);
    Coin* searchCoinByValue(CoinList coins, quint16 left, quint16 right, quint16 lookup);

    // Objekte
    CoinList coins;
    RNGesus* rng;
    NSA* nsa;

    // Variablen
    quint32 total; // Die Summe des gesamten Schatzes
};

#endif // VECTORSTASH_H
