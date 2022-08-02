#include "chessitem.h"
#include "game.h"
#include <QDebug>

#include <iostream>

bool ChessItem::pieceExists(Position pos)
{
    if(!state[pos].isEmpty())
        return true;
    return false;
}

ChessItem::ChessItem(State & _state, ChessColor _color, QGraphicsItem * parent) :
    QGraphicsPixmapItem(parent),
    itemPosition(0, 0),
    side(_color),
    state(_state)
{

}

void ChessItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(itemPosition);
}

void ChessItem::setPosition(Position _pos)
{
    itemPosition = _pos;
}

Position ChessItem::getCurrentPosition()
{
    return itemPosition;
}

ChessColor ChessItem::getSide()
{
    return side;
}

void ChessItem::setSide(ChessColor value)
{
    side = value;
}

QList<Position> ChessItem::getPossibleMoves()
{
    return possibleMoves;
}

void ChessItem::decolor()
{

}
