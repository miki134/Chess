#pragma once

#include "chessitem.h"

class King : public ChessItem
{
public:
    King(State & _state, ChessColor side, QGraphicsItem *parent = 0);

    void setImage() override;
    QList <Position> getPossibleMoves() override;

    void findUnSafeLocation();
};
