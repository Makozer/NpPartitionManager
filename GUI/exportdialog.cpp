#include "exportdialog.h"
#include "ui_exportdialog.h"
#include <fstream>
#include <string>

//debug:
#include <iostream>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
}

ExportDialog::~ExportDialog()
{
    delete ui;
}



void ExportDialog::exportInhaltFestlegen(QString inhalt) {
    exportInhalt = inhalt;
}

void ExportDialog::exportErgebnisFestlegen(QString ergebnis) {
    exportErgebnis = ergebnis;
}


void ExportDialog::on_btn_exportBestaetigen_clicked()
{
    std::ofstream exportStream;
    exportStream.open(ui->lbl_exportAdresse->text().toStdString());
    std::string exportString = exportInhalt.toStdString();
    exportString += "\n\n\n\n";
    exportString += exportErgebnis.toStdString();

    exportStream << exportString;

    this->close();
}



void ExportDialog::on_btn_exportDateiErstellen_clicked()
{
    QString exportName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Data Text (*.txt);;All Files (*)"));
    ui->lbl_exportAdresse->setText(exportName);


    //nur wenn der nutzer tatsaechlich einen exportpfad auswaehlt,
    //wird der button enabled, der den export bestaetigt:
    if (exportName.size() > 0) {
        ui->btn_exportBestaetigen->setEnabled(true);
    }
}

