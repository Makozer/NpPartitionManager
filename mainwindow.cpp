#include "mainwindow.h"
#include "ui_mainwindow.h"

//zum debuggen:
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Wichtiger Part für die Schnittstellen
    // Erstellen der wichtigen Instanzen
    overseer = new MorphLarva();
    nsa = new NSA();
    rootStash = new VectorStash();
    solutionStash = new VectorStash();

    // Damit der overseer die zu nutzenden Sachen kennt :)
    overseer->setNSA(nsa);
    overseer->setRootStash(rootStash);
    overseer->setSolutionStash(solutionStash);
}

MainWindow::~MainWindow() {
    delete ui;
}






QString MainWindow::rootstashInhaltToQString() {
    //RootstashInhalt in einem QString speichern:
    QString inhalt;
    for(int i = 0; i < rootStash->size(); i++) {


        //um das vorangehende Komma vor dem ersten EIntrag zu vermeiden wird diese Fallunterscheidung eingebaut:
        //QString::number(xxx) wird benoetigt, damit nicht das dem integer entsprechende Ascii angezeigt wird,
        //sondern die tatsaechliche zahl.
        if (inhalt == "") {
            inhalt += QString::number(rootStash->getCoinByPos(i)->getValue());
        }
        else {
            inhalt += ", ";
            inhalt += QString::number(rootStash->getCoinByPos(i)->getValue());
        }
    }

    return inhalt;
}









void MainWindow::on_btn_output_root_clicked() {
    QMessageBox::information(this,
        tr("Inhalt des Schatzes"),
        tr(rootStash->display().toUtf8().constData()));
}






void MainWindow::on_btn_fill_clicked() {

    if (ui->lineEdit_randomFuellenAnzahlEingeben->text().size() > 0) {
        //Der Nutzer uebergibt per Eingabe einen QString an das System. Hier wird er
        //in eine integervariable umgewandelt:
        int randomAnzahl = ui->lineEdit_randomFuellenAnzahlEingeben->text().toInt();
        rootStash->fillRandom(randomAnzahl);

        //neuen rootstashInhalt in einem QString speichern, QString auf Gui anzeigen:
        QString neuerInhalt = rootstashInhaltToQString();
        ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);

        //neuen Status in einem QString speichern, QString auf Gui anzeigen:
        QString neuerStatus = "Status:    Dem Schatz wurden ";
        neuerStatus += ui->lineEdit_randomFuellenAnzahlEingeben->text();
        neuerStatus += " Coins mit zufaelligen Werten hinzugefuegt.";
        ui->textEdit_partitionBerechnen->setAktuellerStatus(neuerStatus);
        ui->lineEdit_randomFuellenAnzahlEingeben->clear();
    }
    else {
        QMessageBox::critical(this,"Coins konnten nicht erstellt werden","Es wurde keine Coinanzahl im Textfeld eingegeben.");
    }
}









void MainWindow::on_btn_sort_clicked() {



    if (ui->comboBox_sortKritWaehlen->currentText() != "<Sortierkriterium>") {
        if ( rootStash->size() > 1) {

            //Die Auswahl aus der COmbobox uebernehmen:
            QString sortKriterium = ui->comboBox_sortKritWaehlen->currentText();

            //Fuer gewahltes Verfahren sortieren und sowohl Status als auch neuen
            //Inhalt in der Gui anzeigen lassen:
            if (sortKriterium == "Aufsteigend") {
                rootStash->quickSortAsc();
                QString neuerInhalt = rootstashInhaltToQString();
                ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);
                ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der Schatz wurde in aufsteigender Weise sortiert.");
            }
            else if (sortKriterium == "Absteigend") {
                rootStash->quickSortDesc();
                QString neuerInhalt = rootstashInhaltToQString();
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
    QMessageBox::information(this,
        tr("Inhalt des Schatzes"),
        tr(solutionStash->display().toUtf8().constData()));
}








void MainWindow::on_bt_einzelneCoinHinzufuegen_clicked()
{
    //Der rootstash bekommt einen neuen Coin zugewiesen. Der Wert des coins
    //wird durch den Benutzer im lineEdit eingegeben und wird von dieser Funktion
    //dem COin gegeben. Danach wird der Inhalt des Lineedits gecleart, sodass direkt
    //der naechste coinwert vom Nutzer eingetragen werden kann.



    if (ui->lineEdit_coinHinzufuegenWertEingeben->text().size() >  0) {
        int newCoinWert = ui->lineEdit_coinHinzufuegenWertEingeben->text().toInt();

        rootStash->addCoin(newCoinWert);


        //neuen rootstashInhalt in einem QString speichern und an GUI uebergeben:
        QString neuerInhalt = rootstashInhaltToQString();
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

        //Neuen Status und neuen StashInhalt auf GUI anzeigen:
        ui->textEdit_partitionBerechnen->setRootstashInhalt("leer");
        ui->textEdit_partitionBerechnen->setAktuellerStatus("Status:    Der alte Schatz wurde geloescht.");
        ui->textEdit_partitionBerechnen->setRootstashSum(QString::number(rootStash->sum()));
    }
    else {
        QMessageBox::information(this, "Schatz ist leer", "Der Schatz ist bereits leer.");
    }
}
