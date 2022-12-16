#include "display.h"
#include "player.h"
#include <QWidget>

Display::Display(QWidget * parent) {
}

Display::setPlayer(Player * this_player){
    // triggered by "swap cameras" button
    _player = this_player;
}

Display::callPlayer(){
    _player->_playable->play();
    _player->_playable->setVideoOutput(this);
}