#include "pawn.h"

Pawn::Pawn(State & _state, ChessColor side, QGraphicsItem *parent) :
    ChessItem(_state, side, parent)
{
    Pawn::setImage();
    firstMove = true;
}

void Pawn::setImage()
{
    if(side == WHITE)
        setPixmap(QPixmap(":/images/pawn_white.png"));
    else
        setPixmap(QPixmap(":/images/pawn_black.png"));
}

QList<Position> Pawn::getPossibleMoves()
{
    possibleMoves.clear();

    int row = itemPosition.x;
    int col = itemPosition.y;

    if(side == WHITE)
    {
        Position pos1(row-1, col-1);
        if(col > 0 && row > 0 && state[pos1].color == BLACK) {
            possibleMoves.append(pos1);
        }

        Position pos2(row-1, col+1);
        if(col < 7 && row > 0 && state[pos2].color == BLACK) {
            possibleMoves.append(pos2);
        }

        Position pos3(row-1, col);
        if(row>0 && state[pos3].isEmpty()) {
            possibleMoves.append(pos3);

            Position pos4(row-2, col);
            if(firstMove && state[pos4].isEmpty()){
                qDebug() << firstMove;
                possibleMoves.append(pos4);
            }
        }

    }
    else
    {
        Position pos1(row+1, col-1);
        if(col > 0 && row < 7 && state[pos1].color == WHITE) {
            possibleMoves.append(pos1);
        }

        Position pos2(row+1, col+1);
        if(col < 7 && row <  7 && state[pos2].color == WHITE) {
            possibleMoves.append(pos2);
        }

        Position pos3(row+1, col);
        if(row<7 && state[pos3].isEmpty()) {
            possibleMoves.append(pos3);

            Position pos4(row+2, col);
            if(firstMove && state[pos4].isEmpty()){
                possibleMoves.append(pos4);
            }
        }
    }
    return possibleMoves;
}
