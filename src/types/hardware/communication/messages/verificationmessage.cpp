#include "verificationmessage.h"

VerificationMessage::VerificationMessage(): Message()
{
    this->setType(Message::Type::Verification);
}

QVariantMap VerificationMessage::extractMessage() const
{

}

QByteArray VerificationMessage::serialize() const
{

}

void VerificationMessage::setVerificationCode(QString verificationCode)
{
    m_verificationCode = verificationCode;
}

