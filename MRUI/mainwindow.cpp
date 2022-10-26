#include "mainwindow.h"
#include "camview.h"

#include <QMediaRecorder>
#include <QVideoWidget>
#include <QCameraDevice>
#include <QMediaMetaData>
#include <QMediaDevices>
<<<<<<< HEAD
#include <QSettings>
=======
#include <QAudioDevice>
#include <QAudioInput>

>>>>>>> parent of 1e529ed... Added capture-image function
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
<<<<<<< HEAD
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

    connect(b_capture, SIGNAL(clicked()), main_view , SLOT(takeImage()));
    connect(b_quit, SIGNAL(clicked()), this, SLOT(quitApp()));
    connect(b_playback, SIGNAL(clicked()), this, SLOT(playBack()));
    connect(b_switch_cam, SIGNAL(clicked()), this, SLOT(swapCameras()));

    setUi();
=======
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
        arc_logo.load("/home/josue/ARCLogo.png");
        label->setPixmap(arc_logo.scaled(100,100));
        quitbutton = new QPushButton("quit") ;
        switch_video_button = new QPushButton("Switch Video Input") ;
        resetVal = new QPushButton("Set Zero") ;

        main_view = main_cam;
        second_view = second_cam;

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
        top_dock_widget->setLayout(top_dock_layout);
        topDock->setWidget(top_dock_widget);
        addDockWidget(Qt::TopDockWidgetArea, topDock);
        this->setCentralWidget(main_view->m_view_finder);

        this->setUi();
>>>>>>> parent of 1e529ed... Added capture-image function
}

MainWindow::~MainWindow(){
}

void MainWindow::setUi(){
<<<<<<< HEAD
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
=======
    right_dock_layout->addWidget(switch_video_button);
    right_dock_layout->addWidget(second_view->m_view_finder);
    this->setCentralWidget(main_view->m_view_finder);
    //CENTRAL WIDGET IS BEING COVERED BY DOCKS
    right_dock_widget->setLayout(right_dock_layout);
    rightDock->setWidget(right_dock_widget);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);
}

void MainWindow::resetValue(){
    spinbox->setValue(0);
>>>>>>> parent of 1e529ed... Added capture-image function
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
<<<<<<< HEAD
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
=======
    this->setUi();
    qDebug() << "swapped";
>>>>>>> parent of 1e529ed... Added capture-image function
}