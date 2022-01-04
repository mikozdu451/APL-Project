#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColor>
#include <windows.h>
#include <stdio.h>
#include <time.h>

//extern "C" int _stdcall TestProc0(float*, DWORD);
//extern "C" int _stdcall TestProc(float*, DWORD);
extern "C" int _stdcall Grayscale_GIMP_BT601(float*, DWORD);
extern "C" int _stdcall Grayscale_BT709(float*, DWORD);
extern "C" int _stdcall Grayscale_BT2100(float*, DWORD);
extern "C" int _stdcall Grayscale_arithmetic(float*, DWORD);

MainWindow::MainWindow(QWidget* parent)
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
    ui->imagePreview->setPixmap(model.getPreviewImage().scaled(model.getPreviewWidth(), model.getPreviewHeight(), Qt::KeepAspectRatio));
    ui->filePathLineEdit->setText(model.getImagePath());
}

void MainWindow::on_nextWindowButton1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// Choose method window

int MainWindow::getCheckedRadio() {
    if (ui->radioButton1->isChecked())
        return 1;
    if (ui->radioButton2->isChecked())
        return 2;
    if (ui->radioButton3->isChecked())
        return 3;
    if (ui->radioButton4->isChecked())
        return 4;
    return 0;
}

std::unique_ptr<float[]> MainWindow::getMatrix(QImage image)
{
    int width = image.width();
    int height = image.height();
    auto matrix = std::make_unique<float[]>(width * 3 * height);
    QColor temp;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            temp = image.pixel(i, j);
            matrix[j * width * 3 + i * 3] = temp.red();
            matrix[j * width * 3 + i * 3 + 1] = temp.green();
            matrix[j * width * 3 + i * 3 + 2] = temp.blue();
        }
    }
    return matrix;
}

QPixmap MainWindow::getPixelmap(std::unique_ptr<float[]>& matrix, QImage image) {
    QColor temp;
    for (int j = 0; j < image.height(); j++)
    {
        for (int i = 0; i < image.width(); i++)
        {
            float red = matrix[j * image.width() * 3 + i * 3];
            float green = matrix[j * image.width() * 3 + i * 3 + 1];
            float blue = matrix[j * image.width() * 3 + i * 3 + 2];
            temp.setRgb(red, green, blue);
            image.setPixelColor(i, j, temp);
        }
    }
    return QPixmap::fromImage(image);
}

void MainWindow::changeToGrayscale(std::unique_ptr<float[]>& array, int size, int choice) {
    double options[4][3] = { {0.3, 0.59, 0.11}, {0.2126, 0.7152, 0.0722}, {0.299, 0.587, 0.113}, {0.333, 0.333, 0.333} };
    unsigned char gray;
    for (int i = 0; i < size; i += 3) {
        gray = array[i] * options[choice][0] + array[i + 1] * options[choice][1] + array[i + 2] * options[choice][2];
        array[i] = gray;
        array[i + 1] = gray;
        array[i + 2] = gray;
    }
}

void MainWindow::on_nextWindowButton2_clicked()
{
    if (getCheckedRadio() == 0) {
        QMessageBox::warning(this, "Warning", "No method checked!");
        return;
    }
    else {
        model.setMethodIndex(getCheckedRadio());
    }
    QImage image = model.getPreviewImage().toImage();
    int lenght = 3 * image.width() * image.height();

    auto matrixASM = getMatrix(image);
    auto matrixC = getMatrix(image);
    std::chrono::time_point<std::chrono::steady_clock> begin_C, end_C, begin_ASM, end_ASM;

    if (model.getMethodIndex() == 1) {
        //Gimp (BT.601)
        begin_C = std::chrono::steady_clock::now();
        changeToGrayscale(matrixC, lenght, 0);
        end_C = std::chrono::steady_clock::now();

        begin_ASM = std::chrono::steady_clock::now();
        Grayscale_GIMP_BT601(&matrixASM[0], lenght);
        end_ASM = std::chrono::steady_clock::now();

    }
    else if (model.getMethodIndex() == 2) {
        //  Lume (BT.709)
        begin_C = std::chrono::steady_clock::now();
        changeToGrayscale(matrixC, lenght, 1);;
        end_C = std::chrono::steady_clock::now();

        begin_ASM = std::chrono::steady_clock::now();
        Grayscale_BT709(&matrixASM[0], lenght);
        end_ASM = std::chrono::steady_clock::now();

    }
    else if (model.getMethodIndex() == 3) {
        //  BT.2100
        begin_C = std::chrono::steady_clock::now();
        changeToGrayscale(matrixC, lenght, 2);
        end_C = std::chrono::steady_clock::now();

        begin_ASM = std::chrono::steady_clock::now();
        Grayscale_BT2100(&matrixASM[0], lenght);
        end_ASM = std::chrono::steady_clock::now();

    }
    else if (model.getMethodIndex() == 4) {
        //  Algorithmic
        begin_C = std::chrono::steady_clock::now();
        changeToGrayscale(matrixC, lenght, 3);
        end_C = std::chrono::steady_clock::now();

        begin_ASM = std::chrono::steady_clock::now();
        Grayscale_arithmetic(&matrixASM[0], lenght);
        end_ASM = std::chrono::steady_clock::now();
    }

    auto elapsed_C_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(end_C - begin_C);
    auto elapsed_C_micro = std::chrono::duration_cast<std::chrono::microseconds>(end_C - begin_C);
    auto elapsed_C_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end_C - begin_C);
    auto elapsed_C = std::chrono::duration_cast<std::chrono::seconds>(end_C - begin_C);

    auto elapsed_ASM_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ASM - begin_ASM);
    auto elapsed_ASM_micro = std::chrono::duration_cast<std::chrono::microseconds>(end_ASM - begin_ASM);
    auto elapsed_ASM_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end_ASM - begin_ASM);
    auto elapsed_ASM = std::chrono::duration_cast<std::chrono::seconds>(end_ASM - begin_ASM);

    model.setAsmImage(getPixelmap(matrixASM, image));
    model.setCImage(getPixelmap(matrixC, image));

    ui->asmTime->setText(QString::number(elapsed_ASM_nano.count()));
    ui->asmTime_3->setText(QString::number(elapsed_ASM_micro.count()));
    ui->asmTime_4->setText(QString::number(elapsed_ASM_milli.count()));
    ui->asmTime_5->setText(QString::number(elapsed_ASM.count()));

    ui->cTime->setText(QString::number(elapsed_C_nano.count()));
    ui->cTime_3->setText(QString::number(elapsed_C_micro.count()));
    ui->cTime_4->setText(QString::number(elapsed_C_milli.count()));
    ui->cTime_5->setText(QString::number(elapsed_C.count()));

    ui->asmPreview->setPixmap(model.getAsmImage().scaled(model.getResultWidth(), model.getResultHeight(), Qt::KeepAspectRatio));
    ui->cPreview->setPixmap(model.getCImage().scaled(model.getResultWidth(), model.getResultHeight(), Qt::KeepAspectRatio));
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_previousWindowButton1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Result window

QString MainWindow::getSaveFilePath() {
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
    asmFile.open(QIODevice::WriteOnly);
    model.getAsmImage().save(&asmFile, "BMP");
    asmFile.close();
}


void MainWindow::on_downloadButton2_clicked()
{
    QFile cFile(getSaveFilePath());
    cFile.open(QIODevice::WriteOnly);
    model.getCImage().save(&cFile, "BMP");
    cFile.close();
}