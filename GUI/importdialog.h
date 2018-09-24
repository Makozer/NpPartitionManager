#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include "vectorstash.h"
#include <string>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();

signals:
    void importSignal(std::string importierterStashString);
    void importHatGeklapptSignal();

private slots:
    void on_btn_import_clicked();

    void on_btn_importAdresseWaehlen_clicked();

private:
    Ui::ImportDialog *ui;
    QString pfad;

};

#endif // IMPORTDIALOG_H
