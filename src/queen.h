#pragma once

#include "chessitem.h"

class Queen : public ChessItem
{
public:
    Queen(State & _state, ChessColor side, QGraphicsItem *parent = 0);

    void setImage() override;
    QList <Position> getPossibleMoves() override;
};
