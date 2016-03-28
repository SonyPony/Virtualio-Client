#ifndef VERIFICATIONMESSAGE_H
#define VERIFICATIONMESSAGE_H

#include "message.h"

class VerificationMessage: public Message
{
    private:
        QString m_verificationCode;

    public:
        enum class ContentPart: int {
            VerificationCode
        };

        VerificationMessage();

        virtual QVariantMap extractMessage();
        virtual QByteArray serialize();

        void setVerificationCode(QString verificationCode);
};

#endif // VERIFICATIONMESSAGE_H
