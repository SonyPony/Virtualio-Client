#include "tagoptionsdialog.h"

TagOptionsDialog::TagOptionsDialog(QQuickItem *parent): ComposeableDialog(parent)
{
    connect(this, &ComposeableDialog::modeChanged, [this](QString mode) {
        const QMap<QString, QString> longNames = m_settingsProvider->extractSettingsLongNames();

        if(mode == "None") {
            m_titleColor = QColor("lightGray");
            Q_EMIT this->titleColorChanged(m_titleColor);
        }

        if(longNames.keys().contains(mode))
            m_longName = longNames[mode];
        else
            m_longName = mode;
    });
}

void TagOptionsDialog::createDialogComponents()
{
    this->createDialogComponentsFromSettings("tagOptions");
}

