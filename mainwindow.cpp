#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ExportDialog.h"
#include "importdialog.h"
#include <fstream>









//Konstruktor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    //titel aendern:
    this->setWindowTitle("NP Partition Manager");


    // Erstellen der wichtigen Instanzen
    overseer = new MorphLarva();
    rootStash = new VectorStash();
    zweiterSolutionstash = new VectorStash();

    // Damit der overseer die zu nutzenden Sachen kennt:
    overseer->setRootStash(rootStash);


    //grundlegende Signal / Slot Verbindung
    QObject::connect(overseer, SIGNAL(foundSolution()), this, SLOT(displaySolution()));
    QObject::connect(overseer, SIGNAL(noSolution()), this, SLOT(noSolutionSlot()));
    QObject::connect(overseer, SIGNAL(message(QString)), this, SLOT(catchMessage(QString)));


    //standardmaessige randomRangeWerte: (Diese bestimmen, in welcher Range
    //randomisiert befuellt werden kann.)
    randomRangeMin = 1;
    randomRangeMax = 50;
}









//Destruktor
MainWindow::~MainWindow() {
    delete ui;
}












//slot bekommt signal emitted, sobald ein ergebnis fuer die partition gefunden wurde !
void MainWindow::displaySolution() {

    QString zeit = QString::number(overseer->getTimer()->getSeconds());
    //zunaechst wird der button zurueckgesetzt, welcher die berechnung startet
    //und seinen text aendert, sobald er ein mal geklickt wurde.
    //Dadurch wird er wieder zum berechnen klickbar gemacht:
    ui->btn_output_solution->setWurdeGeklickt(false);
    ui->btn_output_solution->setText("Berechnen");



    //die uebergebene durchlaufzeit speichern, damit sie nich tnur hier verwendet werden kann,
    //sondern im export.
    ui->textEdit_partitionBerechnen->setZeit(zeit);

    //das Ergebnis darstellen:
    QString ergebnisString = "Die Partition liefert folgendes Ergebnis:\n\n\n";
    ergebnisString += "Dauer: ";
    //###################################################################################################################################einheit?
    ergebnisString += ui->textEdit_partitionBerechnen->getZeit();
    ergebnisString += "\nSumme des Ergebnisses: ";
    ergebnisString += QString::number(overseer->getSolutionStash()->sum());
    ergebnisString += "    Anzahl Werte: ";
    ergebnisString += QString::number(overseer->getSolutionStash()->size());
    ergebnisString += "\nAlle Werte:\n";
    ergebnisString += overseer->getSolutionStash()->getGuiQString();
    ui->textEdit_partitionBerechnen->setErgebnisInformationen(ergebnisString);

    //neuen Status in einem QString speichern, QString auf Gui anzeigen:
    QString statusPWurdeBerechnet = "Status:    Die Partition wurde berechnet.";
    ui->textEdit_partitionBerechnen->setAktuellerStatus(statusPWurdeBerechnet);

    //enabled das sortieren des solutionstashes:
    ui->comboBox_sortKriteriumWaehlenErgebnis->setEnabled(true);
    ui->btn_sortErgebnis->setEnabled(true);


    QMessageBox::information(this, tr("Lösung gefunden!"), tr("Die Lösung für das gestellte Problem wurde gefunden!"));
}









void MainWindow::noSolutionSlot() {

    //zunaechst wird der button zurueckgesetzt, welcher die berechnung startet
    //und seinen text aendert, sobald er ein mal geklickt wurde.
    //Dadurch wird er wieder zum berechnen klickbar gemacht:
    ui->btn_output_solution->setWurdeGeklickt(false);
    ui->btn_output_solution->setText("Berechnen");




    //gibt dem nutzer die information, dass keine lösung gefunden wurde:
    QMessageBox::critical(this, "Keine Lösung gefunden", "Mit den vorliegenden Werten konnte keine Partition gebildet werden.");

    //den status aktualisieren:
    ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Es wurde versucht die Partition zu berechnen, doch es gab kein Ergebnis.");
}



