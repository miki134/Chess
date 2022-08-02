#include "knight.h"

Knight::Knight(State & _state, ChessColor side, QGraphicsItem *parent) :
    ChessItem(_state, side, parent)
{
    Knight::setImage();
}

void Knight::setImage()
{
    if(side == WHITE)
        setPixmap(QPixmap(":/images/knight_white.png"));
    else
        setPixmap(QPixmap(":/images/knight_black.png"));
}

QList<Position> Knight::getPossibleMoves()
{
    possibleMoves.clear();
    int row = itemPosition.x;
    int col = itemPosition.y;
    ChessColor team = side;
    int i ,j;

    //1st up up left
    i = row - 2;
    j = col - 1;

    Position pos1(i, j);
    if(i >=0 && j>=0 && state[pos1].color != team) {
        possibleMoves.append(pos1);
    }

    //2nd up up right
    i = row - 2;
    j = col + 1;

    Position pos2(i, j);
    if(i >=0 && j<=7 && state[pos2].color != team) {
        possibleMoves.append(pos2);
    }

    //3rd down down left
    i = row + 2;
    j = col - 1;

    Position pos3(i, j);
    if(i <= 7 && j>=0 && state[pos3].color != team) {
        possibleMoves.append(pos3);
    }

    //4th  down down right
    i = row + 2;
    j = col + 1;

    Position pos4(i, j);
    if(i <=7 && j<=7 && state[pos4].color != team) {
        possibleMoves.append(pos4);
    }

    //5th left left up
    i = row - 1;
    j = col - 2;

    Position pos5(i, j);
    if(i >=0 && j>=0 && state[pos5].color != team) {
        possibleMoves.append(pos5);
    }

    //6th left left down
    i = row + 1;
    j = col - 2;

    Position pos6(i, j);
    if(i <=7 && j>=0 && state[pos6].color != team) {
        possibleMoves.append(pos6);
    }

    //7th right right up
    i = row - 1;
    j = col + 2;

    Position pos7(i, j);
    if(i >=0 && j<=7 && state[pos7].color != team) {
        possibleMoves.append(pos7);
    }

    //8th right right down
    i = row + 1;
    j = col +  2;

    Position pos8(i, j);
    if(i <=7 && j<=7 && state[pos8].color != team) {
        possibleMoves.append(pos8);
    }
    return possibleMoves;
}
