#include "coin.h"

Coin::Coin(quint16 value) {
    if (value > 0) {
        this->value = value;
    } else {
        QString error = "Error: irgendwer hat versucht einen Coin mit dem Wert 0 zu erstellen ...";
        throw std::runtime_error(error.toStdString());
    }
}

Coin::Coin(const Coin &copyCoin) {
    this->value = copyCoin.value;
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
