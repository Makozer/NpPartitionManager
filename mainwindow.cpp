#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Wichtiger Part für die Schnittstellen
    // Erstellen der wichtigen Instanzen
    overseer = new MorphLarva();
    nsa = new NSA();
    rootStash = new VectorStash();
    solutionStash = new VectorStash();

    // Damit der overseer die zu nutzenden Sachen kennt :)
    overseer->setNSA(nsa);
    overseer->setRootStash(rootStash);
    overseer->setSolutionStash(solutionStash);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_output_root_clicked() {
    QMessageBox::information(this,
        tr("Inhalt des Schatzes"),
        tr(rootStash->display().toUtf8().constData()));
}

void MainWindow::on_btn_fill_clicked() {
    rootStash->fillRandom(50);
    solutionStash->fillRandom(25);
}

void MainWindow::on_btn_sort_clicked() {
    rootStash->quickSortDesc();
    solutionStash->quickSortDesc();
}

void MainWindow::on_btn_output_solution_clicked() {
    QMessageBox::information(this,
        tr("Inhalt des Schatzes"),
        tr(solutionStash->display().toUtf8().constData()));
}
