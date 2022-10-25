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
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QDockWidget>
#include <QListWidget>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
        setWindowTitle("TESTS");
        d_player2 = new QDockWidget(tr("Auxiliary Camera"), this); // Just declaring this makes it semi visible
        d_toolbar = new QDockWidget(tr("Tools"), this);
        w_player2 = new QWidget;
        l_player2 = new QVBoxLayout;
        w_toolbar = new QWidget;
        l_toolbar = new QVBoxLayout;

        main_cam = new CamView(0);
        second_cam = new CamView(1);
        label = new QLabel;
        arc_logo.load("../MRUI/ARCLogo.png");
        label->setPixmap(arc_logo.scaled(100,100));

        b_quit = new QPushButton("quit") ;
        b_switch_cam = new QPushButton("Switch Cameras");
        b_playback = new QPushButton("Play Recorded Video");
        b_capture = new QPushButton("Capture Image") ;

        main_view = main_cam;
        second_view = second_cam;

        d_toolbar->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea);
        d_player2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea| Qt::TopDockWidgetArea);

        connect(b_capture, SIGNAL(clicked()), main_cam , SLOT(takeImage()));
        connect(b_quit, SIGNAL(clicked()), this, SLOT(quitApp()));
        connect(b_playback, SIGNAL(clicked()), this, SLOT(temp()));
        connect(b_switch_cam, SIGNAL(clicked()), this, SLOT(swapCameras()));

        l_toolbar->addWidget(label);
        l_toolbar->addWidget(b_switch_cam);
        l_toolbar->addWidget(b_playback);
        l_toolbar->addWidget(b_capture);
        l_toolbar->addWidget(b_quit);
        w_toolbar->setLayout(l_toolbar);
        d_toolbar->setWidget(w_toolbar);
        addDockWidget(Qt::RightDockWidgetArea, d_toolbar);
        setUi();
}

MainWindow::~MainWindow(){
}

void MainWindow::setUi(){
    l_player2->addWidget(second_view);
    w_player2->setLayout(l_player2);
    d_player2->setWidget(w_player2);
    d_player2->setFloating(true);
    setCentralWidget(main_view);
    centralWidget()->resize(500,500);
}

void MainWindow::quitApp(){
    qApp->exit(0);
}

void MainWindow::swapCameras(){
    if (!swapped){
        main_view = second_cam;
        second_view = main_cam;
        d_player2->setWindowTitle("Main Camera");
        swapped = true;
    } else {
        main_view = main_cam;
        second_view = second_cam;
        d_player2->setWindowTitle("Auxiliary Camera");
        swapped = false;        
    }
    setUi();
    qDebug() << "Camera View Swapped";
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

void MainWindow::temp(){
    main_cam->play("/home/josue/code/MediaPlayer/sample_1280x720.mp4");
}