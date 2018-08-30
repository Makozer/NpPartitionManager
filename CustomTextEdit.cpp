#include "CustomTextEdit.h"


//Hier werden die drei Komponenten, aus denen der TExt besteht zusammengefuegt. Die Trennung
//existiert deshalb, weil man so sehr dynamisch auf jeden einzelnen Teil des TextEdit-inhaltes
//zugreifen kann. auf diese Art und weise kann jede Passage, falls benoetigt schnell geaendert werden.
//aendert sich zum Beispiel der Status, so muss nur jener veraendert werdne, ohne dass
//der Rest des Textes beruecksichitgt werden muss.
void CustomTextEdit::baueGesamttext(QString aktuellerStatus, QString rootstashInhalt, QString ergebnisInformationen, QString rootstashSum) {
    QString gesamterText;

    gesamterText += aktuellerStatus;
    gesamterText += "\n\n\n";
    gesamterText += "Inhalt des Schatzes:\n\n";
    gesamterText += "Summe aller Coinwerte: ";
    gesamterText += rootstashSum;
    gesamterText += "\n\nAlle Coins:\n";
    gesamterText += rootstashInhalt;
    gesamterText += "\n\n\n";
    gesamterText += ergebnisInformationen;

    //uebergeben an das interne QTextEdit. Dadurch wird der "gesamterText" auf der Gui dargestellt.
    this->setText(gesamterText);

}

void CustomTextEdit::setAktuellerStatus(QString neuerStatus) {
    aktuellerStatus = neuerStatus;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum);

}


void CustomTextEdit::setRootstashSum(QString neueRootstashSumme) {
    rootstashSum = neueRootstashSumme;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum);
}


void CustomTextEdit::setRootstashInhalt(QString neuerInhalt) {
    rootstashInhalt = neuerInhalt;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum);
}

void CustomTextEdit::setErgebnisInformationen(QString neueErgebnisInfos) {
    ergebnisInformationen = neueErgebnisInfos;
    baueGesamttext(aktuellerStatus, rootstashInhalt, ergebnisInformationen, rootstashSum);
}



