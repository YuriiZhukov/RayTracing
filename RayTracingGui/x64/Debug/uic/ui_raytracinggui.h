/********************************************************************************
** Form generated from reading UI file 'raytracinggui.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAYTRACINGGUI_H
#define UI_RAYTRACINGGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RayTracingGuiClass
{
public:

    void setupUi(QWidget *RayTracingGuiClass)
    {
        if (RayTracingGuiClass->objectName().isEmpty())
            RayTracingGuiClass->setObjectName(QString::fromUtf8("RayTracingGuiClass"));
        RayTracingGuiClass->resize(600, 400);

        retranslateUi(RayTracingGuiClass);

        QMetaObject::connectSlotsByName(RayTracingGuiClass);
    } // setupUi

    void retranslateUi(QWidget *RayTracingGuiClass)
    {
        RayTracingGuiClass->setWindowTitle(QCoreApplication::translate("RayTracingGuiClass", "RayTracingGui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RayTracingGuiClass: public Ui_RayTracingGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAYTRACINGGUI_H
