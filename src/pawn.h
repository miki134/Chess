#pragma once

#include "chessitem.h"

class Pawn : public ChessItem
{
public:
    Pawn(State & _state, ChessColor side,QGraphicsItem *parent = 0);

    void setImage() override;
    QList <Position> getPossibleMoves() override;
};
