#ifndef BINARYUTILS_H
#define BINARYUTILS_H

#include <QString>
#include <QByteArray>
#include "bitarray.h"

namespace BinaryUtils
{
    QByteArray toByteArray(BitArray bits);
    BitArray toBitArray(QByteArray bytes);
    BitArray toBitArray(int number, int8_t length);
    QString extractStringFromBits(int startBitIndex, uint8_t charsCount, const BitArray& bits);
    int extractNumberFromBits(int startBitIndex, int bitLength, const BitArray& bits);
}

#endif // BINARYUTILS_H
