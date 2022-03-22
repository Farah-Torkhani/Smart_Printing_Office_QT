#ifndef GIFANIMATION_H
#define GIFANIMATION_H

#include <QObject>
class QLabel;
class QMovie;

class GifAnimation : public QObject
{
public:
    GifAnimation(QObject *parent = nullptr);
    void startMovie();
    void setFileName(const QString &filename)
    {
        mFilename = filename;
    }
    QString getFilename() const
    {
        return mFilename;
    }
    QLabel *getWidget() const
    {
        return mLabel;
    }
    private:
        QLabel *mLabel;
    QMovie *mMovie;
    QString mFilename;
};

#endif // GIFANIMATION_H
