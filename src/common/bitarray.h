#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <QString>

class BitArray
{
    public:
        unsigned char m_bytesSize;
        std::size_t m_bitsSize;
        unsigned char* m_bytes;

    public:
        BitArray();
        BitArray(std::size_t size, bool value = false);
        BitArray(const BitArray& other);
        ~BitArray();

        void setBit(std::size_t index);
        void setBitState(std::size_t index, bool value);
        void clearBit(std::size_t index);
        void resize(std::size_t size);
        void clear();
        std::size_t size() const;

        BitArray& operator=(const BitArray& other);
        BitArray& operator|=(const BitArray& other);
        bool operator!=(const BitArray& other) const;
        bool operator==(const BitArray& other) const;
        const bool operator[](std::size_t index) const;

        QString toStr() const;
};

BitArray operator>>(const BitArray& ba, std::size_t numberOfShifts);
BitArray operator<<(const BitArray& ba, std::size_t numberOfShifts);

#endif // BITARRAY_H
