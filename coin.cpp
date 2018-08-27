#include "coin.h"

Coin::Coin(quint16 value) {
    this->value = value;
}

quint16 Coin::getValue() {
    return value;
}
