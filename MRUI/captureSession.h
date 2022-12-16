#ifndef CAPTURESESSION_H
#define CAPTURESESSION_H

#include <QImageCapture>
#include <QCamera>
#include <QMediaRecorder>
#include <QAudioInput>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include "playable.h"

class CaptureSession : public IPlayable, public QMediaCaptureSession {
    Q_OBJECT
    public:
        void Play() override;
        static QList<QCamera*> availableCameras();
        static QCamera *camera(int i);
public slots:
    void takeImage();
    void record();
    void stop();

private slots:
    // void setCamera(const QCameraDevice &cameraDevice);
    void setupCamera(QCamera * selected_cam);
    void startCamera();
    void stopCamera();
    private:
        QCamera *m_camera = nullptr;
        QSharedPointer<QMediaRecorder> m_media_recorder;
        QSharedPointer<QAudioInput> m_audio_input;
        QMediaDevices m_devices;
        QImageCapture *m_img_cap;

        bool m_isCapturingImage = false;
        bool m_doImageCapture = true;
        int m_cameras_count = 0;
        static QList<QCameraDevice> s_devices;
        static QList<QCamera*> s_cameras;
        static int m_idx;
};

#endif // CAPTURESESSION_H
