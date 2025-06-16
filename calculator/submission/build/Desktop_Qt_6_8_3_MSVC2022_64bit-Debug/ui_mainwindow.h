/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *l_memory;
    QLabel *l_formula;
    QLabel *l_result;
    QPushButton *btnMC;
    QPushButton *btnMR;
    QPushButton *btnMS;
    QPushButton *btnPow;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnMul;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btnSub;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btnAdd;
    QPushButton *btnDot;
    QPushButton *btn0;
    QPushButton *btnBackspace;
    QPushButton *btnEquals;
    QPushButton *btnDiv;
    QPushButton *btnSign;
    QPushButton *btnClear;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(415, 360);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        l_memory = new QLabel(centralwidget);
        l_memory->setObjectName("l_memory");

        gridLayout->addWidget(l_memory, 0, 0, 1, 4);

        l_formula = new QLabel(centralwidget);
        l_formula->setObjectName("l_formula");
        l_formula->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(l_formula, 1, 0, 1, 4);

        l_result = new QLabel(centralwidget);
        l_result->setObjectName("l_result");
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        l_result->setFont(font);
        l_result->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(l_result, 2, 0, 1, 4);

        btnMC = new QPushButton(centralwidget);
        btnMC->setObjectName("btnMC");

        gridLayout->addWidget(btnMC, 3, 0, 1, 1);

        btnMR = new QPushButton(centralwidget);
        btnMR->setObjectName("btnMR");

        gridLayout->addWidget(btnMR, 3, 1, 1, 1);

        btnMS = new QPushButton(centralwidget);
        btnMS->setObjectName("btnMS");

        gridLayout->addWidget(btnMS, 3, 2, 1, 1);

        btnPow = new QPushButton(centralwidget);
        btnPow->setObjectName("btnPow");

        gridLayout->addWidget(btnPow, 3, 3, 1, 1);

        btn7 = new QPushButton(centralwidget);
        btn7->setObjectName("btn7");

        gridLayout->addWidget(btn7, 5, 0, 1, 1);

        btn8 = new QPushButton(centralwidget);
        btn8->setObjectName("btn8");

        gridLayout->addWidget(btn8, 5, 1, 1, 1);

        btn9 = new QPushButton(centralwidget);
        btn9->setObjectName("btn9");

        gridLayout->addWidget(btn9, 5, 2, 1, 1);

        btnMul = new QPushButton(centralwidget);
        btnMul->setObjectName("btnMul");

        gridLayout->addWidget(btnMul, 5, 3, 1, 1);

        btn4 = new QPushButton(centralwidget);
        btn4->setObjectName("btn4");

        gridLayout->addWidget(btn4, 6, 0, 1, 1);

        btn5 = new QPushButton(centralwidget);
        btn5->setObjectName("btn5");

        gridLayout->addWidget(btn5, 6, 1, 1, 1);

        btn6 = new QPushButton(centralwidget);
        btn6->setObjectName("btn6");

        gridLayout->addWidget(btn6, 6, 2, 1, 1);

        btnSub = new QPushButton(centralwidget);
        btnSub->setObjectName("btnSub");

        gridLayout->addWidget(btnSub, 6, 3, 1, 1);

        btn1 = new QPushButton(centralwidget);
        btn1->setObjectName("btn1");

        gridLayout->addWidget(btn1, 7, 0, 1, 1);

        btn2 = new QPushButton(centralwidget);
        btn2->setObjectName("btn2");

        gridLayout->addWidget(btn2, 7, 1, 1, 1);

        btn3 = new QPushButton(centralwidget);
        btn3->setObjectName("btn3");

        gridLayout->addWidget(btn3, 7, 2, 1, 1);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");

        gridLayout->addWidget(btnAdd, 7, 3, 1, 1);

        btnDot = new QPushButton(centralwidget);
        btnDot->setObjectName("btnDot");

        gridLayout->addWidget(btnDot, 8, 0, 1, 1);

        btn0 = new QPushButton(centralwidget);
        btn0->setObjectName("btn0");

        gridLayout->addWidget(btn0, 8, 1, 1, 1);

        btnBackspace = new QPushButton(centralwidget);
        btnBackspace->setObjectName("btnBackspace");

        gridLayout->addWidget(btnBackspace, 8, 2, 1, 1);

        btnEquals = new QPushButton(centralwidget);
        btnEquals->setObjectName("btnEquals");

        gridLayout->addWidget(btnEquals, 8, 3, 1, 1);

        btnDiv = new QPushButton(centralwidget);
        btnDiv->setObjectName("btnDiv");

        gridLayout->addWidget(btnDiv, 4, 3, 1, 1);

        btnSign = new QPushButton(centralwidget);
        btnSign->setObjectName("btnSign");

        gridLayout->addWidget(btnSign, 4, 2, 1, 1);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");

        gridLayout->addWidget(btnClear, 4, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Calculator", nullptr));
        l_memory->setText(QString());
        l_formula->setText(QString());
        l_result->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnMC->setText(QCoreApplication::translate("MainWindow", "MC", nullptr));
        btnMR->setText(QCoreApplication::translate("MainWindow", "MR", nullptr));
        btnMS->setText(QCoreApplication::translate("MainWindow", "MS", nullptr));
        btnPow->setText(QCoreApplication::translate("MainWindow", "x\312\270", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btnSub->setText(QCoreApplication::translate("MainWindow", "\342\210\222", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnDot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnBackspace->setText(QCoreApplication::translate("MainWindow", "\342\214\253", nullptr));
        btnEquals->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnDiv->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        btnSign->setText(QCoreApplication::translate("MainWindow", "\302\261", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
