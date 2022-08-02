#include "state.h"
#include <iostream>
#include <QDebug>

bool Position::operator< (const Position& b) const
{
    if (x<b.x) return true;
    else if (!(b.x<x) && y<b.y) return true;
    else return false;
}

bool Position::operator==(const Position &v) const
{
    return x==v.x && y==v.y;
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
    os << "(" << pos.x << ", " << pos.y << ')' << std::endl;
    return os;
}

State::State()
{

}

void State::setUpWhite()
{
    auto x = CHESSBOARD_HEIGHT-1;
    auto w = 0;

    items.insert(Position(x, w++), ChessPiece(ROOK, WHITE));
    items.insert(Position(x, w++), ChessPiece(KNIGHT, WHITE));
    items.insert(Position(x, w++), ChessPiece(BISHOP, WHITE));
    items.insert(Position(x, w++), ChessPiece(QUEEN, WHITE));
    items.insert(Position(x, w++), ChessPiece(KING, WHITE));
    items.insert(Position(x, w++), ChessPiece(BISHOP, WHITE));
    items.insert(Position(x, w++), ChessPiece(KNIGHT, WHITE));
    items.insert(Position(x, w++), ChessPiece(ROOK, WHITE));

    x--;
    for(w = 0; w < CHESSBOARD_WIDTH; w++)
    {
        items.insert(Position(x, w), ChessPiece(PAWN, WHITE));
    }
}

void State::setUpBlack()
{
    auto x = 0;
    auto w = 0;

    items.insert(Position(x, w++), ChessPiece(ROOK, BLACK));
    items.insert(Position(x, w++), ChessPiece(KNIGHT, BLACK));
    items.insert(Position(x, w++), ChessPiece(BISHOP, BLACK));
    items.insert(Position(x, w++), ChessPiece(QUEEN, BLACK));
    items.insert(Position(x, w++), ChessPiece(KING, BLACK));
    items.insert(Position(x, w++), ChessPiece(BISHOP, BLACK));
    items.insert(Position(x, w++), ChessPiece(KNIGHT, BLACK));
    items.insert(Position(x, w++), ChessPiece(ROOK, BLACK));

    x++;
    for(w = 0; w < CHESSBOARD_WIDTH; w++)
    {
        items.insert(Position(x, w), ChessPiece(PAWN, BLACK));
    }
}

void State::initialize()
{
    nextMove = WHITE;
    setUpBlack();
    setUpWhite();

    importSaveFromFile("./test.txt");
}

void State::readConfiguration()
{

}

void State::movePiece(Position from, Position to)
{
    auto piece = items[from];

    removePiece(from);
    addPiece(to, piece);
}

void State::addPiece(Position pos, ChessPiece obj)
{
    items.insert(pos, obj);
}

void State::removePiece(Position pos)
{
    deadItems.insert(pos, items[pos]);
    items.remove(pos);
}

void State::exportSaveToFile(QString filePath)
{
    FILE *file;
    file = fopen(filePath.toStdString().c_str(), "wt");

    if (file == NULL)
        printf("file1 has not been opened\n");
    else
    {
        for(int i = 0; i < CHESSBOARD_HEIGHT; i++)
        {
            for(int j = 0; j < CHESSBOARD_WIDTH; j++)
            {
                QString str1 = items[Position(i, j)];
                QByteArray ba = str1.toLocal8Bit();
                const char *b = ba.data();
                fprintf(file, "%s \n", b);
            }
        }
        fclose(file);
    }
}

void State::importSaveFromFile(QString filePath)
{
    FILE *file;
    file = fopen(filePath.toStdString().c_str(), "rt");

    if (file == NULL)
        printf("file1 has not been opened\n");
    else
    {
        for(int i = 0; i < CHESSBOARD_HEIGHT; i++)
        {
            for(int j = 0; j < CHESSBOARD_WIDTH; j++)
            {

                char b[50];
                fscanf(file, "%s \n", &b);
                QString str = QString::fromUtf8(b);
                ChessObject piece = static_cast<ChessObject>(str.toInt());\
                fscanf(file, "%s \n", &b);
                fscanf(file, "%s \n", &b);
                str = QString::fromUtf8(b);
                ChessColor color = static_cast<ChessColor>(str.toInt());
                items.insert(Position(i, j), ChessPiece(piece, color));
            }
        }
        fclose(file);
    }
}

ChessPiece State::operator[](const Position & pos) const
{
    if(items.find(pos) != items.end())
        return items[pos];
    return ChessPiece();
}

ChessColor State::getNextMove()
{
    return nextMove;
}

void State::changeTurn()
{
    switch(nextMove)
    {
    case WHITE:
        nextMove = BLACK;
        break;
    case BLACK:
        nextMove = WHITE;
        break;
    default:
        break;
    }
}

QMap<Position, ChessPiece> State::getDeadItems()
{
    return deadItems;
}
