#ifndef REPORT_H
#define REPORT_H
#include <QString>

class Report {
public:
    Report(QString type, QString message);
    QString getType();
    QString getMessage();
private:
    QString type;
    QString message;
    // Timestamp
};

#endif // REPORT_H
