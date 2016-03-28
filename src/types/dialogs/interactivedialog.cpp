#include "interactivedialog.h"

InteractiveDialog::InteractiveDialog(QQuickItem *parent): ComposeableDialog(parent)
{
    m_longName = tr("Interactive");
}

void InteractiveDialog::createDialogComponents()
{
    this->createDialogComponentsFromSettings("interactiveControls");
}

