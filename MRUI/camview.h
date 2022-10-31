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
#include <QMediaPlayer>
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

class CamView : public QVideoWidget {
    Q_OBJECT
public:
    explicit CamView(int idx, QWidget *parent = nullptr);
    QVideoWidget *m_view_finder;
    static QList<QCamera*> cameras();
    static QCamera *camera(int i);
    void play(int device);
    void play(const QString &file);
    void takeImage();

private slots:
    void setCamera(const QCameraDevice &cameraDevice);
    void startCamera();
    void stopCamera();
    void updateCameras();
    // void takeImage();

private:
    Ui::Widget *m_ui;

    QActionGroup *m_video_devices_group = nullptr;
    QMediaDevices m_devices;
    QMediaCaptureSession *m_capture_session;
    QSharedPointer<QCamera> m_camera;
    QSharedPointer<QAudioInput> m_audio_input;
    QSharedPointer<QMediaRecorder> m_media_recorder;
    QImageCapture *m_image_capture;
    QBoxLayout *m_layout_;
    QMediaPlayer *m_player;
    
    static QList<QCameraDevice> s_devices;
    static QList<QCamera*> s_cameras;

    bool m_isCapturingImage = false;
    bool m_doImageCapture = true;

    int m_cameras_count = 0;
    int m_cam_index;
};

#endif // CAMVIEW_H

