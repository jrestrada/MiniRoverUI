#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "camview.h"

#include <QCamera>
#include <QImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QMediaMetaData>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QAudioInput>
#include <QPixmap>
#include <QStatusBar>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QVBoxLayout>


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void quitApp();
    void swapCameras();
    void playBack();
    void setUi();

private slots:

protected:

private:

    QWidget *w_player2;
    QWidget *w_toolbar;
    QDockWidget *d_player2;
    QDockWidget *d_toolbar; 
    QVBoxLayout *l_player2;
    QVBoxLayout *l_toolbar;
    QPixmap arc_logo;
    QLabel *label;
<<<<<<< HEAD
    QPushButton *b_quit;
    QPushButton *b_capture;
    QPushButton *b_switch_cam;
    QPushButton *b_playback;
    CamView *main_view;
    CamView *second_view;
    QStatusBar *status_bar;
    void saveSettings();
    void reloadSettings();
    bool swapped = false;
    bool playback = false;
=======
    QPushButton *quitbutton;
    QPushButton *resetVal;
    QPushButton *switch_video_button;
    QHBoxLayout *top_dock_layout;
    QVBoxLayout *right_dock_layout;
    CamView *main_cam;
    CamView *second_cam;
    CamView *main_view;
    CamView *second_view;
    bool swapped = false;

>>>>>>> parent of 1e529ed... Added capture-image function
};
#endif // MAINWINDOW_H
