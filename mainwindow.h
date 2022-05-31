#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include "customchartview.h"
#include "barchartview.h"
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
private:
    void enableDisplay();
    void disableDisplay();
    void newStandartCharts();
    void updateDisplay();

private slots:
    void newFile();
    void open();
    void save();
    void clear();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionPenColor_triggered();

    void on_actionBrushColor_triggered();

    void on_actionPenWidth_triggered();

private:
    Ui::MainWindow *ui;
    CustomChartView *customChartView;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *clearAct;
    FileManager fileManager;

    QLabel *statusLabel;
};
#endif // MAINWINDOW_H

//open new save
//меню связать с файлмэнджэр он дает объекты даты
