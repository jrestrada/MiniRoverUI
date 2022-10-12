#include "mainwindow.h"
#include "camview.h"

#include <QMediaRecorder>
#include <QVideoWidget>
#include <QCameraDevice>
#include <QMediaMetaData>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioInput>

#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QDockWidget>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
        setWindowTitle("TESTS");
        QWidget *window = new QWidget;
        window->setWindowTitle("Slider Example");

        auto viewTest = new CamView;
        QDockWidget *rightDock = new QDockWidget(tr("Actions"), this);
        QDockWidget *topDock = new QDockWidget(tr("Exposure"), this); // Just declaring this makes it semi visible
        
        spinbox = new QSpinBox;
        slider = new QSlider(Qt::Horizontal);
        label = new QLabel("<h2><i>Mini</i>""<font color=green>Rover</font><h2>");
        quitbutton = new QPushButton("quit") ;
        switch_video_button = new QPushButton("Switch Video Input") ;
        resetVal = new QPushButton("Set Zero") ;

        slider->setRange(0,130);
        spinbox->setRange(0,130);
        spinbox->setValue(26);
        rightDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea);
        topDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea| Qt::TopDockWidgetArea);

        connect(resetVal, SIGNAL(clicked()),this , SLOT(resetValue()));
        connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
        connect(quitbutton, SIGNAL(clicked()), this, SLOT(quitApp()));
        connect(switch_video_button, SIGNAL(clicked()), viewTest, SLOT(switchCamera()));
        // connect(switch_video_button, SIGNAL(clicked()), viewTest, SLOT(stopCamera()));

        auto layout1 = new QHBoxLayout;
        layout1->addWidget(label);
        layout1->addWidget(spinbox);
        layout1->addWidget(slider);
        layout1->addWidget(resetVal);
        layout1->addWidget(quitbutton);

        window->setLayout(layout1);
        setCentralWidget(viewTest->view_finder_);
        topDock->setWidget(window);
        rightDock->setWidget(switch_video_button);
        addDockWidget(Qt::RightDockWidgetArea, rightDock);
        addDockWidget(Qt::TopDockWidgetArea, topDock);
}

MainWindow::~MainWindow(){
}

void MainWindow::resetValue(){
    spinbox->setValue(0);
}

void MainWindow::quitApp(){
    qApp->exit(0);
}

