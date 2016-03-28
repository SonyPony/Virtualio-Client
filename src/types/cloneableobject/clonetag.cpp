#include "clonetag.h"
#include <QVariantMap>
#include <qmath.h>
#include "extentedmath.h"
#include "fraction.h"
#include "dropableobject.h"

CloneTag::CloneTag(int index, TagAppearance *appearance, QQuickItem *parent): CloneObject(index, parent)
{
    m_currentDirection = appearance->currentDirection();
    m_selected = false;

    setAcceptedMouseButtons(Qt::AllButtons);
    // parent is cloneable tag
    setParentItem(parent);
    // need space for pinview
    setWidth(parent->width() + parent->height());
    setHeight(parent->height());

    m_tagPinView = new TagPinView(this);
    m_tagPinView->setColor("#303031");
    m_tagPinView->setTextColor("white");
    m_tagPinView->setSize(QSize(height(), height()));

    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_opacityAnimation->setDuration(250);

    m_pinViewMoveAnimation = new QPropertyAnimation(m_tagPinView, "x", this);
    m_pinViewMoveAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_pinViewMoveAnimation->setDuration(250);

    m_focusHeartBeat = new QPropertyAnimation(this, "focusOpacity", this);
    m_focusHeartBeat->setKeyValueAt(0, 0);
    m_focusHeartBeat->setKeyValueAt(0.5, 1);
    m_focusHeartBeat->setKeyValueAt(1, 0);

    m_focusHeartBeat->setDuration(2000);
    m_focusHeartBeat->setLoopCount(-1);

    m_tagAppearance = new TagAppearance(appearance, this);
    m_tagName = m_tagAppearance->name();

    this->repositionBody(m_tagAppearance->currentDirection());
    this->showPinView();

    //need just height to resize
    connect(parent, SIGNAL(heightChanged()), this, SLOT(resize()));
    connect(m_tagAppearance, SIGNAL(requestUpdate()), this, SLOT(update()));
    connect(this, SIGNAL(currentPinNumberChanged(int)), this, SLOT(update()));
    connect(m_tagPinView, SIGNAL(xChanged()), this, SLOT(update()));
    connect(this, &CloneTag::focusOpacityChanged, this, &QQuickItem::update);
    connect(this, SIGNAL(catched()), this, SLOT(showPinView()));
    connect(this, SIGNAL(directionChanged()), this, SLOT(repostionPinView()));
    connect(this, &DropableObject::dropped, [this]() {
        if(!m_selected)
            this->hidePinView();
    });
    connect(this, &CloneTag::selectedChanged, [this](bool selected) {
        if(selected) {
            this->showPinView();
            m_focusHeartBeat->start();
        }
        else {
            this->hidePinView();
            m_focusHeartBeat->stop();
        }
    });
    connect(this, &DropableObject::matrixPositionChanged, [this](QPoint pos) {
        emit matrixPositionChanged(pos, this);
    });

    connect(this, &QQuickItem::heightChanged, [this]() {
        if(m_currentDirection == ExtentedEnums::Right)  // 0 means showed, height means hidden
            this->m_tagPinView->setX(this->height());
        else    // because pinview has size(height, height), so we will shift it to the left by "height", so it is hidden
            this->m_tagPinView->setX(this->width() - 2 * this->height());

        this->m_tagPinView->setWidth(this->height());
        this->m_tagPinView->setHeight(this->height());
    });
}

void CloneTag::paint(QPainter *painter)
{
    m_tagPinView->paintPinView(painter);
    m_tagAppearance->paintTag(painter);

    painter->setBrush(QColor("transparent"));
    painter->setPen(QPen(m_tagAppearance->focusColor(), 5));
    QPolygon shape = m_tagAppearance->shape();

    if(m_currentDirection == ExtentedEnums::Right)
        shape.translate(this->height(), 0);

    if(m_selected) {
        painter->setOpacity(m_focusOpacity);
        painter->drawPolyline(shape);
    }
}

QVariantMap CloneTag::options() const
{
    return m_options;
}

TagAppearance *CloneTag::appearance() const
{
    return m_tagAppearance;
}

bool CloneTag::selected() const
{
    return m_selected;
}

double CloneTag::focusOpacity() const
{
    return m_focusOpacity;
}

int CloneTag::currentPinNumber() const
{
    return m_currentPinNumber;
}

ExtentedEnums::Direction CloneTag::currentDirection() const
{
    return m_currentDirection;
}

QString CloneTag::name() const
{
    return m_tagName;
}

