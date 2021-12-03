#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColor>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model.setPreviewHeight(ui->imagePreview->height());
    model.setPreviewWidth(ui->imagePreview->width());
    model.setResultHeight(ui->asmPreview->height());
    model.setResultWidth(ui->asmPreview->width());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Choose file window

void MainWindow::on_chooseImageButton_clicked()
{
    QString filter = "Bitmap file (*.bmp)";
    QString desktopPath = QString(getenv("USERPROFILE")) + "\\Desktop";
    model.setImagePath(QFileDialog::getOpenFileName(this, "Choose a bitmap image", desktopPath, filter));
    model.setPreviewImage(QPixmap(model.getImagePath()));
    ui->imagePreview->setPixmap(model.getPreviewImage().scaled(model.getPreviewWidth(), model.getPreviewHeight(),Qt::KeepAspectRatio));
    ui->filePathLineEdit->setText(model.getImagePath());
}

void MainWindow::on_nextWindowButton1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// Choose method window

int MainWindow::getCheckedRadio(){
    if(ui->radioButton1->isChecked())
        return 1;
    if(ui->radioButton2->isChecked())
        return 2;
    if(ui->radioButton3->isChecked())
        return 3;
    if(ui->radioButton4->isChecked())
        return 4;
    return 0;
}

int* MainWindow::getMatrix(QImage image)
{
    int width = image.width();
    int height = image.height();
    int *matrix = new int [width*3*height*3];
    QColor temp;
    for(int j = 0; j < height; j++)
    {
      for(int i = 0; i < width; i++)
      {
        temp = image.pixel(i,j);
        matrix[j*width*3+i*3] = temp.red();
        matrix[j*width*3+i*3+1] = temp.green();
        matrix[j*width*3+i*3+2] = temp.blue();
      }
    }
    return matrix;
}

QPixmap MainWindow::getPixelmap(int *matrix, QImage image){
    QColor temp;
    for(int j = 0; j < image.height(); j++)
    {
      for(int i = 0; i < image.width(); i++)
      {
        float red = matrix[j*image.width()*3+i*3];
        float green = matrix[j*image.width()*3+i*3+1];
        float blue = matrix[j*image.width()*3+i*3+2];
        temp.setRgb(red,green,blue);
        image.setPixelColor(i,j,temp);
      }
    }
    return QPixmap::fromImage(image);
}

void MainWindow::changeToGrayscale(int *array, int size, int choice){
    double options[4][3]= {{0.3, 0.59, 0.11}, {0.2126, 0.7152, 0.0722}, {0.299, 0.587, 0.113}, {0.333, 0.333, 0.333}};
    unsigned char gray;
    for (int i = 0; i < size; i += 3){
        gray = array[i] * options[choice][0] + array[i+1] * options[choice][1] + array[i+2] * options[choice][2];
        array[i] = gray;
        array[i+1] = gray;
        array[i+2] = gray;
    }
}

void MainWindow::on_nextWindowButton2_clicked()
{
    if(getCheckedRadio()==0){
        QMessageBox::warning(this, "Warning", "No method checked!");
        return;
    } else {
        model.setMethodIndex(getCheckedRadio());
    }
    QImage image = model.getPreviewImage().toImage();
    int *matrixAsm = getMatrix(image);
    int *matrixC = getMatrix(image);

//    QColor temp;
//    for(int j = 0; j < height; j++)
//    {
//      for(int i = 0; i < width; i++)
//      {
//        float red = matrix[j*width*3+i*3];
//        float green = matrix[j*width*3+i*3+1];
//        float blue = matrix[j*width*3+i*3+2];
//        temp.setRgb(red,green,blue);
//        result.setPixelColor(i,j,temp);
//      }
//    }
    if(model.getMethodIndex()==1){
        //  Formula used by GIMP or Photoshop

        changeToGrayscale(matrixC, 9*image.width()*image.height(), 0);
//        passToAsm(&matrix, 9*image.width()*image.height());
    } else if(model.getMethodIndex()==2){
        //  Lume (BT.709)

        changeToGrayscale(matrixC, 9*image.width()*image.height(), 1);
//        passToAsm(&matrix, 9*image.width()*image.height());
    } else if(model.getMethodIndex()==3){
        //  BT.601

        changeToGrayscale(matrixC, 9*image.width()*image.height(), 2);
//        passToAsm(&matrix, 9*image.width()*image.height());
    } else if(model.getMethodIndex()==4){
        //  Algorithmic

        changeToGrayscale(matrixC, 9*image.width()*image.height(), 3);
//        passToAsm(&matrix, 9*image.width()*image.height());
    }
    model.setAsmImage(getPixelmap(matrixAsm,image));
//    model.setAsmImage()
    model.setCImage(getPixelmap(matrixC,image));
    delete [] matrixAsm;
    delete [] matrixC;
    ui->asmPreview->setPixmap(model.getAsmImage().scaled(model.getResultWidth(), model.getResultHeight(),Qt::KeepAspectRatio));
    ui->cPreview->setPixmap(model.getCImage().scaled(model.getResultWidth(), model.getResultHeight(),Qt::KeepAspectRatio));
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_previousWindowButton1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Result window

QString MainWindow::getSaveFilePath(){
    QString filter = "Bitmap file (*.bmp)";
    QString desktopPath = QString(getenv("USERPROFILE")) + "\\Desktop";
    return QFileDialog::getSaveFileName(this, "Save file", desktopPath, filter);
}

void MainWindow::on_previousWindowButton2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_downloadButton1_clicked()
{

    QFile asmFile(getSaveFilePath());
    asmFile.open( QIODevice::WriteOnly);
    model.getAsmImage().save(&asmFile, "BMP");
    asmFile.close();
}


void MainWindow::on_downloadButton2_clicked()
{
    QFile cFile(getSaveFilePath());
    cFile.open( QIODevice::WriteOnly);
    model.getCImage().save(&cFile, "BMP");
    cFile.close();
}

