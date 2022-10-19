#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QActionGroup>
#include <QAudioInput>
#include <QVBoxLayout>
#include "camview.h"

CamView::CamView(QWidget *parent) : QWidget(parent){
    view_finder_ = new QVideoWidget;
    audio_input_.reset(new QAudioInput);
    capture_session_.setAudioInput(audio_input_.data()); //data() is same as get()

    //Camera devices:
    video_devices_group_ = new QActionGroup(this);
    video_devices_group_->setExclusive(true);
    updateCameras();
    connect(&devices_, &QMediaDevices::videoInputsChanged, this, &CamView::updateCameras);
    setCamera(QMediaDevices::defaultVideoInput());   
    available_cameras = QMediaDevices::videoInputs();
    cameras_count = available_cameras.length();

}

void CamView::setCamera(const QCameraDevice &cameraDevice)
{
    camera_.reset(new QCamera(cameraDevice)); //reset from QSharedPointer
    capture_session_.setCamera(camera_.data()); //main functionality

    // connect(m_camera.data(), &QCamera::activeChanged, this, &CamView::updateCameraActive);
    // connect(m_camera.data(), &QCamera::errorOccurred, this, &CamView::displayCameraError);

    if (!media_recorder_) {
        media_recorder_.reset(new QMediaRecorder);
        capture_session_.setRecorder(media_recorder_.data());
        // connect(media_recorder.data(), &QMediaRecorder::recorderStateChanged, this, &CamView::updateRecorderState);
    }

    image_capture_ = new QImageCapture;
    capture_session_.setImageCapture(image_capture_);

    // connect(media_recorder_.data(), &QMediaRecorder::durationChanged, this, &CamView::updateRecordTime);
    // connect(media_recorder_.data(), &QMediaRecorder::errorChanged, this, &CamView::displayRecorderError);

    capture_session_.setVideoOutput(view_finder_);

    // updateCameraActive(camera_->isActive());
    // updateRecorderState(media_recorder_->recorderState());

    // connect(image_capture_, &QImageCapture::readyForCaptureChanged, this, &CamView::readyForCapture);
    // connect(image_capture_, &QImageCapture::imageCaptured, this, &CamView::processCapturedImage);
    // connect(image_capture_, &QImageCapture::imageSaved, this, &CamView::imageSaved);
    // connect(image_capture_, &QImageCapture::errorOccurred, this, &CamView::displayCaptureError);
    // readyForCapture(image_capture_->isReadyForCapture());

    // updateCaptureMode();

    if (camera_->cameraFormat().isNull()) {
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

            camera_->setCameraFormat(bestFormat);
            media_recorder_->setVideoFrameRate(bestFormat.maxFrameRate());
        }
    }

    camera_->start();
}
void CamView::updateCameras(){
    const QList<QCameraDevice> available_cameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &camera_device : available_cameras) {
        QAction *video_device_action = new QAction(camera_device.description(), video_devices_group_);
        video_device_action->setCheckable(true);
        video_device_action->setData(QVariant::fromValue(camera_device));
        if (camera_device == QMediaDevices::defaultVideoInput())
            video_device_action->setChecked(true);
    }
}

void CamView::startCamera(){
    camera_->start();
}

void CamView::stopCamera(){
    camera_->stop();
    qDebug() << "buttonpressed";
}

void CamView::switchCamera(){
    i++;
    if (i == available_cameras.length()) i = 0;
    setCamera(available_cameras[i]);
}