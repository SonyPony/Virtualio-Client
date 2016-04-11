#include "tagappearance.h"
#include "extentedmath.h"
#include <qmath.h>

TagAppearance::TagAppearance(QString name, QColor firstColor, QColor secondColor, QColor focusColor, ExtentedEnums::Direction direction, QQuickItem *parent): QQuickPaintedItem(parent)
{
    m_name = name;
    m_firstColor = firstColor;
    m_secondColor = secondColor;
    m_currentDirection = direction;
    m_focusColor = focusColor;

    m_bodyMoveAnimation = new QPropertyAnimation(this, "bodyPosition", this);
    m_bodyMoveAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_bodyMoveAnimation->setDuration(250);

    setParentItem(parent);
    setBodySize();
    this->setClip(true);

    connect(this, &TagAppearance::xChanged, [this]() {
        setBodyPosition();
    });

    connect(this, &QQuickItem::widthChanged, this, &TagAppearance::setBodySize);
    connect(this, &QQuickItem::heightChanged, this, &TagAppearance::setBodySize);
    connect(this, SIGNAL(bodyPositionChanged(QPoint)), this, SLOT(updatePaintTag()));
    connect(this, &TagAppearance::nameChanged, this, &TagAppearance::updatePaintTag);
}

TagAppearance::TagAppearance(TagAppearance *other, QQuickItem *parent): TagAppearance(other->name(), other->firstColor(), other->secondColor(), other->focusColor(), other->currentDirection(), parent)
{
    m_font = other->font();
    m_textColor = other->textColor();
    this->setWidth(other->width());
    this->setHeight(other->height());
    m_currentDirection = other->currentDirection();

    connect(other, &QQuickItem::widthChanged, [this, other]() {
        this->setWidth(other->width());
    });

    connect(other, &QQuickItem::heightChanged, [this, other]() {
        this->setHeight(other->height());
    });
}

void TagAppearance::paintTag(QPainter *painter)
{
    if(!height() || !width())
        return;

    setBodyPosition();
    const double triangleWidth = ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8);
    const double x = this->x();
    QPointF leftTriangle[3] = {
        QPointF(x + triangleWidth, 0),
        QPointF(x, height() / 2.),
        QPointF(x + triangleWidth, height())
    };

    QPointF rightTriangle[3] = {
        QPointF(width() + x - triangleWidth, 0),
        QPointF(width() + x, height() / 2.),
        QPointF(width() + x - triangleWidth, height())
    };

    QLineF diagonal = ExtentedMath::rectDiagonal(QRect(x, y(), m_body.width(), m_body.height()));
    double diagonalLength = ExtentedMath::lineLength(diagonal);
    double alpha = qAtan2(height(), m_body.width());
    double c = (diagonalLength / 2.) / qCos(alpha);

    QLinearGradient fillPattern(m_body.width() - c + x, 0, c + x, height());

    if(m_currentDirection == ExtentedEnums::Left) { //move gradient as well
        fillPattern.setStart(fillPattern.start() + QPointF(triangleWidth, 0));
        fillPattern.setFinalStop(fillPattern.finalStop() + QPointF(triangleWidth, 0));
    }

    //fill pairs
    /*
     * QColor(0, 162, 232), QColor(0, 145, 206) - BLUE
     * #E6063C, #C40002 - RED
     * QColor(255, 201, 14), QColor(255, 152, 38) - BEIGE
     * QColor(62, 62, 62), QColor(42, 42, 42) - GRAY
     */
    /*fillPattern.setColorAt(0.49, QColor(186, 224, 31)); //light
    fillPattern.setColorAt(0.5, QColor(111, 196, 34));  //dark*/
    fillPattern.setColorAt(0.49, m_firstColor); //light
    fillPattern.setColorAt(0.5, m_secondColor);  //dark

    painter->setBrush(QBrush(fillPattern));
    painter->setPen(QPen(painter->brush(), 1.));
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawConvexPolygon(leftTriangle, 3);
    painter->drawConvexPolygon(rightTriangle, 3);
    painter->drawRect(m_body);

    // draw name
    painter->setFont(m_font);
    painter->setPen(m_textColor);
    painter->drawText(m_body, m_name, QTextOption(Qt::AlignCenter));
}

QRectF TagAppearance::body() const
{
    return m_body;
}

void TagAppearance::pointTo(ExtentedEnums::Direction direction)
{
    Q_ASSERT(direction == ExtentedEnums::Left || direction == ExtentedEnums::Right);

    if(m_currentDirection == direction)
        return;

    m_currentDirection = direction;

    if(direction == ExtentedEnums::Right) {
        m_bodyMoveAnimation->setStartValue(QPoint(m_body.x()+ x(), m_body.y()));
        m_bodyMoveAnimation->setEndValue(QPoint(x(), 0));
    }
    else {
        m_bodyMoveAnimation->setStartValue(QPoint(0, m_body.y()));
        m_bodyMoveAnimation->setEndValue(QPoint(width() - m_body.width(), m_body.y()));
    }
    m_bodyMoveAnimation->start();
}

void TagAppearance::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void TagAppearance::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void TagAppearance::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void TagAppearance::setFocusColor(QColor focusColor)
{
    if (m_focusColor == focusColor)
        return;

    m_focusColor = focusColor;
    emit focusColorChanged(focusColor);
}

void TagAppearance::setBodySize()
{
    if(!height() || !width())
        return;

    const double triangleWidth = ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8);
    m_body.setWidth(width() - triangleWidth);
    m_body.setHeight(height());

    updatePaintTag();
}

void TagAppearance::updatePaintTag()
{
    emit requestUpdate();
}

void TagAppearance::setBodyPosition()
{
    if(!height())
        return;

    const double triangleWidth = ceil(ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8));
    if(m_currentDirection == ExtentedEnums::Right)
        m_body.moveTo(x(), 0);
    else
        m_body.moveTo(x() + triangleWidth, 0);
}

QPoint TagAppearance::bodyPosition() const
{
    return m_bodyPosition;
}

QColor TagAppearance::firstColor() const
{
    return m_firstColor;
}

QColor TagAppearance::secondColor() const
{
    return m_secondColor;
}

ExtentedEnums::Direction TagAppearance::currentDirection() const
{
    return m_currentDirection;
}

QString TagAppearance::name() const
{
    return m_name;
}

QColor TagAppearance::textColor() const
{
    return m_textColor;
}

QFont TagAppearance::font() const
{
    return m_font;
}

QPolygon TagAppearance::shape() const
{
    const double width = this->width();
    const double height = this->height();
    const double triangleWidth = ExtentedMath::legOfRightTriangle(height / 2., height * 0.8);

    QPolygon shape;

    if(m_currentDirection == ExtentedEnums::Right) {
        shape << QPoint(width - triangleWidth, 0)
              << QPoint(width, height / 2.)
              << QPoint(width - triangleWidth, height);
    }

    else {
        shape << QPoint(triangleWidth, 0)
              << QPoint(0, height / 2.)
              << QPoint(triangleWidth, height);
    }

    return shape;
}

QColor TagAppearance::focusColor() const
{
    return m_focusColor;
}

void TagAppearance::setBodyPosition(QPoint bodyPosition)
{
    if (m_bodyPosition == bodyPosition)
        return;

    m_bodyPosition = bodyPosition;
    m_body.moveTo(bodyPosition);
    emit bodyPositionChanged(bodyPosition);
}
