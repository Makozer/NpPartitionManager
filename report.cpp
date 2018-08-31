#include "report.h"

Report::Report(QString type, QString message) {
    this->type = type;
    this->message = message;
    this->timestamp = timestamp.currentDateTime();
}

QString Report::getType() {
    return type;
}

QString Report::getMessage() {
    return message;
}

QDateTime Report::getTimestamp() {
    return timestamp;
}
