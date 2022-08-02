#include "rook.h"

Rook::Rook(State & _state, ChessColor side, QGraphicsItem *parent) :
    ChessItem(_state, side, parent)
{
    Rook::setImage();
}


void Rook::setImage()
{
    if(side == WHITE)
        setPixmap(QPixmap(":/images/rook_white.png"));
    else
        setPixmap(QPixmap(":/images/rook_black.png"));
}

QList<Position> Rook::getPossibleMoves()
{
    possibleMoves.clear();
    int row = itemPosition.x;
    int col = itemPosition.y;
    ChessColor team = side;

    // up
    for(int i = row-1,j = col; i >= 0 ; i--)
    {
        Position pos(i, j);
        if(state[pos].color == team)
            break;
        else
        {
            possibleMoves.append(pos);
            if(pieceExists(pos)) {
                break;
            }
        }
    }

     // Down
    for(int i = row+1,j = col; i <= 7 ; i++)
    {
        Position pos(i, j);
        if(state[pos].color == team)
            break;
        else
        {
            possibleMoves.append(pos);
            if(pieceExists(pos)) {
                break;
            }
        }
    }

    // left
    for(int i = row,j = col-1; j >= 0 ; j--)
    {
        Position pos(i, j);
        if(state[pos].color == team)
            break;
        else
        {
            possibleMoves.append(pos);
            if(pieceExists(pos)) {
                break;
            }
        }
    }

    // Right
    for(int i = row,j = col+1; j <= 7 ; j++)
    {
        Position pos(i, j);
        if(state[pos].color == team)
            break;
        else
        {
            possibleMoves.append(pos);
            if(pieceExists(pos)) {
                break;
            }
        }
    }

    return possibleMoves;
}
