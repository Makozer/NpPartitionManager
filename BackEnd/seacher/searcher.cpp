#include "searcher.h"

searcher::searcher(QString name) {
    this->name = name;
    qDebug() << name << " has been created ...";
}
