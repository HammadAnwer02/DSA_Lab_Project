#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Qwidget>
#include "sudoku.h"
#include <QPushButton>
#include <QObject>
#include <QGridLayout>
#include <QLineEdit>
#include "sudukoboard.h"
#include <QString>
#include <iostream>
#include <QLabel>
using namespace std;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    void startGame(QGridLayout *layout);
    void onTextChanged(const QString& text);
    void restartGame();
    QLabel* mistakesLabel;
    struct NumberPosition
    {
      int row;
      int col;
      int value;
    };
private:
    QLineEdit* grid[9][9];
      QPushButton* playButton;
      QFrame* horizontalLines[3];
        QFrame* verticalLines[3];
        sudukoboard *b;;
        };


#endif // MAINWINDOW_H
