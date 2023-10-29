/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QButtonGroup *Camera;
    QButtonGroup *Cubs;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(819, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(widget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        radioButton = new QRadioButton(MyForm);
        Cubs = new QButtonGroup(MyForm);
        Cubs->setObjectName(QString::fromUtf8("Cubs"));
        Cubs->addButton(radioButton);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(MyForm);
        Cubs->addButton(radioButton_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(MyForm);
        Cubs->addButton(radioButton_3);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_2->addWidget(radioButton_3);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        radioButton_4 = new QRadioButton(MyForm);
        Camera = new QButtonGroup(MyForm);
        Camera->setObjectName(QString::fromUtf8("Camera"));
        Camera->addButton(radioButton_4);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setChecked(true);

        verticalLayout->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(MyForm);
        Camera->addButton(radioButton_5);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));

        verticalLayout->addWidget(radioButton_5);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(widget, SIGNAL(cub1()), radioButton, SLOT(click()));
        QObject::connect(widget, SIGNAL(cub2()), radioButton_2, SLOT(click()));
        QObject::connect(widget, SIGNAL(cub3()), radioButton_3, SLOT(click()));
        QObject::connect(widget, SIGNAL(camera1()), radioButton_4, SLOT(click()));
        QObject::connect(widget, SIGNAL(camera2()), radioButton_5, SLOT(click()));
        QObject::connect(radioButton, SIGNAL(clicked()), widget, SLOT(canviaCub1()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), widget, SLOT(canviaCub2()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), widget, SLOT(canviaCub3()));
        QObject::connect(radioButton_4, SIGNAL(clicked()), widget, SLOT(canviaCamera1()));
        QObject::connect(radioButton_5, SIGNAL(clicked()), widget, SLOT(canviaCamera2()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "Cub seleccionat:", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "Cub-1", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyForm", "Cub-2", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MyForm", "Cub-3", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Camera seleccionada:", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MyForm", "Camera-1", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MyForm", "Camera-2", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
