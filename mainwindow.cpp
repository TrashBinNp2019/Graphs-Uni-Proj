#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPushButton>
#include <QRandomGenerator>

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
    connect(newAct, &QAction::triggered, this, &MainWindow::newStandartCharts);

    customChartView = nullptr;

//    connect( fileManager, &FileManager::fileError, this, [ this ]( const QString& msg ){
//        this->ui->statusbar->showMessage( "File manager error: " + msg, 5000 );
//    } );
//    connect( fileManager, &FileManager::writeSuccess, this, [ this ](){
//        this->ui->statusbar->showMessage( "Wrote successfully", 5000 );
//    } );
//    connect( fileManager, &FileManager::readSuccess, this, [ this ](){
//        this->ui->statusbar->showMessage( "Read successfully", 5000 );
//    } );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newFile()
{

}

void MainWindow::enableDisplay()
{
    if ( !customChartView ) return;
    customChartView->update();
    setCentralWidget(customChartView);
}

void MainWindow::disableDisplay()
{
    if ( customChartView ) {
        delete customChartView;
        customChartView = nullptr;
    }
    setCentralWidget(nullptr);
}

void MainWindow::save() {
    if ( ui->centralwidget ) {
        ui->statusbar->showMessage("Saving...");
        QString newPath = QFileDialog::getSaveFileName(this, tr("Save..."), QDir::home().absolutePath(), tr("Json (*.json)"));
        if (!newPath.isEmpty()){
            fileManager->write(customChartView->getData(), newPath);
        }
    }
}

void MainWindow::newStandartCharts()
{
    if ( customChartView ) {
        delete customChartView;
        customChartView = nullptr;
    }

    Data* data = new Data();
    Data::DataElement el0{ QRandomGenerator::global()->generate() % 100 / 10, "John" };
    Data::DataElement el1{ QRandomGenerator::global()->generate() % 100 / 10, "Steve" };
    Data::DataElement el2{ QRandomGenerator::global()->generate() % 100 / 10, "Karen" };
    data->setTitle( "Default" );
    data->setBrushColor( Qt::white );
    data->setPenColor( Qt::black );
    data->setPenWidth( 1 );
    *data << el0 ;
    *data << el1 ;
    *data << el2 ;
    customChartView = new BarChartView();
    customChartView->setData(data);
    enableDisplay();
}

void MainWindow::open() {  
   ui->statusbar->showMessage("Opening...");
   QString newPath = QFileDialog::getOpenFileName(this, tr("Open..."), QDir::home().absolutePath(), tr("Json (*.json)"));
   if(!newPath.isEmpty()){
        auto data = fileManager->read(newPath);
        if ( !data ) return;

        if ( customChartView ) {
            delete customChartView;
            customChartView = nullptr;
        }

        customChartView = new BarChartView();
        customChartView->setData( data );
        enableDisplay();
   }
}

void MainWindow::clear() {
    disableDisplay();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Nikita Puchinskij");
    msgBox.setInformativeText("Group 10, Variant 3, 2022");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setWindowTitle( "Charts" );

    msgBox.exec();
}

