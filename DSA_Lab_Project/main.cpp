#include "sudoku.h"
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sudoku w;
    MainWindow board;
    board.show();
    return a.exec();
}
