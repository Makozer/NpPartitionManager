#ifndef NSA_H
#define NSA_H
#include <QMutex>
#include <vector>
#include "report.h"


class NSA {
    typedef std::vector<Report*> ReportList;
public:
    NSA();
    void add(Report* report);
    void add(QString type, QString message);
    ReportList getList();
    QString display();
    QString display(quint16 size);
private:
    ReportList reports;
    QMutex mutex;
};

#endif // NSA_H
