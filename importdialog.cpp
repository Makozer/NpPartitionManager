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

    std::string streamAdresse = ui->lineEdit_importAdresse->text().toStdString();
    //Das Signal wird abgefeuert:
    emit importSignal(streamAdresse);
    close();

}
