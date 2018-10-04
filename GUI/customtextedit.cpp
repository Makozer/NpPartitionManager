#include "customtextedit.h"


//Hier werden die drei Komponenten, aus denen der TExt besteht zusammengefuegt. Die Trennung
//existiert deshalb, weil man so sehr dynamisch auf jeden einzelnen Teil des TextEdit-inhaltes
//zugreifen kann. auf diese Art und weise kann jede Passage, falls benoetigt schnell geaendert werden.
//aendert sich zum Beispiel der Status, so muss nur jener veraendert werdne, ohne dass
//der Rest des Textes beruecksichitgt werden muss.
void CustomTextEdit::baueGesamttext(QString aktuellerStatus, QString rootstashInhalt, QString ergebnisInformationen, QString rootstashSum, QString anzahlCoins) {
    QString gesamterText;

    gesamterText += aktuellerStatus;
    gesamterText += "\n\n\n";
    gesamterText += "Inhalt der Menge:\n";
    gesamterText += "Summe aller Werte: ";
    gesamterText += rootstashSum;
    gesamterText += "    Anzahl Werte: ";
    gesamterText += anzahlCoins;
    gesamterText += "\nAlle Werte:\n";
    gesamterText += rootstashInhalt;
    gesamterText += "\n\n\n\n";
    gesamterText += ergebnisInformationen;

    //uebergeben an das interne QTextEdit. Dadurch wird der "gesamterText" auf der Gui dargestellt.
    this->setText(gesamterText);

}




//die jeweiligen setter aller teile der gui:
void CustomTextEdit::setAktuellerStatus(QString neuerStatus) {
    aktuellerStatus = neuerStatus;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum, anzahlCoins);

}


void CustomTextEdit::setRootstashSum(QString neueRootstashSumme, QString neueAnzahlCoins) {
    rootstashSum = neueRootstashSumme;
    anzahlCoins = neueAnzahlCoins;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum, anzahlCoins);
}


void CustomTextEdit::setRootstashInhalt(QString neuerInhalt) {
    rootstashInhalt = neuerInhalt;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum, anzahlCoins);
}

void CustomTextEdit::setErgebnisInformationen(QString neueErgebnisInfos) {
    ergebnisInformationen = neueErgebnisInfos;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum, anzahlCoins);
}
