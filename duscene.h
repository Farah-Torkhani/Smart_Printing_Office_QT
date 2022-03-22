#ifndef DUSCENE_H
#define DUSCENE_H

#include <QGraphicsScene>

class GifAnimation;

class DuScene : public QGraphicsScene
{
public:
    DuScene(QObject *parent = nullptr );
private:
    GifAnimation *mGifAnimation;
};

#endif // DUSCENE_H
