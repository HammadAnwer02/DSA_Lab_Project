#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Qwidget>
#include "sudoku.h"
#include <QPushButton>
#include <QObject>
#include <QGridLayout>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(sudoku &w);
    void startGame(QGridLayout *layout);
private:
    QWidget *widget;
    QPushButton *playButton;
};

#endif // MAINWINDOW_H
