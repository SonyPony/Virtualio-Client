#include "filestream.h"
#include <QFile>
#include <QStandardPaths>
#include <QDir>

FileStream::FileStream(QQuickItem *parent): QQuickItem(parent) {}

QString FileStream::read() { 
    QFile file(p_source);
    QString content;

    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        content = in.readLine();

        file.close();
        return content;
    }

    else
        return "";
}

bool FileStream::write(const QString &data) {
    QFile file(p_source);

    if(!file.open(QIODevice::WriteOnly))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}

QString FileStream::source() const {
    return p_source;
}

void FileStream::setSource(QString &value) {
    #ifdef Q_OS_IOS
    QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation).value(0);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    if (!path.isEmpty() && !path.endsWith("/"))
        path += "/";
        value = path + value;
    #endif

    if(p_source != value) {
        p_source = value;
         emit sourceChanged();
    }
}
