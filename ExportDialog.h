#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

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

private slots:
    void on_btn_exportBestaetigen_clicked();

private:
    Ui::ExportDialog *ui;
    QString exportInhalt;
};

#endif // EXPORTDIALOG_H
