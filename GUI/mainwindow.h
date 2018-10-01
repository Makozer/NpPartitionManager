#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>
#include <QVector>
#include <QMessageBox>
#include "BackEnd/morphlarva.h"
#include "BackEnd/vectorstash.h"
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

    //empfängt die Importadresse vom importDialog, sobald der Nutzer
    //eine eingegeben hat, sodass die Menge implementiert werden kann.
    void importSlot(std::string importierterStashString);

    //Wird ausgelöst,wenn der Import geklappt hat und eine datei importiert werden konnte.
    //kann leider nicht abfangen ob tatsaechlich ein schatz importiert wurde oder nur eine beliebige datei.
    void importHatGeklapptSlot();

    //Wird ausgelöst, falls es bei der Berechnung der Partition zu keinem
    //Ergebnis kommt. Gibt dem Nutzer diese Information.
    void noSolutionSlot();

    //Wird ausgelöst, wenn die Partition gebildet werdne konnte.
    //übermittelt dem Nutzer das Ergebnis.
    void displaySolution();

    //Wird ausgelöst, wenn die Partition gebildet werdne konnte.
    //in speziellen Fällen wird dem Nutzer per message eine spezielle
    //Nachricht übermitelt, die ihm sagt, wiese die Partition nicht berechnet werden konnte.
    void catchMessage(QString message);

private slots:

    //füllt die Menge random auf.
    void on_btn_fill_clicked();

    //sortiert die Menge
    void on_btn_sort_clicked();

    //gibt die Partition der Menge aus(falls möglich)
    //bzw. berechnet die Partition
    void on_btn_output_solution_clicked();

    //fügt einen einzelnen, vom Nutzer eingegebenen Wert
    //der Menge hinzu
    void on_btn_einzelnenCoinHinzufuegen_clicked();

    //löscht die Menge
    void on_btn_clearStash_clicked();

    //exportiert eine Menge und ggf ihre Partition in eine .txt,
    //falls diese berechnet wurde.
    void on_btn_export_clicked();

    //importiert eine Menge aus einer .txt
    void on_btn_import_clicked();

    //entfernt einen Wert, den der Nutzer eingeben kann
    void on_btn_coinEntfernen_clicked();

    //sortiert das Partitionsergebnis
    void on_btn_sortErgebnis_clicked();

    //ändert die range für zufällig erstellte Werte per btn_fill
    void on_horizontalSlider_randomRangeMax_valueChanged(int value);

    //ändert die range für zufällig erstellte Werte per btn_fill
    void on_horizontalSlider_randomRangeMin_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //aendert das Intervall für zufällig erstellte Werte per btn_fill
    //und übermittelt das per GUI an den Nutzer
    void changedRandomRange();

    //für berechnung zuständig:
    MorphLarva* overseer;

    //stellt die Menge da, dessen Partition berechnet werden kann:
    VectorStash* rootStash;

    //bilden das Intervall, in dem zufällige Werte per btn_fill erstellt werden.
    int randomRangeMin;
    int randomRangeMax;
};

#endif // MAINWINDOW_H
