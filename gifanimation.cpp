#include "gifanimation.h"
#include <QLabel>
#include <QMovie>


GifAnimation::GifAnimation(QObject *parent)
     :QObject(parent)
{
    mLabel = new QLabel(static_cast<QWidget *>(parent->parent()->parent()));
    mMovie = new QMovie(this);


}

void GifAnimation::startMovie()
{
    mMovie->setFileName(mFilename);
    mMovie->start();
    mLabel->setMovie(mMovie);
}
