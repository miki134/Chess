#include <QtWidgets>
#include <QDialog>

#include "mainwindow.h"
#include "chessboard.h"

void MainWindow::loadView()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainWidget = new QWidget;

    QVBoxLayout *hlayout = new QVBoxLayout;

    newGame = new QPushButton("New Game", this);
    importSave = new QPushButton("Load save", this);
    exit = new QPushButton("Exit", this);

    connect(newGame, &QPushButton::released, this, &MainWindow::newFile);
    connect(importSave, &QPushButton::released, this, &MainWindow::open);
    connect(exit, &QPushButton::released, this, &QWidget::close);

    hlayout->addWidget(newGame);
    hlayout->addWidget(importSave);
    hlayout->addWidget(exit);
    mainWidget->setLayout(hlayout);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(mainWidget);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);

}

MainWindow::MainWindow()
{
    loadView();
    loadDesign();

    state.readConfiguration();
    state.initialize();
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::loadDesign()
{
    QFile styleSheet(":/styles/StyleSheet.css");
    if (!styleSheet.open(QIODevice::ReadOnly))
        qDebug() << "Can't open file";
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}

void MainWindow::removeLayout(QWidget* wid)
{
    QLayout * sublayout;
    QLayout* layout = wid->layout ();
    QWidget *widget;
    if (layout != 0)
    {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)))
        {
            if ((sublayout = item->layout()) != 0) {delete sublayout;}
            else if ((widget = item->widget()) != 0) {
                widget->hide(); delete widget;
            }
            else {
                delete item;
            }
        }
        delete layout;
    }
}

void MainWindow::newFile()
{
    removeLayout(mainWidget);


    setWindowTitle(tr("Game"));
    showMaximized();
    Game * game = new Game(state, this);
    game->start();
    game->show();

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(game);
    mainWidget->setLayout(hlayout);

}

void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this, "OPEN", "./");

    if(path.isEmpty())
        return;

    qDebug() << "open" << path;

    state.importSaveFromFile(path);

    newFile();

}

void MainWindow::save()
{
    QString path = QFileDialog::getSaveFileName(this, "SAVE", "./", ".save");

    if(path.isEmpty())
        return;

    state.exportSaveToFile(path);
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Menu"),
            tr("The <b>CHESS</b> is a board game played between two players. "
               "It is sometimes called Western chess or international chess to "
               "distinguish it from related games such as xiangqi and shogi. "
               "The current form of the game emerged in Southern Europe during "
               "the second half of the 15th century after evolving from chaturanga, "
               "a similar but much older game of Indian origin. Today, chess is "
               "one of the world's most popular games, played by millions of people worldwide."));
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New game"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new game"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Load save.."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing game"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save game"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save current game to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Game"));
    fileMenu->addAction(newAct);

    fileMenu->addAction(openAct);

    fileMenu->addAction(saveAct);

    fileMenu->addSeparator();

    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
