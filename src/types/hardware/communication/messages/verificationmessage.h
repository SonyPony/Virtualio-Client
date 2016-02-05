#ifndef VERIFICATIONMESSAGE_H
#define VERIFICATIONMESSAGE_H

#include "message.h"

class VerificationMessage: public Message
{
    private:
        QString m_verificationCode;

    public:
        VerificationMessage();

        virtual QVariantMap extractMessage() const;
        virtual QByteArray serialize() const;

        void setVerificationCode(QString verificationCode);
};

#endif // VERIFICATIONMESSAGE_H
