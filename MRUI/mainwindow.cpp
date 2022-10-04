#include "mainwindow.h"
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QDockWidget>
#include<QListWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
        setWindowTitle("Slider Example");
        QWidget *window = new QWidget;
        window->setWindowTitle("Slider Example");

        spinbox = new QSpinBox;
        slider = new QSlider(Qt::Horizontal);
        label = new QLabel("<h2><i>hello!</i>""<font color=green>Qt!</font><h2>");
        quitbutton = new QPushButton("quit") ;
        resetVal = new QPushButton("Set Zero") ;

        slider->setRange(0,130);
        spinbox->setRange(0,130);
        spinbox->setValue(26);

        QObject::connect(resetVal, SIGNAL(clicked()),this , SLOT(resetValue()));
        QObject::connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        QObject::connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
        QObject::connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
        QObject::connect(quitbutton, SIGNAL(clicked()), this, SLOT(quitApp()));

        auto *layout = new QHBoxLayout;
        layout ->addWidget(label);
        layout ->addWidget(spinbox);
        layout ->addWidget(slider);
        layout ->addWidget(resetVal);
        layout ->addWidget(quitbutton);

        window->setLayout(layout);
        setCentralWidget(window);

        QDockWidget *dock = new QDockWidget(tr("list"), this);
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        customerList = new QListWidget(dock);
        customerList->addItems(QStringList()
         << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
                 << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
                 << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
                 << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
                 << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
                 << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
         dock->setWidget(customerList);
         addDockWidget(Qt::RightDockWidgetArea, dock);
//         viewMenu->addAction(dock->toggleViewAction());
}

MainWindow::~MainWindow(){
}

void MainWindow::resetValue(){
    spinbox->setValue(0);
    customerList->clear();
}

void MainWindow::quitApp(){
    qApp->exit(0);
}
