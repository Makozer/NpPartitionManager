// Praise RNGesus
#ifndef RNGESUS_H
#define RNGESUS_H
#include <random>
#include <ctime>
#include <QString>

class RNGesus {
public:
    RNGesus();
    qint16 getRng(qint16 min, qint16 max);
};

#endif // RNGESUS_H
