/* Beschreibung:
 * Die Coin Klasse repräsentiert den einzelnen, simplen Wert einer Menge, zwecks Multithreading hat sie einen Copy Construktor.
 * Mithilfe des Attribues pos kann sich der Coin merken an welcher Stelle er ist, dies macht viele Algorithmen performanter und einfacher.
 * Zuständigkeit: Martin
 */
#ifndef COIN_H
#define COIN_H
#include <QString>
#include <QDebug>

class Coin {
public:
    Coin(quint16 value);
    Coin(const Coin &copyCoin);
    quint16 getValue();
    void setPos(quint16 pos);
    quint16 getPos();
private:
    quint16 pos; // Um manche Vorgänge deutlich leichter zu machen bzw redundantes suchen zu vermeiden ist es ganz gut wenn der Coin wissen KANN wo er ist :)
    quint16 value; // Der Wert vom einzelnen Coin
};

#endif // COIN_H
