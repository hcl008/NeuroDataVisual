/********************************************************************************
** Form generated from reading UI file 'glwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLWIDGET_H
#define UI_GLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GlWidgetClass
{
public:

    void setupUi(QWidget *GlWidgetClass)
    {
        if (GlWidgetClass->objectName().isEmpty())
            GlWidgetClass->setObjectName(QStringLiteral("GlWidgetClass"));
        GlWidgetClass->resize(600, 400);

        retranslateUi(GlWidgetClass);

        QMetaObject::connectSlotsByName(GlWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *GlWidgetClass)
    {
        GlWidgetClass->setWindowTitle(QApplication::translate("GlWidgetClass", "GlWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class GlWidgetClass: public Ui_GlWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLWIDGET_H
