#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QMediaMetaData>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QAudioInput>

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void resetValue();
    void quitApp();
    // void saveMetaData();

private slots:

protected:

private:
    QSpinBox *spinbox;
    QSlider *slider;
    QLabel *label;
    QPushButton *quitbutton;
    QPushButton *resetVal;
    QListWidget *customerList;
    QPushButton *switch_video_button;

    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    bool m_doImageCapture = true;
};
#endif // MAINWINDOW_H
