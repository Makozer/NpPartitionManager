#include "coin.h"

Coin::Coin(quint16 value) {
    this->value = value;
}

quint16 Coin::getValue() {
    return value;
}

void Coin::setPos(quint16 pos) {
    this->pos = pos;
}

quint16 Coin::getPos() {
    return pos;
}
