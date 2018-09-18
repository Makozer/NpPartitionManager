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
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeStatus(QString neuerStatus);

public slots:
    void importSlot(std::string importierterStashString);
    void importHatGeklapptSlot();
    void noSolutionSlot();
    void displaySolution(QString zeit);
    void catchMessage(QString message);

private slots:
    void on_btn_fill_clicked();

    void on_btn_sort_clicked();

    void on_btn_output_solution_clicked();

    void on_btn_einzelnenCoinHinzufuegen_clicked();

    void on_btn_clearStash_clicked();

    void on_btn_export_clicked();

    void on_btn_import_clicked();

    void on_btn_coinEntfernen_clicked();

    void on_btn_sortErgebnis_clicked();

    void on_horizontalSlider_randomRangeMax_valueChanged(int value);

    void on_horizontalSlider_randomRangeMin_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    void changedRandomRange();



    MorphLarva* overseer;
    NSA* nsa;
    VectorStash* rootStash;
    int randomRangeMin;
    int randomRangeMax;
    VectorStash* zweiterSolutionstash;

};

#endif // MAINWINDOW_H
