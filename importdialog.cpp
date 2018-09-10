#include "importdialog.h"
#include "ui_importdialog.h"
#include <fstream>




ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}





void ImportDialog::on_btn_import_clicked()
{


    if (ui->lineEdit_importAdresse->text().size() > 0) {
        std::string streamAdresse = ui->lineEdit_importAdresse->text().toStdString();
        //Die Signale werden abgefeuert, sie geben dem mainwindow den neuen status und die streamadresse:
        emit importSignal(streamAdresse);
        emit importHatGeklapptSignal();
    }
    else {
        QMessageBox::critical(this,"Import Fehlgeschlagen", "Es wurde kein Dateipfad ausgewaehlt");
    }
    close();

}

void ImportDialog::on_btn_importAdresseWaehlen_clicked()
{
    //Das QFileDialogfenster oeffnen:
    QString ausgewaehlterPfad = QFileDialog::getOpenFileName(this,"Schatz exportieren",QDir::homePath());
    QFileDialog filedia(this,"Schatz exportieren", "C:\\");
    ui->lineEdit_importAdresse->setText(ausgewaehlterPfad);
}
