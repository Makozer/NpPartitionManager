#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H


#include <QPushButton>
#include <QWidget>


//Diese Klasse erlaubt es uns einen button zu erzeugen, welcher weiß,
//ob er bereits gedrueckt wurde und der slot der
//durch ihn getriggert wurde gerade noch am arbeiten ist.
class CustomButton : public QPushButton {

    Q_OBJECT

public:
    CustomButton();

    //speichert, ob der Knopf bereits gedrückt wurde, oder nicht
    void setWurdeGeklickt(bool geklickt);

    //getter um zu erfahren, ob der Knopf gedrückt wurde und die Partition
    //bereits berechnet wird.
    inline bool getWurdeGeklickt() { return wurdeGeklickt; }

private:

    //Attribut, welches speichert, ob der Knopf gedrückt wurde.
    //notwendig um die Funktion, das berechnen abzubrechen zu implementieren.
    bool wurdeGeklickt;
};

#endif // CUSTOMBUTTON_H



