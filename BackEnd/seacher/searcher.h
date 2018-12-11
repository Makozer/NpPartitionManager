/* Base class of all search algorithms
 */
#ifndef SEARCHER_H
#define SEARCHER_H
#include <QString>
#include <QDebug>
#include <QThread>
#include "BackEnd/vectorstash.h"
#include "BackEnd/liststash.h"

class Searcher : public QThread {
    Q_OBJECT
signals:
    void foundSolution();
    void noSolution();
public:
    Searcher(QString name);

    virtual void search();

    bool getSuccess();
    QString getName();
    quint32 getGoal();
    VectorStash* getRootStash();

    void setSuccess(bool success);
    void setName(QString name);
    void setGoal(quint32 goal);
    void setRootStash(VectorStash* root);
protected:
    bool success;
    QString name;
    quint32 goal;

    VectorStash* rootStash;
    VectorStash* memoryStash;
};

#endif // SEARCHER_H
