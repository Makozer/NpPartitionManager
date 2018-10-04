/* Beschreibung:
 * Die Klasse ListStash ist eine simple Liste die Coins haben kann und den gesamten Wert speichert, der in ihr ist.
 * Zuständigkeit: Martin
 */
#ifndef LISTSTASH_H
#define LISTSTASH_H
#include <QDebug>
#include <QList>
#include "coin.h"
#include "rngesus.h"

class ListStash {
    typedef QList<Coin*> CoinList;
public:
    ListStash();
    ListStash(QVector<Coin*> *copyVector);       // ListStash mithilfe eines QVectors erstellen
    quint32 sum();                               // Die Summe aller enthaltener Werte

    void addFront(Coin* coin);                   // Fügt einen Coin am Anfang der Liste hinzu
    void addBack(Coin* coin);                    // Fügt einen Coin am Ende der Liste hinzu

    Coin* takeFirst();                           // Nimmt den ersten Coin der Liste und übergibt ihn
    Coin* takeLast();                            // Nimmt den letzten Coin der Liste und übergibt ihn

    Coin* searchntake(quint16 value);            // https://youtu.be/StRVJO9Zq3o

    QVector<Coin*> *toVector();                  // Exportfunktion welche die Liste in einen QVektor konvertiert
private:
    CoinList coins;                              // Die Liste in der Coins gespeichert werden
    RNGesus* rng;                                // Zufallsgenerierende Klasse

    // Variablen
    quint32 total;                               // Die Summe des gesamten Schatzes
};

#endif // LISTSTASH_H