void MainWindow::catchMessage(QString message) {


    //zunaechst wird der button zurueckgesetzt, welcher die berechnung startet
    //und seinen text aendert, sobald er ein mal geklickt wurde.
    //Dadurch wird er wieder zum berechnen klickbar gemacht:
    ui->btn_output_solution->setWurdeGeklickt(false);
    ui->btn_output_solution->setText("Berechnen");




    //gibt dem Nutzer die benötigten informationen, was genau in einem spezialfall,
    //der eine solche message erforderlich macht vorliegt und zu problemen führt:
    QMessageBox::critical(this, "Keine Lösung gefunden", message);
}






//Legt die neuen Grenzen fuer das randomisierte befuellen des schatzes fest:
void MainWindow::changedRandomRange() {

    //Wenn der Nutzer lustig ist und den Minimalwert groesser waehlt, als den Maximalwert:
    if (ui->horizontalSlider_randomRangeMin->value() > ui->horizontalSlider_randomRangeMax->value()) {
        QMessageBox::critical(this, "Range konnte nicht veraendert werden",
                              "Der Minimalwert wurde groesser gewaehlt als der Maximalwert. "
                              "Beide Werte werden zurueckgesetzt.");
        ui->horizontalSlider_randomRangeMin->setValue(0);
        ui->horizontalSlider_randomRangeMax->setValue(50);
    }
    else {



        //Den Status aktualisieren:
        QString changeStatus = "Status:    Random hinzugefuegte Zahlen liegen nun im Bereich zwischen ";
        changeStatus += QString::number(randomRangeMin);
        changeStatus += " und ";
        changeStatus += QString::number(randomRangeMax);
        ui->textEdit_partitionBerechnen->setAktuellerStatus(changeStatus);
    }

}










void MainWindow::on_btn_fill_clicked() {


    //Falls der Nutzer lustig drauf ist und 0 random coins hinzufuegen will:
    if (ui->lineEdit_randomFuellenAnzahlEingeben->text().toInt() == 0) {
        //dann passiert nichts! das verhindert, dass nichtmehr "leer" bei inhalt des Schatzes auf der GUI angezeigt wird.
    }

    //Falls der Nutzer eine gewoehnliche Eingabe taetigt:
    else if (ui->lineEdit_randomFuellenAnzahlEingeben->text().size() > 0) {

        //Der Nutzer uebergibt per Eingabe einen QString an das System. Hier wird er
        //in eine integervariable umgewandelt:
        int randomAnzahl = ui->lineEdit_randomFuellenAnzahlEingeben->text().toInt();

        //Es werden so viele randomisierte Coins erzeugt, wie der Nutzer es befiehlt:
        for (int i = 0; i < randomAnzahl; i++) {

            //Es werden nur Coins bis zu einem gewissen Wert erzeugt, weil riesige Groessen nichtmehr greifbar fuer den Nutzer sind.
            rootStash->addRngCoin(randomRangeMin,randomRangeMax);
        }

        //neuen rootstashInhalt in einem QString speichern, QString auf Gui anzeigen:
        QString neuerInhalt = rootStash->getGuiQString();
        ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);

        //neuen Status in einem QString speichern, QString auf Gui anzeigen:
        QString neuerStatus = "Status:    Dem Schatz wurden ";
        neuerStatus += ui->lineEdit_randomFuellenAnzahlEingeben->text();
        neuerStatus += " zufaellige Werten hinzugefuegt.";
        ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);
        ui->lineEdit_randomFuellenAnzahlEingeben->clear();

        //neue rootstashSumme in QString speichern und auf GUI anzeigen:
        QString neueRootstashSum = QString::number(rootStash->sum());
        QString neueAnzahlCoins = QString::number(rootStash->size());
        ui->textEdit_partitionBerechnen->setRootstashSum(neueRootstashSum, neueAnzahlCoins);
        ui->lineEdit_coinHinzufuegenWertEingeben->clear();



        //ggf die buttons enablen, die nur auf einen bereits bestehenden schatz angewendet werden koennen:

        //fuer die buttons, die den bestehenden schatz dezimieren:
        //falls der schatz min. einen coin enthaelt:
        if (!ui->btn_clearStash->isEnabled() && rootStash->size() > 0) {
            ui->btn_clearStash->setEnabled(true);
            ui->btn_coinEntfernen->setEnabled(true);
        }

        //fuer die elemente, die den schatz sortieren, exportieren und die partition berechnen:
        //falls der schatz min. zwei coins enthaelt:
        if (!ui->btn_output_solution->isEnabled() && rootStash->size() > 1) {
            ui->comboBox_sortKritWaehlen->setEnabled(true);
            ui->btn_sort->setEnabled(true);
            ui->btn_output_solution->setEnabled(true);
            ui->btn_export->setEnabled(true);
        }
    }
    else {
        QMessageBox::critical(this,"Werte konnten nicht erstellt werden","Es wurde keine Wertanzahl im Textfeld eingegeben.");
    }
}











