/* Beschreibung:
 * Die "Basisklasse" in der Werte ( als Coins ) abgespeichert werden, sie basiert auf einem QVector.
 * Sie ist sehr umfangreich und bietet allerlei Funktionen um die in ihr enthaltenen Werte zu managen.
 *
 * Zuständigkeit: Martin
 */
#ifndef VECTORSTASH_H
#define VECTORSTASH_H
#include <QDebug>
#include <QVector>
#include <QList>
#include <QString>
#include "coin.h"
#include "rngesus.h"

class VectorStash {
    typedef QVector<Coin*> CoinList;
public:
    VectorStash();
    VectorStash(VectorStash &copyStash);         // Copy Konstruktor, ohne const weil C++ rumheult wegen member methoden
    VectorStash(QVector<Coin*> *copyVector);     // Konstruktor mit dem von einem reinen Vektor zu einem VectorStash konvertiert wird
    ~VectorStash();                              // Destruktor

    // Generelle Schatzfunktionen
    quint16 size();                              // Gibt die Anzahl an Werten im VectorStash zurück
    quint32 sum();                               // Gibt die Summe der Anzahl der Werte im VectorStash zurück
    QString display();                           // Gibt einen QString mit allen Werten zurück
    void clear();                                // Löscht den kompletten Inhalt
    QVector<Coin*> *exportVector();              // Export Funktion zur Rückgabe als deep copy QVector

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
    QString getQString();
    QString getGuiQString();

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
    void quickSortAsc();                         // Sortiert den Schatz aufsteigend
    void quickSortDesc();                        // Sortiert den Schatz absteigend
    bool isSortedAsc();                          // Kontrolle ob aufsteigend sortiert ist
    bool isSortedDesc();                         // Kontrolle ob absteigend sortiert ist
private:
    // Funktionen
    QVector<Coin*> deepCopy();                   // Gibt eine Deep Copy als QVector zurück

    // Suche nach einem Coin mit spezifiziertem Wert, coins muss vorher absteigend sortiert sein
    Coin* searchCoinByValue(quint16 left, quint16 right, quint16 lookup);

    // Objekte
    CoinList coins;                              // Vector der die Coins speichert
    RNGesus* rng;                                // Zufallsgenerierende Klasse

    // Variablen
    quint32 total;                               // Die Summe des gesamten Schatzes
};

#endif // VECTORSTASH_H
