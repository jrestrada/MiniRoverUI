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

QString video_loc =  "/home/josue/code/MediaPlayer/sample_1280x720.mp4";
QString video_loc2 = "/home/josue/videoplayback.mp4"; 

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    video_loc = "/home/josue/code/MediaPlayer/sample_1280x720.mp4";
    video_loc2 = "/home/josue/videoplayback.mp4";

    setWindowTitle("Miniature Inspection Rover");
    d_player2 = new QDockWidget(tr("Auxiliary Camera"), this); // Just declaring this makes it semi visible
    d_toolbar = new QDockWidget(tr("Tools"), this);
    w_player2 = new QWidget;
    l_player2 = new QVBoxLayout;
    w_toolbar = new QWidget;
    l_toolbar = new QVBoxLayout;
    status_bar = new QStatusBar;
    
    main_view = new CamView(0);
    second_view = new CamView(1);
    label = new QLabel;
    arc_logo.load("../MRUI/ARCLogo.png");
    label->setPixmap(arc_logo.scaled(100,100));

    b_quit = new QPushButton("Quit") ;
    b_switch_cam = new QPushButton("Switch Cameras");
    b_playback = new QPushButton("Play Recorded Video");
    b_capture = new QPushButton("Capture Image") ;

    d_toolbar->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea);
    d_player2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea| Qt::TopDockWidgetArea);

    connect(b_capture, SIGNAL(clicked()), this, SLOT(captureImages()));
    connect(b_quit, SIGNAL(clicked()), this, SLOT(quitApp()));
    connect(b_playback, SIGNAL(clicked()), this, SLOT(playBack()));
    connect(b_switch_cam, SIGNAL(clicked()), this, SLOT(swapCameras()));

    setUi();
}

MainWindow::~MainWindow(){
}

void MainWindow::setUi(){
    l_toolbar->addWidget(label);
    l_toolbar->addWidget(b_switch_cam);
    l_toolbar->addWidget(b_playback);
    l_toolbar->addWidget(b_capture);
    l_toolbar->addStretch(200);
    l_toolbar->addWidget(b_quit);
    w_toolbar->setLayout(l_toolbar);
    d_toolbar->setWidget(w_toolbar);

    l_player2->addWidget(second_view);
    w_player2->setLayout(l_player2);
    d_player2->setWidget(w_player2);
    d_player2->setFloating(true);
    d_player2->resize(400,300);

    addDockWidget(Qt::RightDockWidgetArea, d_toolbar);
    setCentralWidget(main_view);
    centralWidget()->resize(500,500);
    setStatusBar(status_bar);
}

void MainWindow::quitApp(){
    qApp->exit(0);
}

void MainWindow::swapCameras(){
    if (!swapped){
        if (playback) {
            main_view->play(video_loc2);
            second_view->play(video_loc);
        } else {
            main_view->play(1);
            second_view->play(0);
        }
        d_player2->setWindowTitle("Main Camera");
        swapped = true;
    } else {
        if (playback) {
            main_view->play(video_loc);
            second_view->play(video_loc2);
        } else {
            main_view->play(0);
            second_view->play(1);
        }
        d_player2->setWindowTitle("Auxiliary Camera");
        swapped = false;        
    }
    status_bar->showMessage("Camera View Swapped");
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

void MainWindow::playBack(){
    if (!playback){
        if (swapped) {
            main_view->play(video_loc2);
            second_view->play(video_loc);
        } else {
            main_view->play(video_loc);
            second_view->play(video_loc2);
        }
        b_playback->setText("Live video");
        status_bar->showMessage(video_loc);
        playback = true;
    } else {
        if (swapped) {
            main_view->play(1);
            second_view->play(0);
        } else {
            main_view->play(0);
            second_view->play(1);
        }
        b_playback->setText("Play Recorded Video");
        status_bar->showMessage("Playing Live Video");
        playback = false;        
    }
}

void MainWindow::captureImages(){
    // main_view->takeImage();
    second_view->takeImage();
}