void MainWindow::on_btn_sort_clicked() {

    //Der Nutzer muss vorher ein Sortierkriterium ausgewaehlt haben, bevor sortiert werden kann:
    if (ui->comboBox_sortKritWaehlen->currentText() != "<Sortierkriterium>") {


        //Die Auswahl aus der Combobox uebernehmen:
        QString sortKriterium = ui->comboBox_sortKritWaehlen->currentText();


        //Fuer gewahltes Verfahren sortieren und sowohl Status als auch neuen
        //Inhalt in der Gui anzeigen lassen:
        if (sortKriterium == "Aufsteigend") {
            rootStash->quickSortAsc();
            QString neuerInhalt = rootStash->getGuiQString();
            ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);
            ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Schatz wurde in aufsteigender Weise sortiert.");
        }
        else if (sortKriterium == "Absteigend") {
            rootStash->quickSortDesc();
            QString neuerInhalt = rootStash->getGuiQString();
            ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);
            ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Schatz wurde in aubsteigender Weise sortiert.");
        }
    }
    else {
        QMessageBox::critical(this, "Es kann nicht sortiert werden", "Es wurde kein Sortierkriterium ausgewaehlt.");
    }
}













void MainWindow::on_btn_output_solution_clicked() {

    //falls der btn waehrend der berechnung, also wiederholt geklickt wird:
    if (ui->btn_output_solution->getWurdeGeklickt()) {
        //suche komplett abbrechen ##########################################################################################################################################
        QMessageBox::information(this, "Berechnung abgebrochen", "SIe haben die Berechnung abgebrochen.");
    }

    //falls der btn das erste mal geklickt wird, so wird die partition berechnet
    else {

        //Dem Nutzer signalisieren, dass ein erneuter Klick den
        //partitionierungsvorgang abbricht, indem der Text und die
        //farbe des btn geaendert wird:
        ui->btn_output_solution->setWurdeGeklickt(true);
        ui->btn_output_solution->setText("Abbrechen");

        //um die farbe zu aendern:
        QPalette palette = ui->btn_output_solution->palette();
        palette.setColor(QPalette::Button, QColor(200,0,0));
        ui->btn_output_solution->setPalette(palette);
        ui->btn_output_solution->repaint();
        qDebug() << "abbrechen steht auf dem button"; //#############################################################################################################




        //neuen Status in einem QString speichern, QString auf Gui anzeigen:
        QString neuerStatus = "Status:    Die Partition wird berechnet.";
        ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);

        overseer->runCalc();

        //zurueckgesetzt werden wurdeGeklickt und der text des buttons in displaySolution()
        //und dessen alternativen, fuer den fall das keine loesung existiert!
    }
}













