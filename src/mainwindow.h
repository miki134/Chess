#pragma once

#include <QMainWindow>
#include<QAction>
#include<QActionGroup>
#include<QLabel>
#include<QMenu>

#include "game.h"
#include "state.h"

class State;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    void loadView();
    void loadDesign();

    State state;
public:
    MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void newFile();
    void open();
    void save();
    void about();

private:
    void createActions();
    void createMenus();
    void removeLayout(QWidget* wid);

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *aboutAct;

    QWidget *mainWidget;

    QPushButton *newGame;
    QPushButton *importSave;
    QPushButton *exit;
};
