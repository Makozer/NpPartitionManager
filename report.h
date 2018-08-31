#ifndef REPORT_H
#define REPORT_H
#include <QString>
#include <QDateTime>

class Report {
public:
    Report(QString type, QString message);
    QString getType();
    QString getMessage();
    QDateTime getTimestamp();
private:
    QString type;
    QString message;
    QDateTime timestamp;
};

#endif // REPORT_H
