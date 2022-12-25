#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Qwidget>
#include "sudoku.h"
#include <QPushButton>
#include <QObject>
#include <QGridLayout>
#include <QLineEdit>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    void startGame(QGridLayout *layout);
private:
    QLineEdit* grid[9][9];
      QPushButton* playButton;
};

#endif // MAINWINDOW_H
