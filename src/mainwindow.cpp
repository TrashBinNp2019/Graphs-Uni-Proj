#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fileManager( this )
{
    ui->setupUi(this);

    ui->menuPen->setEnabled( false );
    ui->menuBrush->setEnabled( false );

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

    statusLabel = new QLabel( this );
    statusLabel->setText( "Nothing to display" );
    this->ui->statusbar->addPermanentWidget( statusLabel );

    connect( &fileManager, &FileManager::fileError, this, [ this ]( const QString& msg ){
        this->ui->statusbar->showMessage( "File manager error: " + msg, 5000 );
    } );
    connect( &fileManager, &FileManager::writeSuccess, this, [ this ](){
        this->ui->statusbar->showMessage( "Wrote successfully", 5000 );
    } );
    connect( &fileManager, &FileManager::readSuccess, this, [ this ](){
        this->ui->statusbar->showMessage( "Read successfully", 5000 );
    } );
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

    ui->menuPen->setEnabled( true );
    ui->menuBrush->setEnabled( true );
    setCentralWidget(customChartView);
    updateDisplay();
}

void MainWindow::disableDisplay()
{
    if ( customChartView ) {
        delete customChartView;
        customChartView = nullptr;
    }

    ui->menuPen->setEnabled( false );
    ui->menuBrush->setEnabled( false );
    setCentralWidget(nullptr);
}

void MainWindow::save() {
    if ( ui->centralwidget ) {
        ui->statusbar->showMessage("Saving...");
        QString newPath = QFileDialog::getSaveFileName(this, tr("Save..."), QDir::home().absolutePath(), tr("Json (*.json)"));
        if (!newPath.isEmpty()){
            fileManager.write(customChartView->getData(), newPath);
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

void MainWindow::updateDisplay()
{
    if ( !customChartView || !statusLabel ) return;

    customChartView->update();
    statusLabel->setText( QString( "Chart: %1, Pen Color: %2, Pen Width: %3 px, Brush Color: %4" )
                          .arg( customChartView->getData()->getTitle() )
                          .arg( customChartView->getData()->getPenColor().name() )
                          .arg( QString::number( customChartView->getData()->getPenWidth() ) )
                          .arg( customChartView->getData()->getBrushColor().name() ) );
}

void MainWindow::open() {  
   ui->statusbar->showMessage("Opening...");
   QString newPath = QFileDialog::getOpenFileName(this, tr("Open..."), QDir::home().absolutePath(), tr("Json (*.json)"));
   if(!newPath.isEmpty()){
        auto data = fileManager.read(newPath);
        if ( !data ) return;

        if ( customChartView ) {
            delete customChartView;
            customChartView = nullptr;
        }

        customChartView = new BarChartView();
        customChartView->setData( data );
        updateDisplay();
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


void MainWindow::on_actionPenColor_triggered()
{
    if ( !customChartView ) return;

    QColorDialog dlg{ customChartView->getData()->getPenColor(), this };

    switch ( dlg.exec() ) {
    case dlg.Accepted: {
        customChartView->getData()->setPenColor( dlg.currentColor() );
        updateDisplay();
        break;
    }
    case dlg.Rejected: {
        break;
    }
    default:
        break;
    }
}


void MainWindow::on_actionBrushColor_triggered()
{
    if ( !customChartView ) return;

    QColorDialog dlg{ customChartView->getData()->getBrushColor(), this };

    switch ( dlg.exec() ) {
    case dlg.Accepted: {
        customChartView->getData()->setBrushColor( dlg.currentColor() );
        customChartView->update();
        break;
    }
    case dlg.Rejected: {
        break;
    }
    default:
        break;
    }
}


void MainWindow::on_actionPenWidth_triggered()
{
    if ( !customChartView ) return;

    QStringList options{ "1 px", "2 px", "5 px", "10 px", "20 px" };
    QInputDialog dlg{ this };
    dlg.setComboBoxItems( options );


    switch ( dlg.exec() ) {
    case dlg.Accepted: {
        int res;
        switch ( options.indexOf( dlg.textValue() ) ) {
        case 0: {
            res = 1;
            break;
        }
        case 1: {
            res = 2;
            break;
        }
        case 2: {
            res = 5;
            break;
        }
        case 3: {
            res = 10;
            break;
        }
        case 4: {
            res = 20;
            break;
        }
        default: {
            res = 1;
        }
        }

        customChartView->getData()->setPenWidth( res );
        customChartView->update();
        break;
    }
    case dlg.Rejected: {
        break;
    }
    default:
        break;
    }
}

