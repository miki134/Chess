#pragma once

#include "chessitem.h"

class Rook : public ChessItem
{
public:
    Rook(State & _state, ChessColor side, QGraphicsItem *parent = 0);

    void setImage() override;
    QList <Position> getPossibleMoves() override;

};
