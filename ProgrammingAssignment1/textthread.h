#ifndef TEXTTHREAD_H
#define TEXTTHREAD_H

#include <QThread>

class TextThread : public QThread
{
    Q_OBJECT
public:
    TextThread(QObject *parent=0): QThread(parent) {}
signals:
    void signalOutput(const QString &result);
};

#endif // TEXTTHREAD_H
