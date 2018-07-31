#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QFileInfo>
#include <QProgressBar>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_actionSave_triggered();

    void on_radioHSV_clicked();

    void on_radioHSL_clicked();

    void on_radioHSVRGB_clicked();

    void on_radioHSVL_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_radioButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsScene *scene2;

    const char * fileToOpen = NULL;
};

#endif // MAINWINDOW_H
