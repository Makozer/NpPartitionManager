#include "CustomOnlyNumbersLineEdit.h"

CustomOnlyNumbersLineEdit::CustomOnlyNumbersLineEdit(QWidget *parent)
{
    //Ermoeglicht die Eingabe von Zahlen bis 16959 und verhindert somit
    //abgesehen von unsigned ist 16959 die maximal erreichbare Groesse.
    //Die Eingabe von Buchstaben:
    setValidator( new QIntValidator(0, 16959, this) );
}
