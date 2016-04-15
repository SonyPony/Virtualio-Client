#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <QQuickItem>

class FileStream : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

    private:
        QString p_source;

    public:
        explicit FileStream(QQuickItem *parent = 0);

        Q_INVOKABLE QString read();
        Q_INVOKABLE bool write(const QString& data);

        /*-----Settery a gettery----*/
        QString source() const;
        void setSource(QString& value);
        /*--------------------------*/

    signals:
        void  sourceChanged();
};

#endif // FILESTREAM_H
