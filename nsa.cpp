#include "nsa.h"

NSA::NSA() {
}

void NSA::add(Report *report) {
    reports.push_back(report);
}

void NSA::add(QString type, QString message) {
    mutex.lock();
    reports.push_back(new Report(type, message));
    mutex.unlock();
}

NSA::ReportList NSA::getList() {
    // Falls du in der GUI evtl. Zugriff auf die Liste brauchst :)
    return reports;
}

QString NSA::display() {
    // Ausgabe des Inhalts
    QString output = "";
    quint16 max = reports.size();
    for(quint16 i = 0; i < max; i++) {
        output += reports.at(i)->getTimestamp().toString("'Time:' h:m:s:zzz") + "; " + reports.at(i)->getType() + ";\t" + reports.at(i)->getMessage() + "\n";
    }
    return output;
}
