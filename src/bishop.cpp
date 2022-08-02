#include "bishop.h"

Bishop::Bishop(State & _state, ChessColor side, QGraphicsItem *parent) :
    ChessItem(_state, side, parent)
{
    Bishop::setImage();
}

void Bishop::setImage()
{
    if(side == WHITE)
        setPixmap(QPixmap(":/images/bishop_white.png"));
    else
        setPixmap(QPixmap(":/images/bishop_black.png"));
}

QList<Position> Bishop::getPossibleMoves()
{
    possibleMoves.clear();
    int row = itemPosition.x;
    int col = itemPosition.y;
    ChessColor team = side;

    //For upper Left
    for(int i = row-1, j = col-1; i >= 0 && j >=0; i--, j--)
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

     //For upper right
    for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++)
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

      //For downward right

    for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++)
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

       //For downward left

    for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--)
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