void MainWindow::on_btn_einzelnenCoinHinzufuegen_clicked()
{
    //Der rootstash bekommt einen neuen Coin zugewiesen. Der Wert des coins
    //wird durch den Benutzer im lineEdit eingegeben und wird von dieser Funktion
    //dem COin gegeben. Danach wird der Inhalt des Lineedits gecleart, sodass direkt
    //der naechste coinwert vom Nutzer eingetragen werden kann.


    //nur wenn die eingabe des nutzers mindestenz ein zeichen beinhaltet:
    if (ui->lineEdit_coinHinzufuegenWertEingeben->text().size() >  0) {
        int newCoinWert = ui->lineEdit_coinHinzufuegenWertEingeben->text().toInt();

        rootStash->addCoin(newCoinWert);


        //neuen rootstashInhalt in einem QString speichern und an GUI uebergeben:
        QString neuerInhalt = rootStash->getGuiQString();
        ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);


        //neuen Status in einem QString speichern und an GUI uebergeben:
        QString neuerStatus = "Status:    Der Wert ";
        neuerStatus += ui->lineEdit_coinHinzufuegenWertEingeben->text();
        neuerStatus += " wurde dem Schatz hinzugefuegt.";
        ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);

        //neue rootstashSumme in QString speichern und auf GUI anzeigen:
        QString neueRootstashSum = QString::number(rootStash->sum());
        QString neueAnzahlCoins = QString::number(rootStash->size());
        ui->textEdit_partitionBerechnen->setRootstashSum(neueRootstashSum, neueAnzahlCoins);
        ui->lineEdit_coinHinzufuegenWertEingeben->clear();






        //ggf die buttons enablen, die nur auf einen bereits bestehenden schatz angewendet werden koennen:

        //fuer die buttons, die den bestehenden schatz dezimieren:
        //falls der schatz min. einen coin enthaelt:
        if (!ui->btn_clearStash->isEnabled() && rootStash->size() > 0) {
            ui->btn_clearStash->setEnabled(true);
            ui->btn_coinEntfernen->setEnabled(true);
        }

        //fuer die elemente, die den schatz sortieren, exportieren und die partition berechnen:
        //falls der schatz min. zwei coins enthaelt:
        if (!ui->btn_output_solution->isEnabled() && rootStash->size() > 1) {
            ui->comboBox_sortKritWaehlen->setEnabled(true);
            ui->btn_sort->setEnabled(true);
            ui->btn_output_solution->setEnabled(true);
            ui->btn_export->setEnabled(true);
        }
    }


    //falls der nutzer also vorher keinen wert eingegeben haben sollte:
    else {
        QMessageBox::critical(this, "Wert konnte nicht erstellt werden", "Es wurde keine Wertgroesse im Textfeld eingegeben.");
    }

}













void MainWindow::on_btn_clearStash_clicked()
{


    rootStash->clear();

    //Neuen Status und neuen StashInhalt auf GUI anzeigen,sowie Ergebnis entfernen bzw das alte Ergebnis verbergen:
    ui->textEdit_partitionBerechnen->setRootstashInhalt("leer");
    ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der alte Schatz wurde geloescht.");
    ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()),QString::number(rootStash->size()));
    ui->textEdit_partitionBerechnen->setErgebnisInformationen("");


    //disablen saemtlicher funktionen, die nur auf bestehende schaetze angewendet werden koennen:
    ui->comboBox_sortKriteriumWaehlenErgebnis->setEnabled(false);
    ui->btn_sortErgebnis->setEnabled(false);
    ui->btn_export->setEnabled(false);
    ui->btn_clearStash->setEnabled(false);
    ui->btn_coinEntfernen->setEnabled(false);
    ui->comboBox_sortKritWaehlen->setEnabled(false);
    ui->btn_sort->setEnabled(false);
    ui->btn_output_solution->setEnabled(false);
}















