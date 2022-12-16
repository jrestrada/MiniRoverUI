#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtMultimediaWidgets/QVideoWidget>
#include "player.h"

class Player;

class Display : public QVideoWidget{
    Q_OBJECT
    public:
        explicit Display(QWidget * parent = nullptr);
        void setPlayer(Player * this_player);
        void callPlay();
    private:
        Player * _player;
}

#endif // DISPLAY_H