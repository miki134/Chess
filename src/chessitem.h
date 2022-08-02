#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "state.h"

class ChessItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    Position itemPosition;
    ChessColor side;
    bool isPlaced;

    QList <Position> possibleMoves;

    State & state;

    bool pieceExists(Position pos);
public:
    bool firstMove;

    ChessItem(State & _state, ChessColor color, QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setPosition(Position _pos);
    Position getCurrentPosition();

    ChessColor getSide();
    void setSide(ChessColor value);

    virtual QList <Position> getPossibleMoves();
    virtual void setImage() = 0;

    void decolor();

signals:
    void clicked(Position);
    void boxUpdate(Position);

};
