#pragma once

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "state.h"

class ChessBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    Position coords;
    QBrush brush;
    QColor originalColor;

public:
    ChessBox(QGraphicsItem *parent = 0);
    ~ChessBox();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void setColor(QColor color);

    void resetOriginalColor();
    void setOriginalColor(QColor value);
    void setCoords(Position coords);
signals:
    void clicked(Position pos);

};
