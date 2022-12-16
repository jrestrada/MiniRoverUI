#include "captureSession.h"
#include "playable.h"
#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QAudioInput>

QList<QCameraDevice> CaptureSession::s_devices;
QList<QCamera*> CaptureSession::s_cameras;

CaptureSession::CaptureSession() : public IPlayable, public QMediaCaptureSession{
    m_idx = 0;
    m_idx ++;  
    m_capture_session = new QMediaCaptureSession;
    play();    
    m_cameras_count = s_devices.length();
}

void CaptureSession::setupCamera(QCamera * selected_cam){
    m_camera = selected_cam;     // reset from QSharedPointer
    m_capture_session->setCamera(m_camera); // main functionality

    if (!m_media_recorder) {
        m_media_recorder.reset(new QMediaRecorder);
        m_capture_session->setRecorder(m_media_recorder.data());
    }
    m_img_cap = new QImageCapture;
    m_capture_session->setImageCapture(m_img_cap);
    if (m_camera->cameraFormat().isNull())
    {
        auto formats = m_camera->cameraDevice().videoFormats();
        if (!formats.isEmpty()) {
            QCameraFormat bestFormat;
            for (const auto &fmt : formats) {
                if (bestFormat.maxFrameRate() < 29 && fmt.maxFrameRate() > bestFormat.maxFrameRate())
                    bestFormat = fmt;
                else if (bestFormat.maxFrameRate() == fmt.maxFrameRate() &&
                         bestFormat.resolution().width()*bestFormat.resolution().height() <
                             fmt.resolution().width()*fmt.resolution().height())
                    bestFormat = fmt;
            }

            m_camera->setCameraFormat(bestFormat);
            m_media_recorder->setVideoFrameRate(bestFormat.maxFrameRate());
        }
    }
    m_camera->start();
}

void CaptureSession::startCamera(){
    m_camera->start();
}

void CaptureSession::stopCamera(){
    m_camera->stop();
}

void CaptureSession::takeImage(){
    if (m_camera != nullptr){
       m_img_cap->captureToFile(fileName());
       m_watcher->updateStatusBar("Picture saved as: " + fileName());
    } m_watcher->updateStatusBar("Picture not captured, camera " + QString::number(m_idx) +" not set" );
}

void CaptureSession::record(){
    if (m_camera != nullptr){
       m_media_recorder->setOutputLocation(QUrl::fromLocalFile(fileName()));
       m_media_recorder->record();
       m_watcher->updateStatusBar("Began Recording " + fileName());
       m_watcher->b_stop->setEnabled(true);
       m_watcher->b_record->setEnabled(false);
    } m_watcher->updateStatusBar("Recording not started, camera " + QString::number(m_idx) +" not set" );
} 

void CaptureSession::stop(){
    m_media_recorder->stop();
    m_watcher->updateStatusBar("Recording Saved as " + fileName());
    m_watcher->b_stop->setEnabled(false);
    m_watcher->b_record->setEnabled(true);

}

QList<QCamera*> CaptureSession::availableCameras() {
    if (CaptureSession::s_devices.isEmpty()) { // Only once!
        s_devices = QMediaDevices::videoInputs();
        for (const auto &device : s_devices) {
            qDebug() << "Found " << device.description();
            s_cameras.append( new QCamera(device) );
        }
    }
    return CaptureSession::s_cameras;
}

QCamera *CaptureSession::camera(int i) {
    auto cams = availableCameras();
    if (i >= cams.count()) {
        qDebug() << "Ops, camera" << i << "not found!";
        return nullptr;}
    return cams[i];
}

void CaptureSession::play(int i) override{ // Play camera!
    auto c = camera(i);
    if (!c) {
        qDebug() << "Ops, cannot play camera," << i << "doesn't exit!";
        return;
    }
    setupCamera(c);
    qDebug() << "Playing camera" << i;
}