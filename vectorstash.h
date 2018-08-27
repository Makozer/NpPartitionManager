#ifndef VECTORSTASH_H
#define VECTORSTASH_H
// Vererbung?
#include <QVector>
#include <QString>
#include "coin.h"

class VectorStash {
    typedef QVector<Coin*> CoinList;
public:
    VectorStash();
    // Copy Konstruktor?

    // Generelle Schatzfunktionen
    quint16 size();
    quint32 sum();
    QString display();
    void clear();

    // Hinzufügen von Werten
    void addCoin(Coin* pointer);
    void addCoin(quint16 value);
    void fillRandom(quint16 size);
    void fillAscending(quint16 size);

    // Lesen von Werten
    Coin* getCoinByPos(quint16 pos);
    Coin* getByValue(quint16 value);

    // Nehmen von Werten ( entfernt nach Übergabe )
    Coin* takeCoinByValue(quint16 value);
    Coin* takeCoinByPos(quint16 pos);
    Coin* takeCoinByRNG();

    // Entfernen von Werten
    bool removeCoinByValue(quint16 value);
    bool removeCoinByIt(CoinList::iterator it);
    bool removeCoinByP(Coin* pointer);

    // Sortierung
    void quickSortAsc();
    void quickSortDesc();
    bool isSortedAsc();
    bool isSortedDesc();
private:
    // Funktionen
    void quickSortAsc(quint16 leftpos, quint16 rightpos);
    void quickSortDesc(quint16 leftpos, quint16 rightpos);
    Coin* coinSearchByValue(CoinList coins, quint16 left, quint16 right, quint16 lookup);

    // Objekte
    CoinList coins;

    // Variablen
    quint32 total; // Die Summe des gesamten Schatzes
};

#endif // VECTORSTASH_H
