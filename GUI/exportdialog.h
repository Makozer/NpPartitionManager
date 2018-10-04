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
    void exportInhaltFestlegen(QString inhalt);
    void exportErgebnisFestlegen(QString ergebnis);

private slots:
    void on_btn_exportBestaetigen_clicked();

    void on_btn_exportDateiErstellen_clicked();

private:
    Ui::ExportDialog *ui;
    QString exportInhalt;
    QString exportErgebnis;
};

#endif // EXPORTDIALOG_H