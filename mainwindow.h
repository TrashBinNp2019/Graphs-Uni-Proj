#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "customchartview.h"
#include "barchartview.h"
#include "piechartview.h"
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newFile();
    void open();
    void save();

private:
    Ui::MainWindow *ui;
    CustomChartView *customChartView = new BarChartView();
    //QAction *addAct;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    FileManager *fileManager;
};
#endif // MAINWINDOW_H

//open new save
//меню связать с файлмэнджэр он дает объекты даты