void MainWindow::importSlot(std::string importierterStashString) {

    std::ifstream schatzImportStream;
    schatzImportStream.open(importierterStashString);
    std::string eingeleseneZeile;
    QString qZeile;
    int newCoinValue;
    int letztesKommaMarkierer = 0;

    rootStash->clear();


    //Es werden jeweils substrings erstellt, um die einzelnen coinvalues aus der .txt einzulesen. Die Kommata, die als
    //Trennzeichen fungieren dienen als Orientierung und duerfen natuerlich nicht in die values mit aufgenommen werden:
    while(getline(schatzImportStream,eingeleseneZeile)) {
        qZeile = QString::fromStdString(eingeleseneZeile);


        //Es wird ueber die gesamte eingelesene Zeile iteriert:
        for(int i = 0; i < eingeleseneZeile.size(); i++) {

            //Fuer den allerletzten Coin:
            if(i == (eingeleseneZeile.size() - 1)) {
                newCoinValue = qZeile.mid(letztesKommaMarkierer + 1).toInt();
                rootStash->addCoin(newCoinValue);
            }

            //Fuer den allerersten Coin:
            else if (letztesKommaMarkierer == 0 && eingeleseneZeile[i] == ',') {
                newCoinValue = qZeile.left(i).toInt();
                rootStash->addCoin(newCoinValue);
                letztesKommaMarkierer = i;
            }

            //Fuer alle Coins dazwischen:
            else if (eingeleseneZeile[i] == ',') {
                newCoinValue = qZeile.mid((letztesKommaMarkierer + 1), i - (letztesKommaMarkierer + 1)).toInt();
                rootStash->addCoin(newCoinValue);
                letztesKommaMarkierer = i;
            }
        }
    }


    //Den stashinhalt und die stashsumme auf der Gui anzeigen:
    ui->textEdit_partitionBerechnen->setRootstashInhalt(rootStash->getGuiQString());
    ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()), QString::number(rootStash->size()));



    //ggf die buttons enablen, die nur auf einen bereits bestehenden schatz angewendet werden koennen:

    //fuer die buttons, die den bestehenden schatz dezimieren oder exportieren:
    //falls der schatz min. einen coin enthaelt:
    if (!ui->btn_clearStash->isEnabled() && rootStash->size() > 0) {
        ui->btn_clearStash->setEnabled(true);
        ui->btn_coinEntfernen->setEnabled(true);
        ui->btn_export->setEnabled(true);
    }

    //fuer die elemente, die den schatz sortieren und die partition berechnen:
    //falls der schatz min. zwei coins enthaelt:
    if (!ui->btn_output_solution->isEnabled() && rootStash->size() > 1) {
        ui->comboBox_sortKritWaehlen->setEnabled(true);
        ui->btn_sort->setEnabled(true);
        ui->btn_output_solution->setEnabled(true);
    }
}









//Wird ausgeloest,wenn der Import geklappt hat und eine datei importiert werden konnte.
//kann leider nicht abfangen ob tatsaechlich ein schatz importiert wurde oder nur eine beliebige datei.
void MainWindow::importHatGeklapptSlot() {
    ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Ein Schatz wurde importiert.");
}









void MainWindow::on_btn_export_clicked()
{
    //das Dialogfenster oeffnen:
    ExportDialog exportDia;
    exportDia.setModal(true);
    exportDia.setFixedHeight(180);
    exportDia.setFixedWidth(400);

    //Daten uebergeben:

    //stashinhalt:
    QString inhaltsString = "Inhalt des Schatzes:\n";
    inhaltsString += "Summe aller Werte: ";
    inhaltsString += QString::number(rootStash->sum());
    inhaltsString += "    Anzahl Werte: ";
    inhaltsString += QString::number(rootStash->size());
    inhaltsString += "\nAlle Werte:\n";
    inhaltsString += rootStash->getQString();
    exportDia.exportInhaltFestlegen(inhaltsString);

    //ggf ergebnis mit uebergeben, falls es eines gibt:
    if (overseer->hasSuccess()) {
        QString ergebnisString = "Die Partition liefert folgendes Ergebnis:\n\n\n";
        ergebnisString += "Dauer: ";
        //###################################################################################################################################einheit?
        ergebnisString += ui->textEdit_partitionBerechnen->getZeit();
        ergebnisString += "\nSumme des Ergebnisses: ";
        ergebnisString += QString::number(overseer->getSolutionStash()->sum());
        ergebnisString += "    Anzahl Werte: ";
        ergebnisString += QString::number(overseer->getSolutionStash()->size());
        ergebnisString += "\nAlle Werte:\n";
        ergebnisString += overseer->getSolutionStash()->getGuiQString();
        exportDia.exportErgebnisFestlegen(ergebnisString);
    }
    else {
        exportDia.exportErgebnisFestlegen("");
    }

    exportDia.exec();


    //neuen Status in einem QString speichern und an GUI uebergeben:
    QString neuerStatus = "Status:    Der Inhalt des Schatzes wurde exportiert.";
    ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);
}











