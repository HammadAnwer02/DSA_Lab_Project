#include "mainwindow.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLayoutItem>

MainWindow::MainWindow(sudoku &w)
{
    widget = new QWidget(&w);
    w.setCentralWidget(widget);

    playButton = new QPushButton("Play", widget);

    playButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    QGridLayout *layout = new QGridLayout(widget);
    for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                QLineEdit *cell = new QLineEdit;
                cell->setFont(QFont("Arial", 24));
                cell->setMinimumSize(50, 50);
                cell->setMaxLength(1);
                cell->setInputMask("9");
                cell->setAlignment(Qt::AlignCenter);
                 cell->setEnabled(false); // disable the cell by default
                layout->addWidget(cell, row, col);
            }
        }
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(startGame(layout)));
    layout->addWidget(playButton, 9, 0, 1, 9);
    widget->setLayout(layout);
    w.show();
}

void MainWindow::startGame(QGridLayout *layout)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            QLineEdit *cell = qobject_cast<QLineEdit*>(layout->itemAtPosition(row, col)->widget());
            cell->setEnabled(true);
        }
    }
}
