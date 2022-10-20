#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QActionGroup>
#include <QAudioInput>
#include <QVBoxLayout>
#include "camview.h"

CamView::CamView(int idx, QWidget *parent) : QWidget(parent){
    m_view_finder = new QVideoWidget;
    m_audio_input.reset(new QAudioInput);
    m_capture_session.setAudioInput(m_audio_input.data()); //data() is same as get()
    m_cam_index = idx;

    //Camera devices:
    m_video_devices_group = new QActionGroup(this);
    m_video_devices_group->setExclusive(true);
    updateCameras();
    connect(&m_devices, &QMediaDevices::videoInputsChanged, this, &CamView::updateCameras);
    m_available_cameras = QMediaDevices::videoInputs();
    setCamera(m_available_cameras[m_cam_index]);   
    m_cameras_count = m_available_cameras.length();

}

void CamView::setCamera(const QCameraDevice &cameraDevice)
{
    m_camera.reset(new QCamera(cameraDevice)); //reset from QSharedPointer
    m_capture_session.setCamera(m_camera.data()); //main functionality

    // connect(m_camera.data(), &QCamera::activeChanged, this, &CamView::updateCameraActive);
    // connect(m_camera.data(), &QCamera::errorOccurred, this, &CamView::displayCameraError);

    if (!m_media_recorder) {
        m_media_recorder.reset(new QMediaRecorder);
        m_capture_session.setRecorder(m_media_recorder.data());
        // connect(media_recorder.data(), &QMediaRecorder::recorderStateChanged, this, &CamView::updateRecorderState);
    }

    m_image_capture = new QImageCapture;
    m_capture_session.setImageCapture(m_image_capture);

    // connect(m_media_recorder.data(), &QMediaRecorder::durationChanged, this, &CamView::updateRecordTime);
    // connect(m_media_recorder.data(), &QMediaRecorder::errorChanged, this, &CamView::displayRecorderError);

    m_capture_session.setVideoOutput(m_view_finder);

    // updateCameraActive(m_camera->isActive());
    // updateRecorderState(media_recorder_->recorderState());

    // connect(image_capture_, &QImageCapture::readyForCaptureChanged, this, &CamView::readyForCapture);
    // connect(image_capture_, &QImageCapture::imageCaptured, this, &CamView::processCapturedImage);
    // connect(image_capture_, &QImageCapture::imageSaved, this, &CamView::imageSaved);
    // connect(image_capture_, &QImageCapture::errorOccurred, this, &CamView::displayCaptureError);
    // readyForCapture(image_capture_->isReadyForCapture());

    // updateCaptureMode();

    if (m_camera->cameraFormat().isNull()) {
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
    const QList<QCameraDevice> available_cameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &camera_device : available_cameras) {
        QAction *video_device_action = new QAction(camera_device.description(), m_video_devices_group);
        video_device_action->setCheckable(true);
        video_device_action->setData(QVariant::fromValue(camera_device));
        if (camera_device == QMediaDevices::defaultVideoInput())
            video_device_action->setChecked(true);
    }
}

void CamView::startCamera(){
    m_camera->start();
}

void CamView::stopCamera(){
    m_camera->stop();
    qDebug() << "buttonpressed";
}

void CamView::switchCamera(){
    m_cam_index++;
    if (m_cam_index == m_available_cameras.length()) m_cam_index = 0;
    setCamera(m_available_cameras[m_cam_index]);
}