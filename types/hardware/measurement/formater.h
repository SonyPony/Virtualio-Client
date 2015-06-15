#ifndef FORMATER_H
#define FORMATER_H

#include <QQuickItem>

class Formater : public QQuickItem
{
    Q_OBJECT

    public:
        Formater();
        ~Formater();

        QStringList Exponents();

        Q_INVOKABLE QStringList formatCapacitance(QString raw);
        Q_INVOKABLE QStringList splitData(QString raw);
};

#endif // FORMATER_H
