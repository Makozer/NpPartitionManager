#ifndef CUSTOMONLYNUMBERSLINEEDIT_H
#define CUSTOMONLYNUMBERSLINEEDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QIntValidator>

//Die LineEdits in unserer Gui dienen als Platzhalter fuer diese spezialisierten lineEdits.
//Das erlaubt uns, dass die lineEdits lediglich Zahlen eingegeben bekommen koennnen.
//Dadurch erspart man sich die Konsequenzen, die aus falschen Nutzereingaben resultieren koennten.
class CustomOnlyNumbersLineEdit : public QLineEdit {

    Q_OBJECT

public:
    CustomOnlyNumbersLineEdit(QWidget *parent = 0);
};

#endif // CUSTOMONLYNUMBERSLINEEDIT_H
