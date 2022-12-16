#ifndef MEDIASESSION_H
#define MEDIASESSION_H

#include "playable.h"
#include <QMediaPlayer>
#include <QString>

class Player;

class Media: public IPlayable, public QMediaPlayer{
    public:
        explicit Media();
        ~Media();
        void Play() override;
    private:
        QMediaPlayer *m_player;
};
#endif // MEDIASESSION_H