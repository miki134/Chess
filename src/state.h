#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <QMap>
#include <iostream>

#define CHESSBOARD_WIDTH 8
#define CHESSBOARD_HEIGHT 8


class Position
{
public:
    unsigned int x;
    unsigned int y;

    Position(unsigned int _x, unsigned int _y) :
        x(_x), y(_y) {};

    bool operator<(const Position &v) const;
    bool operator==(const Position &v) const;
    friend std::ostream& operator<<(std::ostream& os, const Position& dt);
    operator QString() const { return (QString::number(x) + ", " + QString::number(y) ); }
};

enum ChessObject {
    NULLOBJ = 0,
    PAWN = 1,
    BISHOP = 3,
    KNIGHT = 4, //3
    ROOK = 5,
    QUEEN = 9,
    KING = 10
};

enum ChessColor {
    NULLCOL = 0x0000,
    WHITE = 0x1000,
    BLACK = 0x2000,
};

class ChessPiece {
public:
    ChessObject chessObject;
    ChessColor color;

    ChessPiece() : chessObject(NULLOBJ), color(NULLCOL) {};
    ChessPiece(ChessObject _obj, ChessColor _col) :
        chessObject(_obj), color(_col){};

    bool isEmpty() {
        return (chessObject == NULLOBJ || color == NULLCOL);
    }

    operator QString() const { return (QString::number(chessObject) + " - " + QString::number(color) ); }
};

class State
{
    QMap<Position, ChessPiece> items;

    QMap<Position, ChessPiece> deadItems;

    void setUpWhite();
    void setUpBlack();

    ChessColor nextMove;
public:
    State();
    void initialize();
    void readConfiguration();

    void movePiece(Position from, Position to);
    void addPiece(Position pos, ChessPiece obj);
    void removePiece(Position pos);

    void exportSaveToFile(QString filePath);
    void importSaveFromFile(QString filePath);

    QMap<Position, ChessPiece>* getItems();

    ChessPiece operator[](const Position & pos) const;

    ChessColor getNextMove();
    void changeTurn();
    QMap<Position, ChessPiece> getDeadItems();
};
