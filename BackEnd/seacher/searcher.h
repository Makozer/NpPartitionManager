
#ifndef SEARCHER_H
#define SEARCHER_H
#include <QString>
#include <QDebug>
#include <QThread>
#include "BackEnd/vectorstash.h"
#include "BackEnd/liststash.h"

class searcher : public QThread {
    Q_OBJECT
signals:
    void foundSolution();
    void noSolution();
public:
    searcher(QString name);

    void search();
private:
    QString name;
    quint32 goal;

    VectorStash* rootStash;
    VectorStash* memoryStash;
};

#endif // SEARCHER_H
