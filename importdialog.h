#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include "vectorstash.h"
#include <string>

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

private slots:
    void on_btn_import_clicked();

private:
    Ui::ImportDialog *ui;

};

#endif // IMPORTDIALOG_H
