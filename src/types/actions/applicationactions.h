#ifndef APPLICATIONACTIONS_H
#define APPLICATIONACTIONS_H

#include <QObject>

class ApplicationActions : public QObject
{
        Q_OBJECT
    public:
        explicit ApplicationActions(QObject *parent = 0);

    signals:

    public slots:
};

#endif // APPLICATIONACTIONS_H
