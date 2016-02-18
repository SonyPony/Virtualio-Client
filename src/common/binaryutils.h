#ifndef BINARYUTILS_H
#define BINARYUTILS_H

#include <QString>
#include <QByteArray>
#include <QBitArray>

namespace BinaryUtils
{
    QByteArray toByteArray(QBitArray bits);
    QBitArray toBitArray(QByteArray bytes);
    QBitArray toBitArray(int number, int8_t length);
    QString extractStringFromBits(int startBitIndex, uint8_t charsCount, const QBitArray& bits);
    int extractNumberFromBits(int startBitIndex, int bitLength, const QBitArray& bits);
}

QBitArray operator>>(const QBitArray& ba, int number);

#endif // BINARYUTILS_H
