#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>
#include <QVector>
#include <QMessageBox>
#include "morphlarva.h"
#include "vectorstash.h"
#include "nsa.h"
#include "CustomTextEdit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString rootstashInhaltToQString();

private slots:
    void on_btn_fill_clicked();

    void on_btn_sort_clicked();

    void on_btn_output_root_clicked();

    void on_btn_output_solution_clicked();

    void on_bt_einzelneCoinHinzufuegen_clicked();

private:
    Ui::MainWindow *ui;

    // 4 Objekte die benötigt werden, siehe Konstruktor für zweiten Part der wichtig ist :)
    MorphLarva* overseer;
    NSA* nsa;
    VectorStash* rootStash;
    VectorStash* solutionStash;
};

#endif // MAINWINDOW_H
