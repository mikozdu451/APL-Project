/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *fileChooseWindow;
    QLineEdit *filePathLineEdit;
    QPushButton *chooseImageButton;
    QPushButton *nextWindowButton1;
    QLabel *imagePreview;
    QWidget *methodChooseWindow;
    QPushButton *nextWindowButton2;
    QPushButton *previousWindowButton1;
    QRadioButton *radioButton4;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
    QRadioButton *radioButton1;
    QLabel *label;
    QWidget *resultWindow;
    QPushButton *previousWindowButton2;
    QPushButton *downloadButton1;
    QPushButton *downloadButton2;
    QLabel *asmLabel;
    QLabel *cLabel;
    QLabel *asmTimeLabel;
    QLabel *cTimeLabel;
    QLabel *asmTime;
    QLabel *cTime;
    QLabel *asmPreview;
    QLabel *cPreview;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 801, 581));
        fileChooseWindow = new QWidget();
        fileChooseWindow->setObjectName(QString::fromUtf8("fileChooseWindow"));
        filePathLineEdit = new QLineEdit(fileChooseWindow);
        filePathLineEdit->setObjectName(QString::fromUtf8("filePathLineEdit"));
        filePathLineEdit->setGeometry(QRect(290, 470, 331, 41));
        filePathLineEdit->setAutoFillBackground(false);
        filePathLineEdit->setEchoMode(QLineEdit::Normal);
        filePathLineEdit->setReadOnly(true);
        chooseImageButton = new QPushButton(fileChooseWindow);
        chooseImageButton->setObjectName(QString::fromUtf8("chooseImageButton"));
        chooseImageButton->setGeometry(QRect(190, 470, 101, 41));
        nextWindowButton1 = new QPushButton(fileChooseWindow);
        nextWindowButton1->setObjectName(QString::fromUtf8("nextWindowButton1"));
        nextWindowButton1->setGeometry(QRect(310, 520, 181, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        nextWindowButton1->setFont(font);
        nextWindowButton1->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 141, 0);\n"
"color: rgb(0, 0, 0);"));
        imagePreview = new QLabel(fileChooseWindow);
        imagePreview->setObjectName(QString::fromUtf8("imagePreview"));
        imagePreview->setGeometry(QRect(190, 62, 431, 391));
        imagePreview->setAutoFillBackground(false);
        imagePreview->setStyleSheet(QString::fromUtf8("background-color: rgb(173, 173, 173)"));
        imagePreview->setFrameShape(QFrame::NoFrame);
        stackedWidget->addWidget(fileChooseWindow);
        methodChooseWindow = new QWidget();
        methodChooseWindow->setObjectName(QString::fromUtf8("methodChooseWindow"));
        nextWindowButton2 = new QPushButton(methodChooseWindow);
        nextWindowButton2->setObjectName(QString::fromUtf8("nextWindowButton2"));
        nextWindowButton2->setGeometry(QRect(410, 520, 181, 41));
        nextWindowButton2->setFont(font);
        nextWindowButton2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 141, 0);\n"
"color: rgb(0, 0, 0);"));
        previousWindowButton1 = new QPushButton(methodChooseWindow);
        previousWindowButton1->setObjectName(QString::fromUtf8("previousWindowButton1"));
        previousWindowButton1->setGeometry(QRect(200, 520, 181, 41));
        previousWindowButton1->setFont(font);
        previousWindowButton1->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 141, 0);\n"
"color: rgb(0, 0, 0);"));
        radioButton4 = new QRadioButton(methodChooseWindow);
        radioButton4->setObjectName(QString::fromUtf8("radioButton4"));
        radioButton4->setGeometry(QRect(190, 320, 421, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(16);
        radioButton4->setFont(font1);
        radioButton2 = new QRadioButton(methodChooseWindow);
        radioButton2->setObjectName(QString::fromUtf8("radioButton2"));
        radioButton2->setGeometry(QRect(190, 260, 421, 41));
        radioButton2->setFont(font1);
        radioButton3 = new QRadioButton(methodChooseWindow);
        radioButton3->setObjectName(QString::fromUtf8("radioButton3"));
        radioButton3->setGeometry(QRect(190, 380, 421, 41));
        radioButton3->setFont(font1);
        radioButton1 = new QRadioButton(methodChooseWindow);
        radioButton1->setObjectName(QString::fromUtf8("radioButton1"));
        radioButton1->setGeometry(QRect(190, 200, 421, 41));
        radioButton1->setFont(font1);
        label = new QLabel(methodChooseWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 130, 671, 41));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setWeight(50);
        label->setFont(font2);
        label->setFrameShape(QFrame::WinPanel);
        stackedWidget->addWidget(methodChooseWindow);
        resultWindow = new QWidget();
        resultWindow->setObjectName(QString::fromUtf8("resultWindow"));
        previousWindowButton2 = new QPushButton(resultWindow);
        previousWindowButton2->setObjectName(QString::fromUtf8("previousWindowButton2"));
        previousWindowButton2->setGeometry(QRect(310, 520, 181, 41));
        previousWindowButton2->setFont(font);
        previousWindowButton2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 141, 0);\n"
