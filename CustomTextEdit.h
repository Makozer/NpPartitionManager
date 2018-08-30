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
    QString rootstashInhalt;
    QString ergebnisInformationen;
public:
    CustomTextEdit(QWidget *parent=0) : aktuellerStatus("Status"), rootstashInhalt("leer"), ergebnisInformationen("") { baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen); }
    void setAktuellerStatus(QString neuerStatus);
    void setRootstashInhalt(QString neuerInhalt);
    void setErgebnisInformationen(QString neueErgebnisInfos);
    void baueGesamttext(QString aktuellerStatus, QString rootstashInhalt, QString ergebnisInformationen);
};

#endif // CUSTOMTEXTEDIT_H
