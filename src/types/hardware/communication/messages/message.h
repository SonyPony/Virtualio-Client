#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <QBitArray>
#include <QByteArray>
#include <QVariantMap>

class Message
{
    public:
        enum class Type: uint8_t {
            Verification,
            PinsInit,
            Reading,
            Action
        };

    protected:
        uint8_t m_type;
        QBitArray m_content;
        QBitArray m_header;

        void setType(Message::Type type);
        // length -> number of bits
        // first bit on the left is [0]
        int extractNumberFromBytes(int startIndex, int length);

        // return start index of number;
        int addNumberToContent(int number, int length);
        int addCharToContent(char character);
        void setContent(QByteArray rawBytes);

        QString extractStringFromBytes(int startIndex, uint8_t charsCount);
        QBitArray generateHeader();

        virtual QVariantMap desrialize(QByteArray rawData) const = 0;

    public:
        Message();

        virtual QByteArray serialize() const = 0;
        virtual QVariantMap extractMessage() const = 0;

        uint8_t type() const;
};

#endif // MESSAGE_H
