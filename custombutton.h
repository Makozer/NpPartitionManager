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
    CustomButton(QWidget *parent = 0);
    void setWurdeGeklickt(bool geklickt);
    inline bool getWurdeGeklickt() { return wurdeGeklickt; }

private:
    bool wurdeGeklickt;
};

#endif // CUSTOMBUTTON_H



