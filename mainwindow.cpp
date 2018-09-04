#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ExportDialog.h"
#include "importdialog.h"
#include <fstream>









MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Wichtiger Part für die Schnittstellen
    // Erstellen der wichtigen Instanzen
    overseer = new MorphLarva();
    nsa = new NSA();
    rootStash = new VectorStash();
    zweiterSolutionstash = new VectorStash();


    // Damit der overseer die zu nutzenden Sachen kennt :)
    overseer->setNSA(nsa);
    overseer->setRootStash(rootStash);

    //standardmaessige randomRangeWerte: (Diese bestimmen, in welcher Range
    //randomisiert befuellt werden kann.)
    randomRangeMin = 1;
    randomRangeMax = 100;
}









MainWindow::~MainWindow() {
    delete ui;
}





//Legt die neuen Grenzen fuer das randomisierte befuellen des schatzes fest:
void MainWindow::changeRandomRange(int min, int max) {
    randomRangeMin = min;
    randomRangeMax = max;
}







void MainWindow::on_btn_fill_clicked() {


    //Falls der Nutzer lustig drauf ist und 0 random coins hinzufuegen will:
    if (ui->lineEdit_randomFuellenAnzahlEingeben->text().toInt() == 0) {
        //dann passiert nichts! das verhindert, dass nichtmehr "ller" bei inhalt des Schatzes auf der GUI angezeigt wird.
    }

    //Falls der Nutzer eine gewoehnliche Eingabe taetigt:
    else if (ui->lineEdit_randomFuellenAnzahlEingeben->text().size() > 0) {

        //Der Nutzer uebergibt per Eingabe einen QString an das System. Hier wird er
        //in eine integervariable umgewandelt:
        int randomAnzahl = ui->lineEdit_randomFuellenAnzahlEingeben->text().toInt();

        //Es werden so viele randomisierte Coins erzeugt, wie der Nutzer es befiehlt:
        for (int i = 0; i < randomAnzahl; i++) {

            //ACHTUNG::MaxWert muss noch festgelegt werden
            //Es werden nur Coins bis zu einem gewissen Wert erzeugt, weil riesige Groessen nichtmehr greifbar fuer den Nutzer sind.
            rootStash->addRngCoin(randomRangeMin,randomRangeMax);
        }

        //neuen rootstashInhalt in einem QString speichern, QString auf Gui anzeigen:
        QString neuerInhalt = rootStash->getGuiQString();
        ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);

        //neuen Status in einem QString speichern, QString auf Gui anzeigen:
        QString neuerStatus = "Status:    Dem Schatz wurden ";
        neuerStatus += ui->lineEdit_randomFuellenAnzahlEingeben->text();
        neuerStatus += " Coins mit zufaelligen Werten hinzugefuegt.";
        ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);
        ui->lineEdit_randomFuellenAnzahlEingeben->clear();

        //neue rootstashSumme in QString speichern und auf GUI anzeigen:
        QString neueRootstashSum = QString::number(rootStash->sum());
        ui->textEdit_partitionBerechnen->setRootstashSum(neueRootstashSum);
        ui->lineEdit_coinHinzufuegenWertEingeben->clear();
    }
    else {
        QMessageBox::critical(this,"Coins konnten nicht erstellt werden","Es wurde keine Coinanzahl im Textfeld eingegeben.");
    }
}










void MainWindow::on_btn_sort_clicked() {



    if (ui->comboBox_sortKritWaehlen->currentText() != "<Sortierkriterium>") {
        if ( rootStash->size() > 1) {

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
            QMessageBox::critical(this,"Es kann nicht sortiert werden", "Der Schatz ist zu klein, als dass er sortiert werden koennte.");
        }
    }
    else {
        QMessageBox::critical(this, "Es kann nicht sortiert werden", "Es wurde kein Sortierkriterium ausgewaehlt.");
    }
}












