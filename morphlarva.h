#ifndef MORPHLARVA_H
#define MORPHLARVA_H
#include <QVector>
#include <QString>
#include <vectorstash.h>
#include <nsa.h>
#include <memento.h>
#include <QObject>

// Threading?? alt
#include <thread>
#include <chrono>
// Qt Threading
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
// Conq
#include <QDebug>
#include <QThread>
#include <QString>
#include <QApplication>
#include <QtConcurrent/QtConcurrent>

class MorphLarva : public QThread {
    Q_OBJECT
signals:
    void foundSolution();
public:
    MorphLarva();
    MorphLarva(const MorphLarva &copyLarva);

    // Das wichtigste für die GUI ;)
    bool runCalc(); // startet den Suchvorgang
    void setNSA(NSA* nsa);
    void setRootStash(VectorStash* stash);    
    VectorStash* getSolutionStash();

    bool stopCalc();

    // Unwichtig für GUI, trotzdem zwingend public sichtbar
    void setSolutionStash(VectorStash* stash);
    void setOverseer(MorphLarva* overseer);
    MorphLarva* getOverseer();

    void setSuccess(bool success);
    bool hasSuccess();
    void setStrategy(quint8 strategy);
    quint8 getStrategy();
    void setGoal(quint16 goal);
    quint16 getGoal();

    void search();

    // temporär
    void debug();

private:
    // Threading
    //std::thread* threads[8];
    MorphLarva* worker[8];
    //void mt_search(MorphLarva &worker);
    //QFuture<void> qf[8];
    QVector<MorphLarva*> workers;
    QVector<QFuture<void>> qfs;
    QMutex mutex;

    // Funktionen
    void searchChaosRandom();
    void searchOrderSort();

    // Verschiedene Objekte
    MorphLarva* overseer;

    VectorStash* rootStash;
    VectorStash* memoryStash;
    VectorStash* solutionStash;

    NSA* nsa;
    RNGesus* rng;
    Memento* timer;

    bool success;
    bool cheatCoin;
    quint16 goal;
    quint8 strategy;

};

#endif // MORPHLARVA_H
