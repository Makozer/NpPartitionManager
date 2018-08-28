#ifndef MORPHLARVA_H
#define MORPHLARVA_H
#include <QVector>
#include <QString>
#include <vectorstash.h>
#include <nsa.h>

class MorphLarva {
public:
    MorphLarva();

    // Das wichtigste für die GUI ;)
    void run(); // startet den Suchvorgang
    void setNSA(NSA* nsa);
    void setRootStash(VectorStash* stash);
    void setSolutionStash(VectorStash* stash);
    VectorStash* getSolutionStash();

    // Ab hier alles andere ignorieren :D
    // Unwichtig für GUI, trotzdem public sichtbar
    void setOverseer(MorphLarva* overseer);
    MorphLarva getOverseer();

    bool hasSuccess();
    void setStrategy(quint8 strategy);
    quint8 getStrategy();

private:
    // Verschiedene Objekte
    MorphLarva* overseer;
    MorphLarva* worker;

    VectorStash* rootStash;
    VectorStash* memoryStash;
    VectorStash* solutionStash;

    NSA* nsa;
    RNGesus* rng;

    bool success;
    quint16 goal;
    quint16 value;
    quint8 strategy;

};

#endif // MORPHLARVA_H
