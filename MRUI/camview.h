#ifndef CAMVIEW_H
#define CAMVIEW_H

#include <QCamera>
#include <QImageCapture>

#include <QWidget>
#include <QObject>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMediaRecorder>
#include <QAudioInput>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QtMultimediaWidgets/QVideoWidget>


namespace Ui{
    class Widget;
}

class QCamera;
class QCameraImageCapture;
class QVBoxLayout;
class QCheckbox;
class QLabel;
class QLineEdit;
class QPushbutton;

class CamView : public QWidget {
    Q_OBJECT
public:
    explicit CamView(QWidget *parent = nullptr);
    QVideoWidget *view_finder_;

private slots:
    void setCamera(const QCameraDevice &cameraDevice);
    void startCamera();
    void stopCamera();
    void updateCameras();
    void switchCamera();
    
private:
    Ui::Widget *ui;

    QActionGroup *video_devices_group_ = nullptr;
    QMediaDevices devices_;
    QMediaCaptureSession capture_session_;
    QSharedPointer<QCamera> camera_;
    QSharedPointer<QAudioInput> audio_input_;
    QSharedPointer<QMediaRecorder> media_recorder_;
    QImageCapture *image_capture_;
    QBoxLayout *layout_;
    // QVideoWidget *view_finder_;
    QList<QCameraDevice> available_cameras;
    int cameras_count = 0;
    int i = 0;
};

#endif // CAMVIEW_H

