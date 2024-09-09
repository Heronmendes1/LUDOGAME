/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *logo;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QRadioButton *radioTwo;
    QRadioButton *radioThree;
    QRadioButton *radioFour;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *aboutButton;
    QPushButton *loadButton;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QMainWindow *WelcomeWindow)
    {
        if (WelcomeWindow->objectName().isEmpty())
            WelcomeWindow->setObjectName("WelcomeWindow");
        WelcomeWindow->resize(578, 332);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WelcomeWindow->sizePolicy().hasHeightForWidth());
        WelcomeWindow->setSizePolicy(sizePolicy);
        WelcomeWindow->setMinimumSize(QSize(0, 0));
        centralwidget = new QWidget(WelcomeWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        logo = new QLabel(centralwidget);
        logo->setObjectName("logo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logo->sizePolicy().hasHeightForWidth());
        logo->setSizePolicy(sizePolicy1);
        logo->setMinimumSize(QSize(0, 111));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ani")});
        font.setPointSize(30);
        logo->setFont(font);
        logo->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(logo);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        label->setMargin(0);

        verticalLayout->addWidget(label);

        radioTwo = new QRadioButton(centralwidget);
        radioTwo->setObjectName("radioTwo");
        sizePolicy2.setHeightForWidth(radioTwo->sizePolicy().hasHeightForWidth());
        radioTwo->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(radioTwo);

        radioThree = new QRadioButton(centralwidget);
        radioThree->setObjectName("radioThree");
        sizePolicy2.setHeightForWidth(radioThree->sizePolicy().hasHeightForWidth());
        radioThree->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(radioThree);

        radioFour = new QRadioButton(centralwidget);
        radioFour->setObjectName("radioFour");
        sizePolicy2.setHeightForWidth(radioFour->sizePolicy().hasHeightForWidth());
        radioFour->setSizePolicy(sizePolicy2);
        radioFour->setChecked(true);

        verticalLayout->addWidget(radioFour);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(17, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        aboutButton = new QPushButton(centralwidget);
        aboutButton->setObjectName("aboutButton");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(aboutButton->sizePolicy().hasHeightForWidth());
        aboutButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(aboutButton);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        sizePolicy3.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(loadButton);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        sizePolicy3.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(startButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        WelcomeWindow->setCentralWidget(centralwidget);
        logo->raise();
        radioThree->raise();

        retranslateUi(WelcomeWindow);

        QMetaObject::connectSlotsByName(WelcomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WelcomeWindow)
    {
        WelcomeWindow->setWindowTitle(QCoreApplication::translate("WelcomeWindow", "Luzo Z+", nullptr));
        logo->setText(QString());
        label->setText(QCoreApplication::translate("WelcomeWindow", "Number of players:", nullptr));
        radioTwo->setText(QCoreApplication::translate("WelcomeWindow", "Two players", nullptr));
        radioThree->setText(QCoreApplication::translate("WelcomeWindow", "Three players", nullptr));
        radioFour->setText(QCoreApplication::translate("WelcomeWindow", "Four players", nullptr));
        aboutButton->setText(QCoreApplication::translate("WelcomeWindow", "About", nullptr));
        loadButton->setText(QCoreApplication::translate("WelcomeWindow", "Load saved game", nullptr));
        startButton->setText(QCoreApplication::translate("WelcomeWindow", "Start a new game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomeWindow: public Ui_WelcomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H
