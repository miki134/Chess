#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "chessboard.h"
#include "state.h"
#include "chessitem.h"

class ChessBoard;
class Game : public QGraphicsView
{
    Q_OBJECT

    ChessBoard *chessboard;
    void initializePieces();
    State & state;
    QMap<Position, ChessItem *> chessItems;

    ChessItem *pieceToMove;

    QGraphicsTextItem * turnDisplay;

    void itemSelected(Position pos);
    void selecting(Position pos);
    void deselecting(Position pos);

    void piecePressEvent(Position pos);
    void boxPressEvent(Position pos);

    void movePiece(Position from,  Position to);

    QList <ChessItem *> whiteDead;
    QList <ChessItem *> blackDead;
public:
    Game(State & _state, QWidget *parent = 0);
    void drawChessBoard();

    void placeInDeadPlace();

    void removeAll();
public slots:
    void start();
    void refresh();

    void clicked(Position pos);
    void boxSettings(Position pos);
};
