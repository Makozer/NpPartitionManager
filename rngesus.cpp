#include "rngesus.h"

RNGesus::RNGesus() {
    srand((unsigned)time(0));
}

qint16 RNGesus::getRng(qint16 min, qint16 max) {
    return (rand() % (max - min + 1)) + min;
}
