#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QStandardPaths>
#include <model.h>

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
    QString getSaveFilePath();
    QPixmap getPixelmap(int *matrix, QImage image);
    int* getMatrix(QImage image);
    int getCheckedRadio();
    void changeToGrayscale(int *array, int size, int choice);
    void on_nextWindowButton1_clicked();
    void on_nextWindowButton2_clicked();
    void on_previousWindowButton1_clicked();
    void on_previousWindowButton2_clicked();
    void on_chooseImageButton_clicked();
    void on_downloadButton1_clicked();
    void on_downloadButton2_clicked();

private:
    Ui::MainWindow *ui;
    Model model;
};
#endif // MAINWINDOW_H
