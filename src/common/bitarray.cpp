#include "bitarray.h"
#include <QDebug>

BitArray::BitArray()
{
    m_bytesSize = 0;
    m_bitsSize = 0;
    m_bytes = NULL;
}

BitArray::BitArray(std::size_t size, bool value)
{
    m_bytes = NULL;
    this->resize(size);

    unsigned char mask = (value) ?0xFF :0;

    for(unsigned char i = 0; i < m_bytesSize; i++)
        m_bytes[i] = mask;
}

BitArray::BitArray(const BitArray &other)
{
    m_bitsSize = other.m_bitsSize;
    m_bytesSize = other.m_bytesSize;
    delete[] m_bytes;
    m_bytes = new unsigned char[m_bytesSize];
    memcpy(m_bytes, other.m_bytes, m_bytesSize * sizeof(unsigned char));
}

BitArray::~BitArray()
{
    delete[] m_bytes;
}

void BitArray::setBit(std::size_t index)
{
    m_bytes[index / 8] |= (1 << (7 - index % 8));
}

void BitArray::setBitState(std::size_t index, bool value)
{
    if(value)
        this->setBit(index);
    else
        this->clearBit(index);
}

void BitArray::clearBit(std::size_t index)
{
    m_bytes[index / 8] &= ~(1 << (7 - index % 8));
}

void BitArray::resize(std::size_t size)
{
    unsigned int bytesSize = ceil(size / 8.);
    unsigned char* resizedBytes = new unsigned char[bytesSize];

    if(m_bytes == NULL) {
        m_bytes = new unsigned char[bytesSize];
        m_bitsSize = size;
        m_bytesSize = bytesSize;

        for(unsigned char i = 0; i < bytesSize; i++)
            m_bytes[i] = 0;

        return;
    }

    memcpy(resizedBytes, m_bytes, m_bytesSize * sizeof(unsigned char));

    delete[] m_bytes;
    m_bytes = resizedBytes;

    for(unsigned char i = m_bytesSize; i < bytesSize; i++)
        m_bytes[i] = 0;

    m_bitsSize = size;
    m_bytesSize = bytesSize;
}

void BitArray::clear()
{
    delete[] m_bytes;
    m_bytes = NULL;
    m_bytesSize = 0;
    m_bitsSize = 0;
}

std::size_t BitArray::size() const
{
    return m_bitsSize;
}

BitArray &BitArray::operator=(const BitArray &other)
{
    this->resize(other.size());
    memcpy(m_bytes, other.m_bytes, m_bytesSize);

    return *this;
}

BitArray& BitArray::operator|=(const BitArray &other)
{
    this->resize(std::max(this->size(), other.size()));

    for(unsigned char i = 0; i < m_bytesSize; i++) {
        m_bytes[i] |= other.m_bytes[i];
    }

    return *this;
}

bool BitArray::operator!=(const BitArray &other) const
{
    return !this->operator ==(other);
}

bool BitArray::operator==(const BitArray &other) const
{
    if(m_bitsSize != other.m_bitsSize)
        return false;

    for(unsigned char i = 0; i < m_bytesSize; i++) {
        if(m_bytes[i] != other.m_bytes[i])
            return false;
    }
    return true;
}

const bool BitArray::operator[](std::size_t index) const
{
    Q_ASSERT(index < m_bitsSize);
    const unsigned char shift = 8 - (index % 8) - 1;
    return ((m_bytes[index / 8]) & (1 << shift)) >> shift;
}

BitArray operator>>(const BitArray &ba, std::size_t numberOfShifts)
{
    BitArray result(ba.size() + numberOfShifts, false);

    for(unsigned int i = 0; i < ba.size(); i++)
        result.setBitState(i + numberOfShifts, ba[i]);

    return result;
}

BitArray operator<<(const BitArray &ba, std::size_t numberOfShifts)
{
    BitArray result(ba.size(), false);

    result = ba;
    result.resize(ba.size() + numberOfShifts);

    return result;
}


QString BitArray::toStr() const
{
    QString result;

    for(unsigned int i = 0; i < this->size(); i++) {
        const unsigned char shift = 8 - (i % 8) - 1;
        if(i % 8 == 0)
            result.append(" ");
        bool value = ((m_bytes[i / 8]) & (1 << shift)) >> shift;
        result.append(QString::number(value));
    }
    return result;
}
