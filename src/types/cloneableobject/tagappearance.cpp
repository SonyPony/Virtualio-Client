#include "tagappearance.h"
#include "extentedmath.h"
#include <qmath.h>

TagAppearance::TagAppearance(QColor firstColor, QColor secondColor, QQuickItem *parent)
{
    m_firstColor = firstColor;
    m_secondColor = secondColor;
    m_currentDirection = ExtentedEnums::Left;

    m_bodyMoveAnimation = new QPropertyAnimation(this, "bodyPosition", this);
    m_bodyMoveAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_bodyMoveAnimation->setDuration(250);

    setParentItem(parent);
    setWidth(parent->width());
    setHeight(parent->height());
    setBodySize();

    connect(parentItem(), SIGNAL(widthChanged()), this, SLOT(resizeAppearance()));
    connect(parentItem(), SIGNAL(heightChanged()), this, SLOT(resizeAppearance()));
    connect(this, SIGNAL(widthChanged()), this, SLOT(setBodySize()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(setBodySize()));
    connect(this, SIGNAL(bodyPositionChanged(QPoint)), this, SLOT(updatePaintTag()));
}

TagAppearance::TagAppearance(TagAppearance *other, QQuickItem *parent):
    TagAppearance(other->firstColor(), other->secondColor(), parent)
{
}

void TagAppearance::resizeAppearance()
{
    setSize(QSizeF(parentItem()->width(), parentItem()->height()));
}

void TagAppearance::paintTag(QPainter *painter)
{
    if(!height() || !width())
        return;

    double triangleWidth = ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8);
    QPoint leftTriangle[3] = {
        QPoint( triangleWidth + 1, 0),
        QPoint(0, height() / 2.),
        QPoint(triangleWidth + 1, height())
    };

    QPoint rightTriangle[3] = {
        QPoint(width() - triangleWidth, 0),
        QPoint(width(), height() / 2.),
        QPoint(width() - triangleWidth, height())
    };


    QLineF diagonal = ExtentedMath::rectDiagonal(QRect(x(), y(), m_body.width(), m_body.height()));
    double diagonalLength = ExtentedMath::lineLength(diagonal);
    double alpha = qAtan2(height(), m_body.width());
    double c = (diagonalLength / 2.) / qCos(alpha);

    QLinearGradient fillPattern(m_body.width() - c, 0, c, height());

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

    painter->setPen(QPen("transparent"));
    painter->setBrush(QBrush(fillPattern));
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawConvexPolygon(leftTriangle, 3);
    painter->drawConvexPolygon(rightTriangle, 3);
    painter->drawRect(m_body);
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
    m_bodyMoveAnimation->setStartValue(QPoint(m_body.x(), m_body.y()));

    if(direction == ExtentedEnums::Right)
        m_bodyMoveAnimation->setEndValue(QPoint(0, 0));

    else
        m_bodyMoveAnimation->setEndValue(QPoint(width() - m_body.width(), m_body.y()));

    m_bodyMoveAnimation->start();
}

void TagAppearance::setBodySize()
{
    if(!height() || !width())
        return;
    double triangleWidth = ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8);
    m_body = QRectF(QPoint(), QSize(width() - triangleWidth, height()));
}

void TagAppearance::updatePaintTag()
{
    emit requestUpdate();
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


void TagAppearance::setBodyPosition(QPoint bodyPosition)
{
    if (m_bodyPosition == bodyPosition)
        return;

    m_bodyPosition = bodyPosition;
    m_body.moveTo(bodyPosition);
    emit bodyPositionChanged(bodyPosition);
}
