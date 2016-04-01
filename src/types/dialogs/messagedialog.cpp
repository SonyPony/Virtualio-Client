#include "messagedialog.h"

void MessageDialog::keyPressEvent(QKeyEvent *e)
{
    if(!this->opacity())
        return;

    const int key = e->key();
    if(key == Qt::Key_Return || key == Qt::Key_Escape)
        this->hide();
}

MessageDialog::MessageDialog(QQuickItem *parent): ModalDialog(parent)
{
    m_title = "";
    m_titleColor = QColor("black");

    m_buttonFont = QFont();
    m_buttonColor = QColor("white");

    m_button = new StyledButton(this);
    m_button->setParentItem(this->container());
    m_button->setText(tr("Close"));
    this->applyButtonColor(m_buttonColor);
    m_button->setSize(QSizeF(120, 30));

    this->setDialogBaseSize(QSize(this->width(), m_dialogBaseSize.height()));

    connect(this, &MessageDialog::buttonFontChanged, this, &MessageDialog::applyButtonFont);
    connect(this, &MessageDialog::buttonColorChanged, this, &MessageDialog::applyButtonColor);
    connect(m_button, &StyledButton::clicked, this, &MessageDialog::hide);
    connect(this, &MessageDialog::dialogBaseSizeChanged, this, &MessageDialog::repositionButton);
    connect(this, &MessageDialog::titleChanged, this, &QQuickItem::update);
    connect(this, &MessageDialog::titleColorChanged, this, &QQuickItem::update);
    connect(this, &MessageDialog::titleFontChanged, this, &QQuickItem::update);
    connect(this, &MessageDialog::messageChanged, this, &QQuickItem::update);
    connect(this, &MessageDialog::messageFontChanged, this, &QQuickItem::update);
    connect(this, &MessageDialog::widthChanged, [this]() {
        this->setDialogBaseSize(QSize(this->width(), m_dialogBaseSize.height()));
        this->repositionButton();
    });

    this->setOpacity(0);
}

void MessageDialog::paint(QPainter *painter)
{
    ModalDialog::paint(painter);

    const QFontMetricsF fmTitle(m_titleFont);

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // draw title
    painter->setFont(m_titleFont);
    painter->setPen(m_titleColor);
    painter->setBrush(m_titleColor);

    QPointF titlePos = container()->position();
    titlePos.ry() += fmTitle.height();
    titlePos.rx() += 2. * m_button->width();

    painter->drawText(titlePos, m_title);

    // draw message
    QPointF msgPos = titlePos;
    msgPos.ry() += QFontMetricsF(m_messageFont).height() + 5;
    painter->setBrush(m_buttonColor);
    painter->setPen(m_buttonColor);
    painter->setFont(m_messageFont);
    painter->drawText(msgPos, m_message);
}

QColor MessageDialog::buttonColor() const
{
    return m_buttonColor;
}

QFont MessageDialog::buttonFont() const
{
    return m_buttonFont;
}

QFont MessageDialog::titleFont() const
{
    return m_titleFont;
}

QString MessageDialog::title() const
{
    return m_title;
}

QColor MessageDialog::titleColor() const
{
    return m_titleColor;
}

QString MessageDialog::message() const
{
    return m_message;
}

QFont MessageDialog::messageFont() const
{
    return m_messageFont;
}

void MessageDialog::repositionButton()
{
    const double buttonHeight = m_button->height();
    const double buttonWidth = m_button->width();
    m_button->setPosition(QPointF(
        m_dialogBaseSize.width() - buttonHeight - 2. * buttonWidth,
        m_dialogBaseSize.height() - 2. * buttonHeight
    ));
}

void MessageDialog::applyButtonFont(QFont font)
{
    m_button->setFont(font);
}

void MessageDialog::applyButtonColor(QColor color)
{
    m_button->setTextColor(color);
    m_button->setBorderColor(color);
    m_button->setColor(color);
}

void MessageDialog::setButtonColor(QColor buttonColor)
{
    if (m_buttonColor == buttonColor)
        return;

    m_buttonColor = buttonColor;
    emit buttonColorChanged(buttonColor);
}

void MessageDialog::setButtonFont(QFont buttonFont)
{
    if (m_buttonFont == buttonFont)
        return;

    m_buttonFont = buttonFont;
    emit buttonFontChanged(buttonFont);
}

void MessageDialog::setTitleFont(QFont titleFont)
{
    if (m_titleFont == titleFont)
        return;

    m_titleFont = titleFont;
    emit titleFontChanged(titleFont);
}

void MessageDialog::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(title);
}

void MessageDialog::setTitleColor(QColor titleColor)
{
    if (m_titleColor == titleColor)
        return;

    m_titleColor = titleColor;
    emit titleColorChanged(titleColor);
}

void MessageDialog::setMessage(QString message)
{
    if (m_message == message)
        return;

    m_message = message;
    emit messageChanged(message);
}

void MessageDialog::setMessageFont(QFont messageFont)
{
    if (m_messageFont == messageFont)
        return;

    m_messageFont = messageFont;
    emit messageFontChanged(messageFont);
}

