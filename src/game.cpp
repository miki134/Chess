#include "game.h"
#include "chessbox.h"
#include "chessitem.h"
#include "pawn.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "rook.h"

#include <QPixmap>
#include <QDebug>

void Game::piecePressEvent(Position pos)
{
    auto item = chessItems[pos];
    auto chessBox = chessboard->at(pos);
    auto possibleMoves = item->getPossibleMoves();

    if(chessItems[pos] == pieceToMove){
        chessboard->resetAllToOriginalColor();
        pieceToMove = NULL;
       return;
    }

    if(((state.getNextMove() != item->getSide()) && (!pieceToMove)))
        return;

    //selecting
    if(!pieceToMove){
        pieceToMove = item;

        for(auto it : possibleMoves) {
            if(!state[it].isEmpty())
            {

                if(state[it].chessObject == KING)
                    chessboard->at(it)->setColor(QColor(255, 0, 0, 100));
                else
                    chessboard->at(it)->setColor(QColor(120, 0, 0, 100));
            }
            else
                chessboard->at(it)->setColor(QColor(77, 77, 77, 100));
        }

        chessBox->setColor(QColor(26, 26, 26, 100));
    }
    else if(item->getSide() != pieceToMove->getSide()){
        boxPressEvent(pos);
    }
}

void Game::boxPressEvent(Position pos)
{
    auto item = chessItems[pos];
    auto chessBox = chessboard->at(pos);

    if(item == pieceToMove && item){
      piecePressEvent(pos);
      return;
    }

    //if selected
    if(pieceToMove)
    {
        auto possibleMoves = pieceToMove->getPossibleMoves();

        bool goodMove = false;
        for(auto it : possibleMoves) {
            if(it == pos)
                goodMove = true;
        }

        if(!goodMove) {
            chessboard->resetAllToOriginalColor();
            pieceToMove = NULL;
            return;
        }

        if(!state[pos].isEmpty())
        {
            if(state[pos].chessObject == KING)
            {
                return;
            }

            state.removePiece(pos);
            chessboard->removeFromScene(chessItems[pos]);
        }

        auto from = pieceToMove->getCurrentPosition();
        state.movePiece(from, pos);
        movePiece(from, pos);
        chessboard->resetAllToOriginalColor();

        chessItems[pos]->firstMove = false;
        pieceToMove->firstMove = false;

        chessBox->resetOriginalColor();

        pieceToMove = NULL;

        QString turn;
        if(state.getNextMove() == WHITE)
            turn = "BLACK";
        else
            turn = "WHITE";
        turnDisplay->setPlainText("Turn : " + turn);

        state.changeTurn();
    }
    else if(item)
    {
        piecePressEvent(pos);
    }
}

void Game::movePiece(Position from, Position to)
{
    auto item = chessItems[from];
    item->firstMove = false;
    chessboard->removeFromScene(item);


    auto chessBox = chessboard->at(to);
    qreal x = chessBox->x() + 50 - item->pixmap().width()/2;
    qreal y = chessBox->y() + 50 - item->pixmap().width()/2;
    item->setPos(x,y);
    item->setPosition(to);

    chessItems.insert(to, item);
//    chessItems.remove(from);
    chessboard->addToScene(item);
}

Game::Game(State & _state, QWidget *parent) :
    QGraphicsView(parent),
    state(_state)
{

    chessboard = new ChessBoard();

    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(chessboard);
    pieceToMove = NULL;

    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");

    QObject::connect(chessboard, &ChessBoard::clicked, this, &Game::clicked);

    drawChessBoard();
}

void Game::drawChessBoard()
{
    chessboard->drawBoxes(width()/2-400,50);
}

void Game::placeInDeadPlace()
{
}

void Game::start()
{
    refresh();

    chessboard->addToScene(turnDisplay);
}

void Game::refresh()
{
    removeAll();
    for(int i = 0; i < CHESSBOARD_HEIGHT; i++) {
        for(int j = 0; j < CHESSBOARD_WIDTH; j++)
        {
            Position pos(i, j);
            auto piece = state[pos];
            if(!piece.isEmpty()) {
                ChessItem *item;
                switch(piece.chessObject)
                {
                case PAWN:
                    item = new Pawn(state, piece.color);
                    break;
                case BISHOP:
                    item = new Bishop(state, piece.color);
                    break;
                case KNIGHT:
                    item = new Knight(state, piece.color);
                    break;
                case ROOK:
                    item = new Rook(state, piece.color);
                    break;
                case QUEEN:
                    item = new Queen(state, piece.color);
                    break;
                case KING:
                    item = new King(state, piece.color);
                    break;
                default:

                    qDebug() << "error: undefined chess piece";
                    return;
                }

                auto chessBox = chessboard->at(pos);
                qreal x = chessBox->x() + 50 - item->pixmap().width()/2;
                qreal y = chessBox->y() + 50 - item->pixmap().width()/2;
                item->setPos(x,y);
                item->setPosition(pos);

                QObject::connect(item, &ChessItem::clicked, this, &Game::clicked);
                QObject::connect(item, &ChessItem::boxUpdate, this, &Game::boxSettings);
                chessItems.insert(pos, item);
                chessboard->addToScene(item);
            }
        }
    }
}

void Game::clicked(Position pos)
{
    qDebug() << " Game::clicked" << pos;

    boxPressEvent(pos);
}

void Game::boxSettings(Position pos)
{
    qDebug() << "boxSettings";
    auto box = chessboard->at(pos);
    auto item = chessItems.find(pos);

    if(item != chessItems.end()) {
        King *q = dynamic_cast<King*>(*item);
        if(q){
            box->setColor(Qt::blue);
        }
        else
            box->setColor(Qt::red);
    }
    else
        box->setColor(Qt::darkRed);
}

void Game::removeAll(){
    for(auto it : chessItems) {
        chessboard->removeFromScene(it);
    }
}
