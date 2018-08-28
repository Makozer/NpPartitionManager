#ifndef COIN_H
#define COIN_H
#include <QString>

class Coin {
public:
    Coin(quint16 value);
    quint16 getValue();
    void setPos(quint16 pos);
    quint16 getPos();
private:
    quint16 pos; // Um manche Vorgänge deutlich leichter zu machen bzw redundantes suchen zu vermeiden ist es ganz gut wenn der Coin wissen KANN wo er ist :)
    quint16 value;
};

#endif // COIN_H
