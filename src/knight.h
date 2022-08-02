#pragma once

#include "chessitem.h"

class Knight : public ChessItem
{
public:
    Knight(State & _state, ChessColor side, QGraphicsItem *parent = 0);

    void setImage() override;
    QList <Position> getPossibleMoves() override;
};
