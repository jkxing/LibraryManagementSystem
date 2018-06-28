/********************************************************************************
** Form generated from reading UI file 'guiapp.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIAPP_H
#define UI_GUIAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiApp
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Login;
    QPushButton *Register;
    QPushButton *Help;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GuiApp)
    {
        if (GuiApp->objectName().isEmpty())
            GuiApp->setObjectName(QStringLiteral("GuiApp"));
        GuiApp->resize(420, 465);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/logo"), QSize(), QIcon::Normal, QIcon::Off);
        GuiApp->setWindowIcon(icon);
        GuiApp->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(GuiApp);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 30, 331, 381));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Login = new QPushButton(verticalLayoutWidget);
        Login->setObjectName(QStringLiteral("Login"));
        QFont font;
        font.setFamily(QStringLiteral("Comic Sans MS"));
        font.setPointSize(24);
        Login->setFont(font);
        Login->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,50);"));

        verticalLayout_3->addWidget(Login);

        Register = new QPushButton(verticalLayoutWidget);
        Register->setObjectName(QStringLiteral("Register"));
        Register->setFont(font);
        Register->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,50);"));

        verticalLayout_3->addWidget(Register);

        Help = new QPushButton(verticalLayoutWidget);
        Help->setObjectName(QStringLiteral("Help"));
        Help->setFont(font);
        Help->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,50);"));

        verticalLayout_3->addWidget(Help);

        GuiApp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GuiApp);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 420, 23));
        GuiApp->setMenuBar(menubar);
        statusbar = new QStatusBar(GuiApp);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GuiApp->setStatusBar(statusbar);

        retranslateUi(GuiApp);

        QMetaObject::connectSlotsByName(GuiApp);
    } // setupUi

    void retranslateUi(QMainWindow *GuiApp)
    {
        GuiApp->setWindowTitle(QApplication::translate("GuiApp", "Welcome to Library", nullptr));
        Login->setText(QApplication::translate("GuiApp", "Login", nullptr));
        Register->setText(QApplication::translate("GuiApp", "Register", nullptr));
        Help->setText(QApplication::translate("GuiApp", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GuiApp: public Ui_GuiApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIAPP_H
