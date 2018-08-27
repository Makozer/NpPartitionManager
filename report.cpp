#include "report.h"

Report::Report(QString type, QString message) {
    this->type = type;
    this->message = message;
}

QString Report::getType() {
    return type;
}

QString Report::getMessage() {
    return message;
}
