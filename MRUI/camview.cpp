#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QActionGroup>
#include <QAudioInput>
#include <QVBoxLayout>
#include <QMediaPlayer>

#include <QFileInfo>

#include "camview.h"

QList<QCameraDevice> CamView::s_devices;
QList<QCamera*> CamView::s_cameras;

CamView::CamView(int idx, QWidget *parent) : QVideoWidget(parent){

    m_cam_index = idx;
    m_capture_session = new QMediaCaptureSession;

    //Camera devices:
    m_video_devices_group = new QActionGroup(this);
    m_video_devices_group->setExclusive(true);
    updateCameras();
    connect(&m_devices, &QMediaDevices::videoInputsChanged, this, &CamView::updateCameras);
<<<<<<< HEAD
    play(m_cam_index);   
    m_cameras_count = s_devices.length();
=======
    m_available_cameras = QMediaDevices::videoInputs();
    setCamera(m_available_cameras[m_cam_index]);   
    m_cameras_count = m_available_cameras.length();
>>>>>>> parent of 1e529ed... Added capture-image function

}

void CamView::setCamera(const QCameraDevice &cameraDevice)
{
    m_camera.reset(new QCamera(cameraDevice));     // reset from QSharedPointer
    m_capture_session->setCamera(m_camera.data()); // main functionality

    // connect(m_camera.data(), &QCamera::activeChanged, this, &CamView::updateCameraActive);
    // connect(m_camera.data(), &QCamera::errorOccurred, this, &CamView::displayCameraError);

    if (!m_media_recorder) {
        m_media_recorder.reset(new QMediaRecorder);
        m_capture_session->setRecorder(m_media_recorder.data());
        // connect(media_recorder.data(), &QMediaRecorder::recorderStateChanged, this, &CamView::updateRecorderState);
    }

    m_image_capture = new QImageCapture;
    m_capture_session->setImageCapture(m_image_capture);

    // connect(m_media_recorder.data(), &QMediaRecorder::durationChanged, this, &CamView::updateRecordTime);
    // connect(m_media_recorder.data(), &QMediaRecorder::errorChanged, this, &CamView::displayRecorderError);

    m_capture_session->setVideoOutput(this);

    // updateCameraActive(m_camera->isActive());
    // updateRecorderState(media_recorder_->recorderState());

    // connect(image_capture_, &QImageCapture::readyForCaptureChanged, this, &CamView::readyForCapture);
    // connect(image_capture_, &QImageCapture::imageCaptured, this, &CamView::processCapturedImage);
    // connect(image_capture_, &QImageCapture::imageSaved, this, &CamView::imageSaved);
    // connect(image_capture_, &QImageCapture::errorOccurred, this, &CamView::displayCaptureError);
    // readyForCapture(image_capture_->isReadyForCapture());

    // updateCaptureMode();

    if (m_camera->cameraFormat().isNull())
    {
        auto formats = cameraDevice.videoFormats();
        if (!formats.isEmpty()) {
            // Choose a decent camera format: Maximum resolution at at least 30 FPS
            // we use 29 FPS to compare against as some cameras report 29.97 FPS...
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
void CamView::updateCameras(){
    // const QList<QCameraDevice> devices = QMediaDevices::videoInputs();
    // for (const QCameraDevice &camera_device : devices) {
        // QAction *video_device_action = new QAction(camera_device.description(), m_video_devices_group);
        // video_device_action->setCheckable(true);
        // video_device_action->setData(QVariant::fromValue(camera_device));
        // if (camera_device == QMediaDevices::defaultVideoInput())
            // video_device_action->setChecked(true);
    // }
}

void CamView::startCamera(){
    m_camera->start();
}

void CamView::stopCamera(){
    m_camera->stop();
    qDebug() << "buttonpressed";
}

<<<<<<< HEAD
void CamView::takeImage(){
    m_image_capture->captureToFile("./test1.jpg");
    qDebug() << "image captured";
}

QList<QCamera*> CamView::cameras() {
    if (CamView::s_devices.isEmpty()) { // Only once!
        s_devices = QMediaDevices::videoInputs();
        for (const auto &device : s_devices) {
            qDebug() << "Found " << device.description();
            s_cameras.append( new QCamera(device) );
        }
    }
    return CamView::s_cameras;
}

QCamera *CamView::camera(int i) {
    auto cams = cameras();
    if (i >= cams.count()) {
        qDebug() << "Ops, camera" << i << "not found!";
        return nullptr;
    }
    return cams[i];
}

void CamView::play(int i) { // Play camera!
    auto c = camera(i);
    if (!c) {
        qDebug() << "Ops, cannot play camera," << i << "doesn't exit!";
        return;
    }
    m_capture_session->setCamera(c);
    m_capture_session->setVideoOutput( this );
    c->start();
    qDebug() << "Playing camera" << i;
}

void CamView::play(const QString &file) {
    if (!QFileInfo::exists(file)) {
        qDebug() << "Ops, cannot play file," << file << "doesn't exit!";
        return;
    }
    m_player = new QMediaPlayer;
    m_player->setSource(file);
    m_player->setVideoOutput( this );
    m_player->play();
    qDebug() << "Playing video" << file;
=======
void CamView::switchCamera(){
    m_cam_index++;
    if (m_cam_index == m_available_cameras.length()) m_cam_index = 0;
    setCamera(m_available_cameras[m_cam_index]);
>>>>>>> parent of 1e529ed... Added capture-image function
}