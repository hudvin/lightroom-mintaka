/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dndtableview.h"
#include "imagelistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_6;
    QPushButton *generateKeywordsBtn;
    QPushButton *saveBtn;
    DndTableView *keywordsTable;
    ImageListWidget *lrImages;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(467, 339);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        generateKeywordsBtn = new QPushButton(centralWidget);
        generateKeywordsBtn->setObjectName(QStringLiteral("generateKeywordsBtn"));

        verticalLayout_6->addWidget(generateKeywordsBtn);

        saveBtn = new QPushButton(centralWidget);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        verticalLayout_6->addWidget(saveBtn);

        keywordsTable = new DndTableView(centralWidget);
        keywordsTable->setObjectName(QStringLiteral("keywordsTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(keywordsTable->sizePolicy().hasHeightForWidth());
        keywordsTable->setSizePolicy(sizePolicy1);
        keywordsTable->setMouseTracking(false);
        keywordsTable->setFocusPolicy(Qt::WheelFocus);
        keywordsTable->setAcceptDrops(true);
        keywordsTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        keywordsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        keywordsTable->setDragDropOverwriteMode(false);
        keywordsTable->setDragDropMode(QAbstractItemView::DragDrop);
        keywordsTable->setDefaultDropAction(Qt::MoveAction);
        keywordsTable->setAlternatingRowColors(false);
        keywordsTable->setSelectionMode(QAbstractItemView::SingleSelection);
        keywordsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        keywordsTable->setGridStyle(Qt::DotLine);
        keywordsTable->horizontalHeader()->setDefaultSectionSize(90);
        keywordsTable->horizontalHeader()->setMinimumSectionSize(27);
        keywordsTable->horizontalHeader()->setStretchLastSection(true);
        keywordsTable->verticalHeader()->setVisible(false);
        keywordsTable->verticalHeader()->setDefaultSectionSize(18);
        keywordsTable->verticalHeader()->setMinimumSectionSize(15);

        verticalLayout_6->addWidget(keywordsTable);


        horizontalLayout->addLayout(verticalLayout_6);

        lrImages = new ImageListWidget(centralWidget);
        lrImages->setObjectName(QStringLiteral("lrImages"));
        lrImages->setProperty("showDropIndicator", QVariant(false));
        lrImages->setDragEnabled(true);
        lrImages->setDragDropMode(QAbstractItemView::NoDragDrop);
        lrImages->setMovement(QListView::Static);
        lrImages->setResizeMode(QListView::Adjust);
        lrImages->setViewMode(QListView::IconMode);

        horizontalLayout->addWidget(lrImages);


        horizontalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 467, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        generateKeywordsBtn->setText(QApplication::translate("MainWindow", "Generate Keywords", 0));
        saveBtn->setText(QApplication::translate("MainWindow", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
