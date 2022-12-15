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
#include <QListWidgetItem>
#include <QListWidget>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QToolBox>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton *b_record;
    QPushButton *b_stop;
public slots:
    void quitApp();
    void swapCameras();
    void swapMenu();
    void playBack();
    void populate();
    void assign();
    void findVideos();
    void playVideos(QListWidgetItem *video);
    void updateStatusBar(QString newMessage);

private slots:

protected:

private:
    QStatusBar *status_bar;
    QWidget *w_player2;
    QWidget *w_toolbar;
    QWidget *w_record_stack;
    QVBoxLayout *l_record_stack;
    QVBoxLayout *l_playback_stack;
    QWidget *w_playback_stack;
    QStackedWidget *w_stack;
    QDockWidget *d_player2;
    QDockWidget *d_toolbar; 
    QVBoxLayout *l_player2;
    QVBoxLayout *l_toolbar;
    QToolBox *w_toolbox;
    QPixmap arc_logo;
    QLabel *label;
    QListWidget *w_vid_list;
    QPushButton *b_quit;
    QPushButton *b_capture;
    QPushButton *b_switch_cam;

    CamView *main_view;
    CamView *second_view;
    void saveSettings();
    void reloadSettings();
    bool swapped = false;
    bool playback = false;
};
#endif // MAINWINDOW_H
