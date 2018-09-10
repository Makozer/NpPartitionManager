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
#include <string>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public slots:
    void displaySolution();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeRandomRange(int min, int max);
    void changeStatus(QString neuerStatus);

public slots:
    void importSlot(std::string importierterStashString);
    void importHatGeklapptSlot();

private slots:
    void on_btn_fill_clicked();

    void on_btn_sort_clicked();

    void on_btn_output_solution_clicked();

    void on_btn_einzelnenCoinHinzufuegen_clicked();

    void on_btn_clearStash_clicked();

    void on_btn_export_clicked();

    void on_btn_import_clicked();

    void on_btn_changeRandomRange_clicked();

    void on_btn_coinEntfernen_clicked();

    void on_btn_sortErgebnis_clicked();

private:
    Ui::MainWindow *ui;


    // 6 Objekte die benötigt werden, siehe Konstruktor für zweiten Part der wichtig ist :)
    MorphLarva* overseer;
    NSA* nsa;
    VectorStash* rootStash;
    int randomRangeMin;
    int randomRangeMax;
    VectorStash* zweiterSolutionstash;

};

#endif // MAINWINDOW_H
