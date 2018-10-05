#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent) : wurdeGeklickt(false) { }

void CustomButton::setWurdeGeklickt(bool geklickt) {
    wurdeGeklickt = geklickt;
}
