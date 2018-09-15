#ifndef MORPHLARVA_H
#define MORPHLARVA_H
#include <QVector>
#include <QString>
#include <vectorstash.h>
#include <liststash.h>
#include <nsa.h>
#include <memento.h>
#include <QObject>

// Qt Threading
#include <QMutex>
#include <QSize>
#include <QWaitCondition>
#include <QDebug>
#include <QThread>
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

    // Unwichtig für GUI, trotzdem zwingend public sichtbar
    void setSolutionStash(VectorStash* stash);
    void setOverseer(MorphLarva* overseer);
    MorphLarva* getOverseer();

    void setSuccess(bool success);
    bool hasSuccess();
    void setStrategy(quint8 strategy);
    quint8 getStrategy();
    void setGoal(quint32 goal);
    quint32 getGoal();

    void search();

private:
    // Threading
    QVector<MorphLarva*> workers;
    QVector<QFuture<void>> qfs;
    QMutex mutex;

    // Analyse & cleanup / readycheck / stop
    bool stopCalc();
    bool cleanup();
    bool readycheck();
    bool analysis();

    // temporär
    void debug();

    // SuchFunktionen
    void searchChaosRandom();
    void searchOrderSort();
    void searchDanceJinJang();
    void searchDanceS();
    void searchFaculty();
    void searchFaculty(int &picked);

    // CheatCoin
    bool cheatCoin;
    bool addCheatCoin();
    bool removeCheatCoin();

    // Verschiedene Objekte
    MorphLarva* overseer;

    VectorStash* rootStash;
    VectorStash* memoryStash;
    VectorStash* solutionStash;

    NSA* nsa;
    RNGesus* rng;
    Memento* timer;

    bool success;
    quint32 goal;
    quint8 strategy;

};

#endif // MORPHLARVA_H
