#include "mainwindow.h"
#include "ui_mainwindow.h"



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
    QString filePath = QFileDialog::getOpenFileName(this, "Choose a bitmap image", desktopPath, filter);
    model.setPreviewImage(QPixmap(filePath));
    ui->imagePreview->setPixmap(model.getPreviewImage().scaled(model.getPreviewWidth(), model.getPreviewHeight(),Qt::KeepAspectRatio));
    ui->filePathLineEdit->setText(filePath);
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

void MainWindow::on_nextWindowButton2_clicked()
{
    if(getCheckedRadio()==0){
        QMessageBox::warning(this, "Warning", "No method checked!");
        return;
    } else {
        model.setMethodIndex(getCheckedRadio());
    }
    QImage previewImage = model.getPreviewImage().toImage();
    int width = previewImage.width();
    int height = previewImage.height();
    int *matrix = new int [width*height];
    for(int j = 0; j < height; j++)
    {
      for(int i = 0; i < width; i++)
      {
        matrix[j*width+i] = previewImage.pixel(i,j);
      }
    }
//    model.setAsmImage();
//    model.setCImage()
    delete [] matrix;
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

