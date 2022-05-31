#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(customChartView);

    newAct = ui->actionNew;
    saveAct = ui->actionSave;
    openAct = ui->actionOpen;

    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save() {
    ui->statusbar->showMessage("Saving...");
    QString newPath = QFileDialog::getOpenFileName(this, tr("Save"), QDir::home().absolutePath(), tr("Json"));
    if (!newPath.isEmpty()){
        fileManager->write(customChartView->getData(), newPath);
    }
}

void MainWindow::open() {
   ui->statusbar->showMessage("Open...");
   QString newPath = QFileDialog::getOpenFileName(this, tr("Save"), QDir::home().absolutePath(), tr("Json"));
   if(!newPath.isEmpty()){
   customChartView->setData(fileManager->read(newPath));
   }
}
