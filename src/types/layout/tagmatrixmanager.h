#ifndef TAGMATRIXCONTROLLER_H
#define TAGMATRIXCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <QPoint>
#include <types/cloneableobject/clonetag.h>

class TagMatrixManager : public QObject
{
        Q_OBJECT
    private:
        QMap<QString, QPointer<CloneTag> > m_tagsInMatrix;

        QString pointToString(QPoint point, ExtentedEnums::Direction tagOrientation) const;

    public:
        TagMatrixManager(QObject *parent = 0);

        QMap<QString, QString> tagsNamesInMatrix() const;
        QMap<QString, QJsonObject> tags() const;
        QStringList tagNamesInRow(int row, ExtentedEnums::Direction tagOrientation) const;

    private Q_SLOTS:
        void reindexTag(QPoint newMatrixPos, CloneTag* tag);

    public Q_SLOTS:
        void registerObject(CloneTag* tag);
        void unregisterObject(CloneTag* tag);
};

#endif // TAGMATRIXCONTROLLER_H
