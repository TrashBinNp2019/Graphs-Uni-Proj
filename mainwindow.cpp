#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newAct = ui->actionNew;
    saveAct = ui->actionSave;
    openAct = ui->actionOpen;
    clearAct = ui->actionClear;

    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    connect(clearAct, &QAction::triggered, this, &MainWindow::clear);

    connect( fileManager, &FileManager::fileError, this, [ this ]( const QString& msg ){
        this->ui->statusbar->showMessage( "File manager error: " + msg, 5000 );
    } );
    connect( fileManager, &FileManager::writeSuccess, this, [ this ](){
        this->ui->statusbar->showMessage( "Wrote successfully", 5000 );
    } );
    connect( fileManager, &FileManager::readSuccess, this, [ this ](){
        this->ui->statusbar->showMessage( "Read successfully", 5000 );
    } );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newFile()
{

void MainWindow::enableDisplay()
{
    customChartView->updateData();
    setCentralWidget(customChartView);
}

void MainWindow::disableDisplay()
{
    setCentralWidget(nullptr);
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
   enableDisplay();
   }
}

void MainWindow::clear() {
    disableDisplay();
}
