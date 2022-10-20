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
#include <QVBoxLayout>
#include <QApplication>
#include <QDockWidget>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
        setWindowTitle("TESTS");
        topDock = new QDockWidget(tr("Exposure"), this); // Just declaring this makes it semi visible
        rightDock = new QDockWidget(tr("Actions"), this);

        top_dock_widget = new QWidget;
        top_dock_layout = new QHBoxLayout;

        right_dock_widget = new QWidget;
        right_dock_layout = new QVBoxLayout;

        main_cam = new CamView(0);
        second_cam = new CamView(1);
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
        // connect(switch_video_button, SIGNAL(clicked()), main_cam, SLOT(switchCamera()));
        connect(switch_video_button, SIGNAL(clicked()), this, SLOT(swapCameras()));

        top_dock_layout->addWidget(label);
        top_dock_layout->addWidget(spinbox);
        top_dock_layout->addWidget(slider);
        top_dock_layout->addWidget(resetVal);
        top_dock_layout->addWidget(quitbutton);

        this->setUi();
}

MainWindow::~MainWindow(){
}

void MainWindow::setUi(){

    right_dock_layout->addWidget(second_cam->m_view_finder);
    right_dock_layout->addWidget(switch_video_button);
    
    top_dock_widget->setLayout(top_dock_layout);
    right_dock_widget->setLayout(right_dock_layout);
    topDock->setWidget(top_dock_widget);
    // topDock->widget()->resize(500,1080);
    rightDock->setWidget(right_dock_widget);
    
    main_cam->m_view_finder->resize(800,800);
    setCentralWidget(main_cam->m_view_finder);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);
    addDockWidget(Qt::TopDockWidgetArea, topDock);
}

void MainWindow::resetValue(){
    spinbox->setValue(0);
}

void MainWindow::quitApp(){
    qApp->exit(0);
}

void MainWindow::swapCameras(){
    this->setUi();
    qDebug() << "swapped";
}