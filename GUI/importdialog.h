#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include "BackEnd/vectorstash.h"
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

    //übergibt die importierte Menge an das mainwindow:
    void importSignal(std::string importierterStashString);

    //wenn import erfolgreich war, damit der Status aktualisiert wird:
    void importHatGeklapptSignal();

private slots:

    //bestätigt den Import:
    void on_btn_import_clicked();

    //Nutzer wählt importadresse:
    void on_btn_importAdresseWaehlen_clicked();

private:
    Ui::ImportDialog *ui;

    //pfad, aus dem importiert werden soll:
    QString pfad;

};

#endif // IMPORTDIALOG_H
