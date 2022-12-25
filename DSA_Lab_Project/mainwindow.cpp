#include "mainwindow.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLayoutItem>
#include <QIntValidator>
MainWindow::MainWindow()
{
    QGridLayout* layout = new QGridLayout;

    // Create the grid of QLineEdit widgets for the Sudoku board
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        grid[row][col] = new QLineEdit;
        grid[row][col]->setMaxLength(1);  // Allow only one character to be entered
        grid[row][col]->setAlignment(Qt::AlignCenter);
        grid[row][col]->setEchoMode(QLineEdit::Password);  // Hide the user's input
        grid[row][col]->setValidator(new QIntValidator(1, 9, grid[row][col]));  // Allow only integer input
        grid[row][col]->setReadOnly(true);  // Set the widget to read-only
        layout->addWidget(grid[row][col], row, col);
      }
    }

    // Create the "Play" button
    playButton = new QPushButton("Play");
    layout->addWidget(playButton, 9, 0, 1, 9);

    // Set the layout of the Sudoku board widget
    setLayout(layout);

    // Connect the "Play" button to a slot that enables all the QLineEdit widgets
    connect(playButton, &QPushButton::clicked, [this]() {
      for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
          grid[row][col]->setEchoMode(QLineEdit::Normal);  // Show the user's input
          grid[row][col]->setReadOnly(false);  // Allow the user to edit the widget
        }
      }
    });
    }

