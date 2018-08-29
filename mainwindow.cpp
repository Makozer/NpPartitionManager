#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_btn_output_root_clicked() {
    QMessageBox::information(this,
        tr("Inhalt des Schatzes"),
        tr(rootStash->display().toUtf8().constData()));
}

void MainWindow::on_btn_fill_clicked() {
    rootStash->fillRandom(50);
    solutionStash->fillRandom(25);
}

void MainWindow::on_btn_sort_clicked() {
    rootStash->quickSortDesc();
    solutionStash->quickSortDesc();
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
        ui->lineEdit_coinHinzufuegenWertEingeben->clear();

        //neuen rootstashInhalt in einem QString speichern:
        QString neuerInhalt;
        for(int i = 0; i < rootStash->size(); i++) {


            //um das vorangehende Komma vor dem ersten EIntrag zu vermeiden wird diese Fallunterscheidung eingebaut:
            //QString::number(xxx) wird benoetigt, damit nicht das dem integer entsprechende Ascii angezeigt wird,
            //sondern die tatsaechliche zahl.
            if (neuerInhalt == "") {
                neuerInhalt += QString::number(rootStash->getCoinByPos(i)->getValue());
            }
            else {
                neuerInhalt += ", ";
                neuerInhalt += QString::number(rootStash->getCoinByPos(i)->getValue());
            }
        }

        ui->textEdit_partitionBerechnen->setRootstashInhalt(neuerInhalt);
    }
    else {
        QMessageBox::critical(this, "Coin konnte nicht erstellt werden", "Es wurde kein Coinwert im Textfeld eingegeben.");
    }

}