void MainWindow::on_btn_output_solution_clicked() {

    //neuen Status in einem QString speichern, QString auf Gui anzeigen:
    QString neuerStatus = "Status:    Die Partition wird berechnet.";
    ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);


    overseer->run();
    QString ergebnisString = "Die Partition liefert folgendes Ergebnis:\n\n";
    ergebnisString += overseer->getSolutionStash()->getGuiQString();
    ergebnisString += "\n\nSumme des Ergebnisses: ";
    ergebnisString += QString::number(overseer->getSolutionStash()->sum());

    ui->textEdit_partitionBerechnen->setErgebnisInformationen(ergebnisString);

    //neuen Status in einem QString speichern, QString auf Gui anzeigen:
    QString statusPWurdeBerechnet = "Status:    Die Partition wurde berechnet.";
    ui->textEdit_partitionBerechnen->setAktuellerStatus(statusPWurdeBerechnet);





    //QMessageBox::information(this, tr("NSA Report"), tr(this->nsa->display().toUtf8().constData()));
    //QMessageBox::information(this, tr("Loesung"), tr(this->overseer->getSolutionStash()->display().toUtf8().constData()));
}












void MainWindow::on_btn_einzelnenCoinHinzufuegen_clicked()
{
    //Der rootstash bekommt einen neuen Coin zugewiesen. Der Wert des coins
    //wird durch den Benutzer im lineEdit eingegeben und wird von dieser Funktion
    //dem COin gegeben. Danach wird der Inhalt des Lineedits gecleart, sodass direkt
    //der naechste coinwert vom Nutzer eingetragen werden kann.



    if (ui->lineEdit_coinHinzufuegenWertEingeben->text().size() >  0) {
        int newCoinWert = ui->lineEdit_coinHinzufuegenWertEingeben->text().toInt();

        rootStash->addCoin(newCoinWert);


        //neuen rootstashInhalt in einem QString speichern und an GUI uebergeben:
        QString neuerInhalt = rootStash->getGuiQString();
        ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);


        //neuen Status in einem QString speichern und an GUI uebergeben:
        QString neuerStatus = "Status:    Ein Coin mit dem Wert ";
        neuerStatus += ui->lineEdit_coinHinzufuegenWertEingeben->text();
        neuerStatus += " wurde dem Schatz hinzugefuegt.";
        ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);

        //neue rootstashSumme in QString speichern und auf GUI anzeigen:
        QString neueRootstashSum = QString::number(rootStash->sum());
        ui->textEdit_partitionBerechnen->setRootstashSum(neueRootstashSum);
        ui->lineEdit_coinHinzufuegenWertEingeben->clear();
    }
    else {
        QMessageBox::critical(this, "Coin konnte nicht erstellt werden", "Es wurde kein Coinwert im Textfeld eingegeben.");
    }

}











void MainWindow::on_btn_clearStash_clicked()
{

    if (rootStash->size() > 0) {
        rootStash->clear();

        //Neuen Status und neuen StashInhalt auf GUI anzeigen,sowie Ergebnis entfernen:
        ui->textEdit_partitionBerechnen->setRootstashInhalt("leer");
        ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der alte Schatz wurde geloescht.");
        ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()));
        ui->textEdit_partitionBerechnen->setErgebnisInformationen("");
    }
    else {
        QMessageBox::information(this, "Schatz ist leer", "Der Schatz ist bereits leer.");
    }
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
                newCoinValue = qZeile.mid(letztesKommaMarkierer + 2).toInt();
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
                newCoinValue = qZeile.mid((letztesKommaMarkierer + 2), i - (letztesKommaMarkierer + 2)).toInt();
                rootStash->addCoin(newCoinValue);
                letztesKommaMarkierer = i;
            }
        }
    }


    //Den Status, den stashinhalt und die stashsumme auf der Gui anzeigen:
    ui->textEdit_partitionBerechnen->setRootstashInhalt(rootStash->getGuiQString());
    ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Ein Schatz wurde importiert.");
    ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()));
}












