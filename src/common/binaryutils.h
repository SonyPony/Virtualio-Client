#ifndef BINARYUTILS_H
#define BINARYUTILS_H

#include <QString>
#include <QByteArray>
#include <QBitArray>

namespace BinaryUtils
{
    QByteArray toByteArray(QBitArray bits);
    QBitArray toBitArray(QByteArray bytes);
    QString extractStringFromBits(int startBitIndex, uint8_t charsCount, const QBitArray& bits);
    int extractNumberFromBits(int startBitIndex, int bitLength, const QBitArray& bits);
}

#endif // BINARYUTILS_H