QVariantMap CloneTag::controlState() const
{
    return m_controlState;
}

void CloneTag::repostionPinView()
{
    m_pinViewMoveAnimation->setStartValue(m_tagPinView->x());
    m_pinViewMoveAnimation->stop();

    if(m_currentDirection == ExtentedEnums::Left) {
        m_pinViewMoveAnimation->setStartValue(this->height());
        m_pinViewMoveAnimation->setEndValue(this->width() - this->height() - 1);
    }
    else {
        m_pinViewMoveAnimation->setStartValue(this->width() - 2. * this->height() - 1);
        m_pinViewMoveAnimation->setEndValue(0);
    }

    m_pinViewMoveAnimation->start();
}

void CloneTag::showPinView()
{
    m_pinViewMoveAnimation->setStartValue(m_tagPinView->x());
    m_pinViewMoveAnimation->stop();

    if(m_currentDirection == ExtentedEnums::Right)
        m_pinViewMoveAnimation->setEndValue(0);

    else
        m_pinViewMoveAnimation->setEndValue(width() - height() - 1);

    if(m_pinViewMoveAnimation->startValue() == m_pinViewMoveAnimation->endValue())
        return;
    m_pinViewMoveAnimation->start();
}

void CloneTag::hidePinView()
{
    m_pinViewMoveAnimation->setStartValue(m_tagPinView->x());
    m_pinViewMoveAnimation->stop();

    if(m_currentDirection == ExtentedEnums::Right)
        m_pinViewMoveAnimation->setEndValue(height());

    else
        m_pinViewMoveAnimation->setEndValue(width() - 2 * height() - 1);

    if(m_pinViewMoveAnimation->startValue() == m_pinViewMoveAnimation->endValue())
        return;
    m_pinViewMoveAnimation->start();
}

void CloneTag::repositionBody(ExtentedEnums::Direction direction)
{
    if(direction == ExtentedEnums::Right)
        m_tagAppearance->setX(height());
    else
        m_tagAppearance->setX(0);
        m_tagAppearance->pointTo(direction);
}

void CloneTag::resize()
{
    const double parentHeight = parentItem()->height();
    const double height = Fraction(parentHeight, 420) * 18;
    setSize(QSizeF(Fraction(80, 25) * height + height, height));

    repositionBody(m_currentDirection);
}

void CloneTag::setCurrentPinNumber(int pinNumber)
{
    if(m_currentPinNumber == pinNumber)
        return;

    m_currentPinNumber = pinNumber;
    m_tagPinView->setPinNumber(m_currentPinNumber);
    emit currentPinNumberChanged(pinNumber);
}

void CloneTag::pointTo(ExtentedEnums::Direction direction)
{
    Q_ASSERT(direction == ExtentedEnums::Left || direction == ExtentedEnums::Right);

    if(m_currentDirection == direction)
        return;

    m_currentDirection = direction;
    repositionBody(direction);
    m_tagAppearance->pointTo(direction);

    emit directionChanged();
}

void CloneTag::setOptions(QVariantMap options)
{
    m_options = options;
    emit optionsChanged(options);
}

void CloneTag::setSelected(bool selected)
{
    if (m_selected == selected)
        return;

    m_selected = selected;

    emit selectedChanged(selected);
}

void CloneTag::setFocusOpacity(double focusOpacity)
{
    if (m_focusOpacity == focusOpacity)
        return;

    m_focusOpacity = focusOpacity;
    emit focusOpacityChanged(focusOpacity);
}

void CloneTag::setControlState(QVariantMap controlState)
{
    if (m_controlState == controlState)
        return;

    m_controlState = controlState;
    emit controlStateChanged(controlState);
}

void CloneTag::setValue(QString value)
{
    if(m_value == value)
        return;

    m_value = value;
    // TODOto signal/slot
    m_tagAppearance->setName(value);
    this->update();
}

void CloneTag::restoreName()
{
    m_tagAppearance->setName(m_tagName);
}

void CloneTag::enteredIntoGrid()
{
    if(m_opacityAnimation->endValue() == 1)
        return;
    m_opacityAnimation->stop();
    m_opacityAnimation->setStartValue(opacity());
    m_opacityAnimation->setEndValue(1);
    m_opacityAnimation->start();
}

void CloneTag::leavedFromGrid()
{
    if(m_opacityAnimation->endValue() == 0.5)
        return;
    m_opacityAnimation->stop();
    m_opacityAnimation->setStartValue(opacity());
    m_opacityAnimation->setEndValue(0.5);
    m_opacityAnimation->start();
}


