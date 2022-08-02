#pragma once

#include "chessitem.h"

class Bishop : public ChessItem
{
public:
    Bishop(State & _state, ChessColor side, QGraphicsItem *parent = 0);

    void setImage() override;
    QList <Position> getPossibleMoves() override;

};

