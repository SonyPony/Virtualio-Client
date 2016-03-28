#ifndef TAGOPTIONSDIALOG_H
#define TAGOPTIONSDIALOG_H

#include <QQuickItem>
#include "composeabledialog.h"

class TagOptionsDialog : public ComposeableDialog
{
        Q_OBJECT

    public:
        TagOptionsDialog(QQuickItem* parent = 0);

    public Q_SLOTS:
        virtual void createDialogComponents();

    Q_SIGNALS:
};

#endif // TAGOPTIONSDIALOG_H
