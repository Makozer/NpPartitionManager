#ifndef COIN_H
#define COIN_H
#include <QString>

class Coin {
public:
    Coin(quint16 value);
    quint16 getValue();
private:
    quint16 value;
};

#endif // COIN_H
