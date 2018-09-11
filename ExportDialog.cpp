#include "ExportDialog.h"
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

    //OUTDATED::BEGIN::macht er mittlerweile selbststaendig.
    //Damit der Nutzer eine moeglichst bequeme Eingabe hat fuegen die naechsten Zeielen die benoetigten
    //doppelten backslashes ein:
    //for (int i = 0; i < exportString.size(); i++) {

    //    if ( exportString[i] == '\\') {
    //        std::string tempString;

    //        for (int j = 0; j < i; j++) {
    //            tempString[j] = exportString[j];
    //        }
    //        tempString += '\\';

    //        for (int j = i; j < exportString.size(); j++) {
    //            tempString += exportString[j];
    //        }
    //        exportString = tempString;
    //    }
    //}
    //OUTDATED::ENDE

    exportStream << exportString;

    this->close();

}



void ExportDialog::on_btn_exportDateiErstellen_clicked()
{
    QString exportName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Data Text (*.txt);;All Files (*)"));
    ui->lbl_exportAdresse->setText(exportName);

    ui->btn_exportBestaetigen->setEnabled(true);
}

