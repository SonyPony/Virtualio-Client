#ifndef INTERACTIVEDIALOG_H
#define INTERACTIVEDIALOG_H

#include <QQuickItem>
#include "composeabledialog.h"

class InteractiveDialog : public ComposeableDialog
{
        Q_OBJECT
    public:
        InteractiveDialog(QQuickItem* parent = 0);

    public Q_SLOTS:
        virtual void createDialogComponents();
};

#endif // INTERACTIVEDIALOG_H
