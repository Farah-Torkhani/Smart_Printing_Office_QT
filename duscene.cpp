#include "duscene.h"
#include "gifanimation.h"
#include <QLabel>

DuScene::DuScene(QObject *parent)
     :QGraphicsScene(parent)
{
    mGifAnimation = new GifAnimation(this);
    mGifAnimation->setFileName(":/Resources/client_img/gif.gif");
    mGifAnimation->startMovie();
    addWidget(mGifAnimation->getWidget());
}