void MainWindow::on_btn_import_clicked()
{

    //das Dialogfenster oeffnen:
    ImportDialog *importDia = new ImportDialog();
    importDia->setModal(true);
    importDia->setFixedHeight(180);
    importDia->setFixedWidth(400);

    //Die connect verbindet die beide Fenster per SIGNAL-->SLOT.
    //Dadurch koennen per Event(signal) Informationen zwischen Klassen
    //transportiert werden.(in den Slot)
    QObject::connect(importDia,SIGNAL(importSignal(std::string)),this,SLOT(importSlot(std::string)));
    QObject::connect(importDia,SIGNAL(importHatGeklapptSignal()),this,SLOT(importHatGeklapptSlot()));

    importDia->exec();


}


















void MainWindow::changeStatus(QString neuerStatus) {
    ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);
}












void MainWindow::on_btn_coinEntfernen_clicked()
{

    //uebernimmt den vom Nutzer eingegebenen Wert und falls ein Coin im Schatz diesen
    //Wert besitzt wird EIN entsprechender Coin entfernt. Falls es keinen Coin mit dem
    //eingegebenen Wert gibt, so wird eine Messagebox angezeigt:

    //Nutzerwunschwert speichern:
    int zuEntfernenderWert = ui->lineEdit_coinEntfernen->text().toInt();


    //suchalgorithmus ###################################################################################################################################################################################
    //checken,ob ein Coin des Schatzes den entsprechenden Wert besitz:
    bool found = false;
    for (int i = 0; i < rootStash->size(); i++) {
        if (rootStash->getCoinByPos(i)->getValue() == zuEntfernenderWert) {
            rootStash->removeCoinByValue(zuEntfernenderWert);
            found = true;

            //beendet die suche: (break ginge auch)
            i = rootStash->size();
        }
    }


    //Wenn kein entsprechender Coin existiert wird eine ensprechende Nachricht in einer Messagebox ausgegeben:
    QString fehlermeldung = "In diesem Schatz existiert kein Wert der Groesse ";
    fehlermeldung += ui->lineEdit_coinEntfernen->text();
    if (!found) {
        QMessageBox::critical(this, "Wert konnte nicht entfernt werden.", fehlermeldung);
    }



    //Status, Stashsumme und Stashinhalt wird aktualisiert und auf Gui angezeigt:

    QString neuerStatus = "Status:    Der Wert ";
    neuerStatus += ui->lineEdit_coinEntfernen->text();
    neuerStatus += " wurde aus dem Schatz entfernt.";

    //Damit nicht einfach nichts als inhalt fuer den rootstash steht, steht dort, falls der stash leer ist "leer"
    if (rootStash->size() > 0) {
        ui->textEdit_partitionBerechnen->setRootstashInhalt(rootStash->getGuiQString());
    }
    else {
        ui->textEdit_partitionBerechnen->setRootstashInhalt("leer");
    }

    ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);
    ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()), QString::number(rootStash->size()));


    //falls vorher ein Ergebnis existiert hat wird es hiermit verborgen, sodass der Nutzer nicht den
    //rootstash aendert und dazu ein falsches ergebnis angezeigt bekomt:
    ui->textEdit_partitionBerechnen->setErgebnisInformationen("");

    ui->lineEdit_coinEntfernen->clear();



    //ggf die buttons disablen, die nur auf einen bereits bestehenden schatz angewendet werden koennen:

    //fuer die buttons, die den bestehenden schatz dezimieren, oder exportieren:
    //falls der schatz weniger als einen coin enthaelt:
    if (ui->btn_clearStash->isEnabled() && rootStash->size() == 0) {
        ui->btn_clearStash->setEnabled(false);
        ui->btn_coinEntfernen->setEnabled(false);
        ui->btn_export->setEnabled(false);
    }

    //fuer die elemente, die den schatz sortieren und die partition berechnen:
    //falls der schatz weniger als zwei coins enthaelt:
    if (ui->btn_output_solution->isEnabled() && rootStash->size() < 2) {
        ui->comboBox_sortKritWaehlen->setEnabled(false);
        ui->btn_sort->setEnabled(false);
        ui->btn_output_solution->setEnabled(false);
    }
}












