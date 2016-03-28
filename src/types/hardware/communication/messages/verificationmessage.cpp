#include "verificationmessage.h"
#include "binaryutils.h"

VerificationMessage::VerificationMessage(): Message()
{
    this->setType(Message::Type::Verification);
}

QVariantMap VerificationMessage::extractMessage()
{
    QVariantMap parsedContent;
    parsedContent["verificationCode"] = this->extractStringFromContent(0, m_content.size() / 8);

    m_verificationCode = parsedContent["vericationCode"].toString();

    return parsedContent;
}

QByteArray VerificationMessage::serialize()
{
    BitArray serializedBits(s_headerLength + m_content.size());
    this->setContent(m_verificationCode.toLocal8Bit());

    serializedBits = m_header;
    serializedBits |= m_content >> s_headerLength;

    return BinaryUtils::toByteArray(serializedBits);
}

void VerificationMessage::setVerificationCode(QString verificationCode)
{
    m_verificationCode = verificationCode;
}