void MainWindow::on_btn_export_clicked()
{


    //das Dialogfenster oeffnen:
    ExportDialog exportDia;
    exportDia.setModal(true);
    exportDia.setFixedHeight(156);
    exportDia.setFixedWidth(400);

    //Daten uebergeben:

    //stashginhalt:
    QString inhaltsString = "Inhalt des Schatzes:\n";
    inhaltsString += "Summe aller Coinwerte: ";
    inhaltsString += QString::number(rootStash->sum());
    inhaltsString += "\nAlle Coins:\n";
    inhaltsString += rootStash->getQString();
    exportDia.exportInhaltFestlegen(inhaltsString);

    //ggf ergebnis mit uebergeben, falls es eines gibt:
    if (overseer->hasSuccess()) {
        QString ergebnisString = "Die Partition liefert folgendes Ergebnis:\n";
        ergebnisString += overseer->getSolutionStash()->getQString();
        ergebnisString += "\n\nSumme des Ergebnisses: ";
        ergebnisString += QString::number(overseer->getSolutionStash()->sum());
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
    importDia->setFixedHeight(156);
    importDia->setFixedWidth(400);

    //Die connect verbindet die beide Fenster per SIGNAL-->SLOT.
    //Dadurch koennen per Event(signal) Informationen zwischen Klassen
    //transportiert werden.(in den Slot)
    QObject::connect(importDia,SIGNAL(importSignal(std::string)),this,SLOT(importSlot(std::string)));

    importDia->exec();


}









void MainWindow::on_btn_changeRandomRange_clicked()
{

    //Wenn der Nutzer lustig ist und den Minimalwert groesser waehlt, als den Maximalwert:
    if (ui->horizontalSlider_randomRangeMin->value() > ui->horizontalSlider_randomRangeMax->value()) {
        QMessageBox::critical(this, "Range konnte nicht veraendert werden", "Der Minimalwert wurde groesser gewaehlt als der Maximalwert.");
    }
    else {

        //setzt den neuen Bereich fest und informiert den Nutzer:
        randomRangeMin = ui->horizontalSlider_randomRangeMin->value();
        randomRangeMax = ui->horizontalSlider_randomRangeMax->value();
        QMessageBox::information(this, "Erfolg", "Die Range wurde erfolgreich geaendert.");

        //Den Status aktualisieren:
        QString changeStatus = "Status:    Random hinzugefuegte Zahlen liegen nun im Bereich zwischen ";
        changeStatus += QString::number(randomRangeMin);
        changeStatus += " und ";
        changeStatus += QString::number(randomRangeMax);
        ui->textEdit_partitionBerechnen->setAktuellerStatus(changeStatus);
    }
}











void MainWindow::on_btn_coinEntfernen_clicked()
{

    //uebernimmt den vom Nutzer eingegebenen Wert und falls ein Coin im Schatz diesen
    //Wert besitzt wird EIN entsprechender Coin entfernt. Falls es keinen Coin mit dem
    //eingegebenen Wert gibt, so wird eine Messagebox angezeigt:

    //Nutzerwunschwert speichern:
    int zuEntfernenderWert = ui->lineEdit_coinEntfernen->text().toInt();


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
    QString fehlermeldung = "In diesem Schatz existiert kein Coin mit dem Wert ";
    fehlermeldung += ui->lineEdit_coinEntfernen->text();
    if (!found) {
        QMessageBox::critical(this, "Coin konnte nicht entfernt werden.", fehlermeldung);
    }



    //Status, Stashsumme und Stashinhalt wird aktualisiert und auf Gui angezeigt:

    QString neuerStatus = "Status:    Ein Coin mit dem Wert ";
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
    ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()));

    ui->lineEdit_coinEntfernen->clear();
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



                //Die Gui-anzeigen aktualisieren:
                ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Ergebnisschatz wurde in absteigender Weise sortiert.");
                ui->textEdit_partitionBerechnen->setErgebnisInformationen(inhalt);
            }
            else if (sortKriterium == "Absteigend") {
                overseer->getSolutionStash()->quickSortDesc();


                //QString fuer die GUI-anzeigen erstellen:
                QString inhalt = "Die Partition liefert folgendes Ergebnis:\n\n";
                inhalt += overseer->getSolutionStash()->getGuiQString();
                inhalt += "\n\nSumme des Ergebnisses: ";
                inhalt += QString::number(overseer->getSolutionStash()->sum());



                //Die Gui-anzeigen aktualisieren:
                ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Ergebnisschatz wurde in absteigender Weise sortiert.");
                ui->textEdit_partitionBerechnen->setErgebnisInformationen(inhalt);
            }
        }
        else {
            QMessageBox::critical(this,"Es kann nicht sortiert werden", "Es liegt kein Ergebnisschatz vor, der sortiert werden koennte.");
        }
    }
    else {
        QMessageBox::critical(this, "Es kann nicht sortiert werden", "Es wurde kein Sortierkriterium ausgewaehlt.");
    }
}
