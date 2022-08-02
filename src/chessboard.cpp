#include "chessboard.h"
#include <QObject>
ChessBoard::ChessBoard()
{
}

void ChessBoard::addToScene(QGraphicsItem *item)
{
    addItem(item);
}

void ChessBoard::removeFromScene(QGraphicsItem *item)
{
    removeItem(item);
}


void ChessBoard::drawBoxes(int x,int y)
{
    int SHIFT = 100;
    for(int i = 0; i < CHESSBOARD_HEIGHT; i++) {
        for(int j = 0; j < CHESSBOARD_WIDTH; j++) {
            ChessBox *box = new ChessBox();

            Position coords(i, j);

            box->setCoords(coords);
            box->setPos(x+SHIFT*j,y+SHIFT*i);

            if((i+j) % 2 == 0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);

            QObject::connect(box, &ChessBox::clicked, this, &ChessBoard::boxClicked);
            addToScene(box);
            chessBoxes.insert(coords, box);
        }
    }
}

void ChessBoard::reset()
{
}

void ChessBoard::resetAllToOriginalColor()
{
    for (auto it : chessBoxes)
        it->resetOriginalColor();
}

ChessBox *ChessBoard::at(const Position & pos) const
{
    if(chessBoxes.find(pos) != chessBoxes.end())
        return chessBoxes[pos];
    ChessBox *it = new ChessBox();
    return it;
}

ChessBox * ChessBoard::operator[](const Position & pos) const
{
    if(chessBoxes.find(pos) != chessBoxes.end())
        return chessBoxes[pos];
    ChessBox *it = new ChessBox();
    return it;
}

QMap<Position, ChessBox *>::Iterator ChessBoard::find(Position pos)
{
    return chessBoxes.find(pos);
}

QMap<Position, ChessBox *>::Iterator ChessBoard::end()
{
    return chessBoxes.end();
}

void ChessBoard::boxClicked(Position pos)
{
    emit clicked(pos);
}