void MainWindow::on_btn_sortErgebnis_clicked() {

    if (ui->comboBox_sortKriteriumWaehlenErgebnis->currentText() != "<Sortierkriterium>") {

        if (overseer->hasSuccess()) {

            //Die Auswahl aus der Combobox uebernehmen:
            QString sortKriterium = ui->comboBox_sortKriteriumWaehlenErgebnis->currentText();

            //Fuer gewahltes Verfahren sortieren und sowohl Status als auch neuen
            //Inhalt in der Gui anzeigen lassen:
            if (sortKriterium == "Aufsteigend") {
                overseer->getSolutionStash()->quickSortAsc();

                //QString fuer die GUI-anzeigen erstellen:
                QString inhalt = "Die Partition liefert folgendes Ergebnis:\n\n";
                inhalt += overseer->getSolutionStash()->getGuiQString();
                inhalt += "\n\nSumme des Ergebnisses: ";
                inhalt += QString::number(overseer->getSolutionStash()->sum());
                inhalt += "    Anzahl Werte: ";
                inhalt += QString::number(overseer->getSolutionStash()->size());



                //Die Gui-anzeigen aktualisieren:
                ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Ergebnisschatz wurde in aufsteigender Weise sortiert.");
                ui->textEdit_partitionBerechnen->setErgebnisInformationen(inhalt);
            }
            else if (sortKriterium == "Absteigend") {
                overseer->getSolutionStash()->quickSortDesc();


                //QString fuer die GUI-anzeigen erstellen:
                QString inhalt = "Die Partition liefert folgendes Ergebnis:\n\n";
                inhalt += overseer->getSolutionStash()->getGuiQString();
                inhalt += "\n\nSumme des Ergebnisses: ";
                inhalt += QString::number(overseer->getSolutionStash()->sum());
                inhalt += "    Anzahl Werte: ";
                inhalt += QString::number(overseer->getSolutionStash()->size());



                //Die Gui-anzeigen aktualisieren:
                ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Ergebnisschatz wurde in absteigender Weise sortiert.");
                ui->textEdit_partitionBerechnen->setErgebnisInformationen(inhalt);
            }
        }


        //eigentlich irrelevant durch das disablen des buttons aber man wiess ja nie ###########################################################################################################################################################################################
        else {
            QMessageBox::critical(this,"Es kann nicht sortiert werden", "Es liegt kein Ergebnisschatz vor, der sortiert werden koennte.");
        }
    }
    else {
        QMessageBox::critical(this, "Es kann nicht sortiert werden", "Es wurde kein Sortierkriterium ausgewaehlt.");
    }
}





void MainWindow::on_horizontalSlider_randomRangeMax_valueChanged(int value)
{
    randomRangeMax = value;
    changedRandomRange();
}





void MainWindow::on_horizontalSlider_randomRangeMin_valueChanged(int value)
{
    randomRangeMin = value;
    changedRandomRange();
}
