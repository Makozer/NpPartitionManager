#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QWidget>

//Diese Klasse ist eine spezielle Form des TextEdits. Das TextEdit wird um einige Attribute erweitert,
//welche den Zugriff auf den vom TextEdit dargestellten Text dynamischer gestaltet.
//Das TextEdit auf der "berechnen-page" dient als Platzhalter fuer dieses eigens erstellte TextEdit.
class CustomTextEdit : public QTextEdit {

    Q_OBJECT

private:

    //all diese Attribute stehen für einzelne Elemente, die auf der Gui
    //angezeigt werden. Diese Elemente können so jeweils einzeln
    //verändert werden.
    QString aktuellerStatus;
    QString rootstashSum;
    QString rootstashInhalt;
    QString ergebnisInformationen;
    QString anzahlCoins;
public:
    CustomTextEdit(QWidget *parent=0);

    //Diese Setter ändern jeweils die zugehörigen Attribute und rufen
    //baueGesamttext(..) auf.
    void setAktuellerStatus(QString neuerStatus);
    void setRootstashSum(QString neueRootstashSumme, QString neueAnzahlCoins);
    void setRootstashInhalt(QString neuerInhalt);
    void setErgebnisInformationen(QString neueErgebnisInfos);

    //stellt jedes der Attribute auf der Gui dar.
    //Es wird dabei jeweils dasselbe Pattern verwendet.
    void baueGesamttext(QString aktuellerStatus, QString rootstashInhalt, QString ergebnisInformationen, QString rootstashSum, QString neueAnzahlCoins);
};

#endif // CUSTOMTEXTEDIT_H
