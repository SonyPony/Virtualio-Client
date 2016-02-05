#ifndef MESSAGETESTS_H
#define MESSAGETESTS_H

#include <QObject>
#include <QTest>
#include "../../types/hardware/communication/messages/message.h"

namespace Tests {
    class TMessage: public Message
    {
        friend class MessageTests;

        protected:
            virtual QVariantMap desrialize(QByteArray rawData) const {}

        public:
            virtual QByteArray serialize() const {}
            virtual QVariantMap extractMessage() const {}
    };

    class MessageTests : public QObject
    {
            Q_OBJECT
        private Q_SLOTS:
            void testExtractingNumber();
            void testExtractingString();
            void testAddingParam();
            void testGeneratingHeader();
    };
}

#endif // MESSAGETESTS_H
