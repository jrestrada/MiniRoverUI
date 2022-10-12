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

    // void setCamera(const QCameraDevice &cameraDevice);

    // void startCamera();
    // void stopCamera();

    // void record();
    // void pause();
    // void stop();
    // void setMuted(bool);

    // void takeImage();
    // void displayCaptureError(int, QImageCapture::Error, const QString &errorString);

    // void configureCaptureSettings();
    // void configureVideoSettings();
    // void configureImageSettings();

    // void displayRecorderError();
    // void displayCameraError();

    // void updateCameraDevice(QAction *action);

    // void updateCameraActive(bool active);
    // void updateCaptureMode();
    // void updateRecorderState(QMediaRecorder::RecorderState state);
    // void setExposureCompensation(int index);

    // void updateRecordTime();

    // void processCapturedImage(int requestId, const QImage &img);

    // void displayViewfinder();
    // void displayCapturedImage();

    // void readyForCapture(bool ready);
    // void imageSaved(int id, const QString &fileName);

    // void updateCameras();

    // void showMetaDataDialog();
protected:

private:
    QSpinBox *spinbox;
    QSlider *slider;
    QLabel *label;
    QPushButton *quitbutton;
    QPushButton *resetVal;
    QListWidget *customerList;

    QActionGroup *videoDevicesGroup  = nullptr;

    QMediaDevices m_devices;
    QMediaCaptureSession m_captureSession;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QAudioInput> m_audioInput;
    QImageCapture *m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    bool m_doImageCapture = true;
};
#endif // MAINWINDOW_H
