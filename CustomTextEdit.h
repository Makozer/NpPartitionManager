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
    QString aktuellerStatus;
    QString rootstashSum;
    QString rootstashInhalt;
    QString ergebnisInformationen;
    QString anzahlCoins;
public:
    CustomTextEdit(QWidget *parent=0) : aktuellerStatus("Status:    Es wurde noch nichts getan."), rootstashInhalt("leer"), ergebnisInformationen(""), rootstashSum("0"), anzahlCoins("0")  { baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum, anzahlCoins); }
    void setAktuellerStatus(QString neuerStatus);
    void setRootstashSum(QString neueRootstashSumme, QString neueAnzahlCoins);
    void setRootstashInhalt(QString neuerInhalt);
    void setErgebnisInformationen(QString neueErgebnisInfos);
    void baueGesamttext(QString aktuellerStatus, QString rootstashInhalt, QString ergebnisInformationen, QString rootstashSum, QString neueAnzahlCoins);
};

#endif // CUSTOMTEXTEDIT_H
