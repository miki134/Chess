#include "mainwindow.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Chess");
    w.setWindowIcon(QIcon(":/icons/icon.png"));
    w.show();

    return a.exec();
}
