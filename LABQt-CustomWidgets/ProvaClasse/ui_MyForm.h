/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include "MyQLabel.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QLineEdit *lineEdit;
    MyQLabel *label;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(765, 473);
        lineEdit = new QLineEdit(MyForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(190, 110, 113, 25));
        label = new MyQLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 170, 67, 17));

        retranslateUi(MyForm);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), label, SLOT(CuentaEnters()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QApplication::translate("MyForm", "Form", nullptr));
        label->setText(QApplication::translate("MyForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
