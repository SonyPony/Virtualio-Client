#include "message.h"
#include <QDebug>
#include <QBitArray>

void Message::setType(Message::Type type)
{
    m_type = (uint8_t)type;
}

int Message::extractNumberFromBytes(int startIndex, int length)
{
    int wantedBits = 0;

    for(int i = 0; i < length; i++) {
        wantedBits |= m_content[startIndex + i];
        if(i < length - 1)
            wantedBits <<= 1;
    }

    return wantedBits;
}

int Message::addNumberToContent(int number, int length)
{
    const int startPos = m_content.size();

    m_content.resize(m_content.size() + length);

    for(int i = 0; i < length; i++) {
        m_content[startPos + length - i - 1] = number % 2;
        number >>= 1;
    }

    this->generateHeader();

    return startPos;
}

int Message::addCharToContent(char character)
{
    return this->addNumberToContent(character, 8);
}

void Message::setContent(QByteArray rawBytes)
{
    m_content.resize(rawBytes.length() * 8);

    for(int i = 0; i < rawBytes.length(); i++) {
        for(uint8_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            m_content[i * 8 + 7 - bitIndex] = rawBytes.at(i) % 2;
            rawBytes[i] = rawBytes[i] >> 1;
        }
    }

    this->generateHeader();
}

QString Message::extractStringFromBytes(int startIndex, uint8_t charsCount)
{
    Q_ASSERT(startIndex + charsCount - 1 >= 0);
    Q_ASSERT(startIndex + charsCount * 8 - 1 < m_content.size());

    QString result;
    char byte;

    for(int i = 0; i < charsCount; i++) {
        byte = 0;

        for(uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
            byte |= m_content[startIndex + i * 8 + bitIndex] << (7 - bitIndex);
        result += byte;
    }

    return result;
}

QBitArray Message::generateHeader()
{
    QBitArray header(15, false);
    // contains message type and length of content
    // message type reserves 5 bits
    // content length reserves 10 bits

    int messageType = m_type;

    for(int i = 0; i < 5; i++) {
        header[4 - i] = messageType % 2;
        messageType >>= 1;
    }

    constexpr int startPos = 5;
    int contentLength = m_content.size();

    for(int i = 0; i < 10; i++) {
        header[startPos + 9 - i] = contentLength % 2;
        contentLength >>= 1;
    }

    if(m_header != header)
        m_header = header;

    return m_header;
}

Message::Message()
{
}

uint8_t Message::type() const
{
    return m_type;
}

