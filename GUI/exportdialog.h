#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();

    //setter, um die zu exportierenden Attribute zu setzen:
    void exportInhaltFestlegen(QString inhalt);
    void exportErgebnisFestlegen(QString ergebnis);

private slots:

    //exportiert die Menge:
    void on_btn_exportBestaetigen_clicked();

    //Nutzer wählt Exportadresse:
    void on_btn_exportDateiErstellen_clicked();

private:
    Ui::ExportDialog *ui;

    //Menge, die exportiert werden soll:
    QString exportInhalt;

    //Ergebnismenge, die (falls vorhanden) exportiert werden soll:
    QString exportErgebnis;
};

#endif // EXPORTDIALOG_H
