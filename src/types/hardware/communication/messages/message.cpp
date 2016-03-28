#include "message.h"
#include <QDebug>
#include "bitarray.h"
#include "binaryutils.h"

void Message::setType(Message::Type type)
{
    m_type = (uint8_t)type;
}

int Message::extractNumberFromContent(int startIndex, int length)
{
    return BinaryUtils::extractNumberFromBits(startIndex, length, m_content);
}

int Message::addNumberToContent(int number, int8_t length)
{
    const int startPos = m_content.size();
    m_content.resize(m_content.size() + length);
    m_content |= BinaryUtils::toBitArray(number, length) >> (m_content.size() - length);
    this->generateHeader();

    return startPos;
}

int Message::addCharToContent(char character)
{
    return this->addNumberToContent(character, 8);
}

void Message::setContent(QByteArray rawBytes)
{
    m_content = BinaryUtils::toBitArray(rawBytes);
    qDebug() << "content set";
    //this->generateHeader();
}

QString Message::extractStringFromContent(int startIndex, uint8_t charsCount)
{
    return BinaryUtils::extractStringFromBits(startIndex, charsCount, m_content);
}

BitArray Message::generateHeader()
{
    BitArray header(15, false);
    // contains message type and length of content
    // message type reserves 5 bits
    // content length reserves 10 bits

    const int messageType = m_type;
    const int contentLength = m_content.size();

    header |= BinaryUtils::toBitArray(messageType, 5);
    header |= BinaryUtils::toBitArray(contentLength, 10) >> 5;

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

