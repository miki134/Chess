#include "king.h"
#include "state.h"


King::King(State & _state, ChessColor side, QGraphicsItem *parent) :
    ChessItem(_state, side, parent)
{
    King::setImage();
}

void King::setImage()
{
    if(side == WHITE)
        setPixmap(QPixmap(":/images/king_white.png"));
    else
        setPixmap(QPixmap(":/images/king_black.png"));
}

QList<Position> King::getPossibleMoves()
{
    possibleMoves.clear();
    int row = itemPosition.x;
    int col = itemPosition.y;
    ChessColor team = side;

    //up left
    Position pos1(row-1, col-1);
    if(col > 0 && row > 0 && state[pos1].color != team) {
        possibleMoves.append(pos1);
    }

    // up right
    Position pos2(row-1, col+1);
    if(col < 7 && row > 0 && state[pos2].color != team) {
        possibleMoves.append(pos2);
    }

    //up
    Position pos3(row-1, col);
    if(row > 0 && state[pos3].color != team) {
        possibleMoves.append(pos3);
    }

    //down
    Position pos4(row+1, col);
    if(row < 7 && state[pos4].color != team) {
        possibleMoves.append(pos4);
    }

    // left
    Position pos5(row, col-1);
    if(col > 0&& state[pos5].color != team) {
        possibleMoves.append(pos5);
    }

    //right
    Position pos6(row, col+1);
    if(col < 7 && state[pos6].color != team) {
        possibleMoves.append(pos6);
    }

    //down left
    Position pos7(row+1, col-1);
    if(col > 0 && row < 7 && state[pos7].color != team) {
        possibleMoves.append(pos7);
    }

    //down right
    Position pos8(row+1, col+1);
    if(col < 7 && row < 7 && state[pos8].color != team) {
        possibleMoves.append(pos8);
    }

    return possibleMoves;
}
