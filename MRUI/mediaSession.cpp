#include "media.h"
#include <QString>

void Media::Media(){
}
void Media::Play() override{
    QString file ="/home/josue/code/MediaPlayer/sample_1280x720.mp4"
    if (!QFileInfo::exists(file)) {
        qDebug() << "Ops, cannot play file," << file << "doesn't exit!";
        return;
    }
    m_player->setSource(file);
}