#include "mainwindow.h"
#include "camview.h"

#include <QMediaRecorder>
#include <QVideoWidget>
#include <QCameraDevice>
#include <QMediaMetaData>
#include <QMediaDevices>
#include <QSettings>
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
        label = new QLabel;
        arc_logo.load("../MRUI/ARCLogo.png");
        label->setPixmap(arc_logo.scaled(100,100));
        quitbutton = new QPushButton("quit") ;
        switch_video_button = new QPushButton("Switch Video Input") ;
        capture_button = new QPushButton("Capture Image") ;

        main_view = main_cam;
        second_view = second_cam;

        slider->setRange(0,130);
        spinbox->setRange(0,130);
        spinbox->setValue(26);
        rightDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea);
        topDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea| Qt::TopDockWidgetArea);

        connect(capture_button, SIGNAL(clicked()), main_cam , SLOT(takeImage()));
        connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
        connect(quitbutton, SIGNAL(clicked()), this, SLOT(quitApp()));
        // connect(switch_video_button, SIGNAL(clicked()), main_cam, SLOT(switchCamera()));
        connect(switch_video_button, SIGNAL(clicked()), this, SLOT(swapCameras()));

        top_dock_layout->addWidget(label);
        top_dock_layout->addWidget(spinbox);
        top_dock_layout->addWidget(slider);
        top_dock_layout->addWidget(capture_button);
        top_dock_layout->addWidget(quitbutton);
        top_dock_widget->setLayout(top_dock_layout);
        topDock->setWidget(top_dock_widget);
        right_dock_layout->addWidget(switch_video_button);
        addDockWidget(Qt::TopDockWidgetArea, topDock);
        addDockWidget(Qt::RightDockWidgetArea, rightDock);
        setUi();
}

MainWindow::~MainWindow(){
}

void MainWindow::setUi(){
    right_dock_layout->addWidget(second_view->m_view_finder);
    right_dock_widget->setLayout(right_dock_layout);
    rightDock->setWidget(right_dock_widget);

    auto w = new QWidget;
    auto l = new QVBoxLayout;
    w->setLayout(l);
    l->addWidget(main_view->m_view_finder);
    setCentralWidget(w);
    setCentralWidget(main_view->m_view_finder);
    centralWidget()->resize(500,500);
    auto ql = new QPushButton("okok",w);
    // ql->move(0,200);
    
    ql->repaint();
}

void MainWindow::resetValue(){
    spinbox->setValue(0);
}

void MainWindow::quitApp(){
    qApp->exit(0);
}

void MainWindow::swapCameras(){
    // if (!swapped){
    //     main_view = second_cam;
    //     second_view = main_cam;
    //     swapped = true;
    // } else {
    //     main_view = main_cam;
    //     second_view = second_cam;
    //     swapped = false;        
    // }
    setUi();
    qDebug() << "swapped";
}

void MainWindow::saveSettings() {
    QSettings settings("FIU-ARC", "MediaPlayer");
    settings.beginGroup( "MainWindow" );
    settings.setValue( "geometry", saveGeometry() );
    settings.setValue( "saveState", saveState() );
    settings.setValue( "maximized", isMaximized() );
    settings.endGroup();
}

void MainWindow::reloadSettings() {
    QSettings settings("FIU-ARC", "MediaPlayer");
    settings.beginGroup( "MainWindow" );
    restoreGeometry(settings.value( "geometry", saveGeometry() ).toByteArray());
    restoreState(settings.value( "saveState", saveState() ).toByteArray());
    settings.endGroup();
}
