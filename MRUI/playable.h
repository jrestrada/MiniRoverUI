#ifndef PLAYABLE_H
#define PLAYABLE_H

#include <QString>
#include <QObject>

class Player;

class IPlayable{
    public:
        explicit IPlayable();
        ~IPlayable();
        virtual void play();
        // virtual void SetVideoOutput(QObject * display);
    private:
};
#endif // PLAYABLE_H