#include "formater.h"
#include <QRegularExpression>

Formater::Formater()
{

}

Formater::~Formater()
{

}

QStringList Formater::splitData(QString raw) {
    return raw.split(":");
}

QStringList Formater::formatCapacitance(QString raw)
{
    //split into identifier and number
    QStringList data = raw.split(":");

    QStringList postfixes;
    postfixes << ""
              << "m"
              << "u"
              << "n"
              << "p";

    if(data.at(0) == "Capacitance") {
        double result = data.at(1).toDouble();
        int exponent = 0;

        while(result < 1) {
            result *= 1000;
            exponent++;
        }

        data[1] = QString::number(result, 'f', 2)
                .append(postfixes.at(exponent))
                .append("F");
    }

    return data;
    //raw = QRegularExpression("Capacitance:\\d\.\\d*").match(raw).captured(0);
    //get only number
    //qDebug() << "dd";
    //raw = QRegularExpression("\\d\.\\d*").match(raw);


}

