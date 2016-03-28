#include "binaryutils.h"
#include <QDebug>

QByteArray BinaryUtils::toByteArray(BitArray bits)
{
    QByteArray bytes;
    char byte = 0;
    int8_t bytePos = 0;

    for(uint i = 0; i < bits.size(); i++) {
        byte |= bits[i] << (7 - i % 8);

        if(++bytePos == 8 || i == bits.size() - 1) {
            bytes.append(byte);
            bytePos = 0;
            byte = 0;
        }
    }

    return bytes;
}

BitArray BinaryUtils::toBitArray(QByteArray bytes)
{
    BitArray bits(bytes.length() * 8, false);

    for(int i = 0; i < bytes.length(); i++) {
        for(uint8_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            bits.setBitState(i * 8 + 7 - bitIndex, bytes.at(i) % 2);
            bytes[i] = bytes[i] >> 1;
        }
    }

    return bits;
}

QString BinaryUtils::extractStringFromBits(int startBitIndex, uint8_t charsCount, const BitArray &bits)
{
    Q_ASSERT(startBitIndex + charsCount - 1 >= 0);
    Q_ASSERT(startBitIndex + charsCount * 8 - 1 < bits.size());

    QString result;
    char byte;

    for(int i = 0; i < charsCount; i++) {
        byte = 0;

        for(uint8_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            byte |= bits[startBitIndex + i * 8 + bitIndex] << (7 - bitIndex);
        }
        result += byte;
    }

    return result;
}

int BinaryUtils::extractNumberFromBits(int startBitIndex, int bitLength, const BitArray &bits)
{
    int wantedBits = 0;

    for(int i = 0; i < bitLength; i++) {
        wantedBits |= bits[startBitIndex + i];
        if(i < bitLength - 1)
            wantedBits <<= 1;
    }

    return wantedBits;
}

BitArray BinaryUtils::toBitArray(int number, int8_t length)
{
    Q_ASSERT(length > 0);
    BitArray result(length, false);

    for(int i = 0; i < length; i++) {
        result.setBitState(length - i - 1, number % 2);
        number >>= 1;
    }

    return result;
}
