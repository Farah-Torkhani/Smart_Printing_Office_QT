#include "duscene.h"
#include "gifanimation.h"
#include <QLabel>

DuScene::DuScene(QObject *parent)
     :QGraphicsScene(parent)
{
    mGifAnimation = new GifAnimation(this);
    mGifAnimation->setFileName("C:/Users/ALI/Desktop/projet c++/gif.gif");
    mGifAnimation->startMovie();
    addWidget(mGifAnimation->getWidget());
}
