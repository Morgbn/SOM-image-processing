#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/som.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide(); // par défaut cacher la bar de progression
    // mise en place de la scène ou afficher l'image
    scene = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    ui->label->setText("");
    QString fileName = QFileDialog::getOpenFileName(this,"Open Image File",QDir::currentPath(),"Image PNG (*.png)");
    if(!fileName.isEmpty())
    {
        QPixmap pixmap(fileName);
        if(pixmap.isNull()) // si pas une image
        {
            QMessageBox::information(this,"Image Viewer","Error displaying image!"); // msg d'erreur
            return;
        }
        scene->clear();
        scene->addPixmap(pixmap);
        ui->graphicsView->show();
        fileToOpen = strdup(fileName.toStdString().c_str());
    }
}

void MainWindow::on_pushButton_clicked()
{
    // lancer le programme d'edition d'image
    if (!fileToOpen) // pas de fichier ouvert
    {
        QMessageBox::information(this,"Image Edition","No file open!");
        return;
    }
    if(!QFileInfo(fileToOpen).exists()) // fichier inexistant ou dossier
    {
        QMessageBox::information(this,"Image Edition","File doesn't exist!");
        return;
    }
    ui->progressBar->show();
    int error = editImg(fileToOpen, "/tmp/somOut.png", ui->progressBar, 0);
    ui->progressBar->hide();
    if (error) // erreur lors du traitement de l'image
    {
        QMessageBox::information(this,"Image Edition","Error while processing the image!");
        return;
    }
    QPixmap pixmap2("/tmp/somOut.png");
    scene2->clear();
    scene2->addPixmap(pixmap2);
    ui->graphicsView_2->show();
}

void MainWindow::on_actionSave_triggered()
{
    if (scene2->width() == 0) return; // pas d'image à enregistrer
    QString fileName = QFileDialog::getSaveFileName(this,"Save Image File",QDir::currentPath(),"Image PNG (*.png)");
    QImage pixmap(scene2->width(), scene2->height(), QImage::Format_ARGB32_Premultiplied);
    QPainter p;
    p.begin(&pixmap);
    p.setRenderHint(QPainter::Antialiasing, true);
    scene2->render(&p);
    p.end();
    pixmap.save(fileName, "PNG");

    ui->label->setText("Saved !");
}



void MainWindow::on_radioHSV_clicked()
{
    MY_HSV = 1;
    MY_HSL = MY_HSVRGB = MY_HSVL = 0;
}

void MainWindow::on_radioHSL_clicked()
{
    MY_HSL = 1;
    MY_HSV = MY_HSVRGB = MY_HSVL = 0;
}

void MainWindow::on_radioHSVRGB_clicked()
{
    MY_HSVRGB = 1;
    MY_HSV = MY_HSL = MY_HSVL = 0;
}

void MainWindow::on_radioHSVL_clicked()
{
    MY_HSVL = 1;
    MY_HSV = MY_HSL = MY_HSVRGB = 0;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    makeTransparent = arg1;
}
