#include "queen.h"

Queen::Queen(State & _state, ChessColor side, QGraphicsItem *parent) :
    ChessItem(_state, side, parent)
{
    Queen::setImage();
}

void Queen::setImage()
{
    if(side == WHITE)
        setPixmap(QPixmap(":/images/queen_white.png"));
    else
        setPixmap(QPixmap(":/images/queen_black.png"));
}

QList<Position> Queen::getPossibleMoves()
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

    //Down
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

    //upper Left
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--)
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

     // upper right
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

    // down right
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

    // down left
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