"color: rgb(0, 0, 0);"));
        downloadButton1 = new QPushButton(resultWindow);
        downloadButton1->setObjectName(QString::fromUtf8("downloadButton1"));
        downloadButton1->setGeometry(QRect(140, 520, 101, 21));
        downloadButton2 = new QPushButton(resultWindow);
        downloadButton2->setObjectName(QString::fromUtf8("downloadButton2"));
        downloadButton2->setGeometry(QRect(540, 520, 101, 21));
        asmLabel = new QLabel(resultWindow);
        asmLabel->setObjectName(QString::fromUtf8("asmLabel"));
        asmLabel->setGeometry(QRect(140, 30, 121, 21));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setWeight(75);
        asmLabel->setFont(font3);
        asmLabel->setLayoutDirection(Qt::LeftToRight);
        asmLabel->setAlignment(Qt::AlignCenter);
        cLabel = new QLabel(resultWindow);
        cLabel->setObjectName(QString::fromUtf8("cLabel"));
        cLabel->setGeometry(QRect(540, 30, 121, 21));
        cLabel->setFont(font3);
        cLabel->setLayoutDirection(Qt::LeftToRight);
        cLabel->setAlignment(Qt::AlignCenter);
        asmTimeLabel = new QLabel(resultWindow);
        asmTimeLabel->setObjectName(QString::fromUtf8("asmTimeLabel"));
        asmTimeLabel->setGeometry(QRect(90, 480, 91, 20));
        cTimeLabel = new QLabel(resultWindow);
        cTimeLabel->setObjectName(QString::fromUtf8("cTimeLabel"));
        cTimeLabel->setGeometry(QRect(510, 480, 81, 20));
        asmTime = new QLabel(resultWindow);
        asmTime->setObjectName(QString::fromUtf8("asmTime"));
        asmTime->setGeometry(QRect(190, 480, 91, 21));
        cTime = new QLabel(resultWindow);
        cTime->setObjectName(QString::fromUtf8("cTime"));
        cTime->setGeometry(QRect(600, 480, 91, 21));
        asmPreview = new QLabel(resultWindow);
        asmPreview->setObjectName(QString::fromUtf8("asmPreview"));
        asmPreview->setGeometry(QRect(20, 60, 371, 411));
        asmPreview->setAutoFillBackground(false);
        asmPreview->setStyleSheet(QString::fromUtf8("background-color: rgb(173, 173, 173)"));
        asmPreview->setFrameShape(QFrame::NoFrame);
        cPreview = new QLabel(resultWindow);
        cPreview->setObjectName(QString::fromUtf8("cPreview"));
        cPreview->setGeometry(QRect(410, 60, 371, 411));
        cPreview->setAutoFillBackground(false);
        cPreview->setStyleSheet(QString::fromUtf8("background-color: rgb(173, 173, 173)"));
        cPreview->setFrameShape(QFrame::NoFrame);
        stackedWidget->addWidget(resultWindow);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        chooseImageButton->setText(QApplication::translate("MainWindow", "Choose File", nullptr));
        nextWindowButton1->setText(QApplication::translate("MainWindow", "Next", nullptr));
        imagePreview->setText(QString());
        nextWindowButton2->setText(QApplication::translate("MainWindow", "Next", nullptr));
        previousWindowButton1->setText(QApplication::translate("MainWindow", "Previous", nullptr));
        radioButton4->setText(QApplication::translate("MainWindow", "BT.601", nullptr));
        radioButton2->setText(QApplication::translate("MainWindow", "Lume (BT.709)", nullptr));
        radioButton3->setText(QApplication::translate("MainWindow", "Algorithmic", nullptr));
        radioButton1->setText(QApplication::translate("MainWindow", "Formula used by GIMP or Photoshop", nullptr));
        label->setText(QApplication::translate("MainWindow", "Please choose grayscale filter method:", nullptr));
        previousWindowButton2->setText(QApplication::translate("MainWindow", "Previous", nullptr));
        downloadButton1->setText(QApplication::translate("MainWindow", "Download", nullptr));
        downloadButton2->setText(QApplication::translate("MainWindow", "Download", nullptr));
        asmLabel->setText(QApplication::translate("MainWindow", "Assembler", nullptr));
        cLabel->setText(QApplication::translate("MainWindow", "C", nullptr));
        asmTimeLabel->setText(QApplication::translate("MainWindow", "Time in seconds:", nullptr));
        cTimeLabel->setText(QApplication::translate("MainWindow", "Time in seconds:", nullptr));
        asmTime->setText(QString());
        cTime->setText(QString());
        asmPreview->setText(QString());
        cPreview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
