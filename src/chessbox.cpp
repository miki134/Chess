#include "chessbox.h"
//#include "game.h"
#include <QDebug>

ChessBox::ChessBox(QGraphicsItem *parent) :
    QGraphicsRectItem(parent),
    coords(0,0)
{
    //making the Square CHess Box
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);

    setZValue(-1);
}

ChessBox::~ChessBox()
{

}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(coords);
}

void ChessBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void ChessBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}

void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

void ChessBox::setCoords(Position _coords)
{
    coords = _coords;
}
