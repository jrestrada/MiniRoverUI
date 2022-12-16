#ifndef PLAYER_H
#define PLAYER_H

#include "playable.h"

#include <QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>

class QCamera;
class QCameraImageCapture;

class Player : public QVideoWidget {
    Q_OBJECT
public:
    explicit Player(IPlayable * original_playable);
    void callPlay();

private:
    IPlayable *_playable;
};

#endif // PLAYER_H

