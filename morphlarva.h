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
    bool run(); // startet den Suchvorgang
    void setNSA(NSA* nsa);
    void setRootStash(VectorStash* stash);    
    VectorStash* getSolutionStash();

    // Unwichtig für GUI, trotzdem zwingend public sichtbar
    void setSolutionStash(VectorStash* stash);
    void setOverseer(MorphLarva* overseer);
    MorphLarva* getOverseer();

    bool hasSuccess();
    void setStrategy(quint8 strategy);
    quint8 getStrategy();
    void setGoal(quint16 goal);
    quint16 getGoal();

    void search();

private:
    // Funktionen
    void searchChaosRandom();
    void searchOrderSort();

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
    quint8 strategy;

};

#endif // MORPHLARVA_H
