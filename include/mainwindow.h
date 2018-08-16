#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/** @file mainwindow.h
    GUI du logiciel
*/

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QFileInfo>
#include <QProgressBar>
#include <QDesktopWidget>

#include "include/graphwidget.h"

/**
 * Espace de nommage regroupant les composants de la fenêtre
 */
namespace Ui {
class MainWindow;
}

/**
 * Classe pour notre gui
 * @param  parent parent
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructeur de la classe MainWindow
     * @param parent parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /** Ouvrir un dossier */
    void on_actionOpen_triggered();
    /** Lancer le programme d'edition d'image */
    void on_pushButton_clicked();
    /** Sauvegarder l'image modifée */
    void on_actionSave_triggered();
    /** Passer en mode HSV */
    void on_radioHSV_clicked();
    /** Passer en mode HSL */
    void on_radioHSL_clicked();
    /** Passer en mode HSV&RGB */
    void on_radioHSVRGB_clicked();
    /** Passer en mode HSV+L */
    void on_radioHSVL_clicked();
    /** Inverser la valeur de l'option transparence */
    void on_checkBox_stateChanged(int arg1);
    /** Inverser la valeur de l'option nombre de couleur */
    void on_spinBox_valueChanged(int arg1);
    /** Passer en mode RGB */
    void on_radioButton_clicked();
    /** Inverser la valeur de l'option post process */
    void on_checkBox_2_stateChanged(int arg1);

private:
    /** Ensemble des composants */
    Ui::MainWindow *ui;

    /** Scene où afficher l'image original */
    QGraphicsScene *scene;
    /** Scene où afficher l'image retouché */
    QGraphicsScene *scene2;

    /** Chemin vers l'image à retoucher */
    const char * fileToOpen = NULL;
};

#endif // MAINWINDOW_H
