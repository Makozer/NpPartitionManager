#include "importdialog.h"
#include "ui_importdialog.h"
#include <fstream>




ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog), pfad("")
{
    ui->setupUi(this);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}










void ImportDialog::on_btn_importAdresseWaehlen_clicked()
{
    //Das QFileDialogfenster oeffnen:
    QString ausgewaehlt = "Ausgewählt: ";
    pfad = QFileDialog::getOpenFileName(this,"Schatz exportieren",QDir::homePath());
    ausgewaehlt += pfad;
    QFileDialog filedia(this,"Schatz exportieren", QDir::homePath());
    ui->lbl_importAdresse->setText(ausgewaehlt);



    //falls der nutzer tatsaechlich einen Pfad auswaehlt wird der importButton enabled,
    //sodass der nutzer den import bestaetigen kann:
    if (pfad.size() > 0) {
        ui->btn_import->setEnabled(true);
    }
}








void ImportDialog::on_btn_import_clicked()
{


    if (pfad.size() > 0) {
        std::string streamAdresse = pfad.toStdString();
        //Die Signale werden abgefeuert, sie geben dem mainwindow den neuen status und die streamadresse:
        emit importSignal(streamAdresse);
        emit importHatGeklapptSignal();
        pfad.clear();
    }
    close();

}
