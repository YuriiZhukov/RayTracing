/********************************************************************************
** Form generated from reading UI file 'raytracing.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAYTRACING_H
#define UI_RAYTRACING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RayTracingClass
{
public:

    void setupUi(QWidget *RayTracingClass)
    {
        if (RayTracingClass->objectName().isEmpty())
            RayTracingClass->setObjectName(QString::fromUtf8("RayTracingClass"));
        RayTracingClass->resize(600, 400);

        retranslateUi(RayTracingClass);

        QMetaObject::connectSlotsByName(RayTracingClass);
    } // setupUi

    void retranslateUi(QWidget *RayTracingClass)
    {
        RayTracingClass->setWindowTitle(QCoreApplication::translate("RayTracingClass", "RayTracing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RayTracingClass: public Ui_RayTracingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAYTRACING_H
