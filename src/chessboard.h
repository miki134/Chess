#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMap>
#include <QObject>
#include <QGraphicsRectItem>

#include "state.h"
#include "chessbox.h"
#include "game.h"

class ChessBoard : public QGraphicsScene
{
    Q_OBJECT

    QMap<Position, ChessBox *> chessBoxes;

public:
    explicit ChessBoard();

    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
    void drawBoxes(int x, int y);

    void reset();
    void resetAllToOriginalColor();
    ChessBox *at(const Position & pos) const;
    ChessBox *operator[](const Position & pos) const;

    QMap<Position, ChessBox *>::Iterator find(Position pos);
    QMap<Position, ChessBox *>::Iterator end();
public slots:
    void boxClicked(Position pos);
signals:
    void clicked(Position);
};
