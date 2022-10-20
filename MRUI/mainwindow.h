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

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
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
    void resetValue();
    void quitApp();
    // void saveMetaData();
    void swapCameras();
    void setUi();

private slots:

protected:

private:
    QWidget *top_dock_widget;
    QWidget *right_dock_widget;
    QDockWidget *rightDock; 
    QDockWidget *topDock;
    QPixmap arc_logo;
    QSpinBox *spinbox;
    QSlider *slider;
    QLabel *label;
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

};
#endif // MAINWINDOW_H
