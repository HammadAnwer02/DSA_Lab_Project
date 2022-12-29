#include "mainwindow.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLayoutItem>
#include <QIntValidator>
#include <QSpacerItem>
#include <QLabel>
#include "sudukoboard.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QApplication>
MainWindow::MainWindow()
{


    QGridLayout* layout = new QGridLayout;
b=new sudukoboard();
b->fill();
b->numMistakes=0;
b->clearRandomSpots(30);
b->setMaxMistakes(4);
QHBoxLayout* mistakesLayout = new QHBoxLayout;

QLabel* mistakesTextLabel = new QLabel("Mistakes:");
mistakesLayout->addWidget(mistakesTextLabel);
mistakesTextLabel->setAlignment(Qt::AlignRight);

// Create the QLabel widget for the mistakes counter
mistakesLabel = new QLabel;
mistakesLayout->addWidget(mistakesLabel);

// Update the mistakes counter text
mistakesLabel->setText(QString::number(b->numMistakes));

// Add the "out of" text and maxMistakes value to the mistakes counter text
mistakesLabel->setText(mistakesLabel->text() + " out of " + QString::number(b->getMaxMistakes()));

layout->addLayout(mistakesLayout, 9, 5);



    // Create the grid of QLineEdit widgets for the Sudoku board
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        grid[row][col] = new QLineEdit;
        grid[row][col]->setMaxLength(1);  // Allow only one character to be entered
        grid[row][col]->setAlignment(Qt::AlignCenter);
        grid[row][col]->setEchoMode(QLineEdit::Password);  // Hide the user's input
        grid[row][col]->setValidator(new QIntValidator(1, 9, grid[row][col]));  // Allow only integer input
        grid[row][col]->setReadOnly(true);  // Set the widget to read-only
        grid[row][col]->setMinimumSize(85, 70);  // Set the minimum size to 70x70 pixels
              grid[row][col]->setMaximumSize(85, 70);  // Set the maximum size to 70x70 pixels

        layout->addWidget(grid[row][col], row, col);
      }
    }






    // Create the "Play" button
    playButton = new QPushButton("Play");

    layout->addWidget(playButton, 9, 0, 1, 5);

    // Set the layout of the Sudoku board widget
    setLayout(layout);

    // Connect the "Play" button to a slot that enables all the QLineEdit widgets
    connect(playButton, &QPushButton::clicked, [this]() {
      for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
grid[row][col]->setText(QString::number(b->board[row][col]));
          grid[row][col]->setEchoMode(QLineEdit::Normal);  // Show the user's input
            // Allow the user to edit the widget
          if (b->board[row][col] == 0) {
                grid[row][col]->setText("");
                grid[row][col]->setReadOnly(false);
                connect(grid[row][col], &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
              } else {
                grid[row][col]->setText(QString::number(b->board[row][col]));
                grid[row][col]->setReadOnly(true);
              }
        }
      }
    });
    }

void MainWindow::onTextChanged(const QString& text)
{
  // Find the QLineEdit widget that emitted the signal
  QLineEdit* sender = qobject_cast<QLineEdit*>(QObject::sender());
  if (!sender) return;

  // Find the row and column of the QLineEdit widget
  int row = -1, col = -1;
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (grid[r][c] == sender) {
        row = r;
        col = c;
        break;
      }
    }
  }
  if (row == -1 || col == -1) return;

  // Convert the text entered by the user to an integer
  bool ok;
  int value = text.toInt(&ok);
  if (!ok) return;  // Conversion failed, do nothing

  // Create a NumberPosition struct with the row, column, and value
  NumberPosition pos;
  pos.row = row;
  pos.col = col;
  pos.value = value;

  // Check if the value is valid for the specified position
  bool x = b->isValid(pos.row,pos.col, pos.value);
  if (x) {
    // Set the background color of the widget to green
    sender->setStyleSheet("background-color: green;");

    // Set the widget to read-only to fix the number in place
    sender->setReadOnly(true);
  } else {
    // Set the background color of the widget to red
    sender->setStyleSheet("background-color: red;");
    b->numMistakes++;
    mistakesLabel->setText(QString::number(b->numMistakes));
    mistakesLabel->setText(mistakesLabel->text() + " out of " + QString::number(b->getMaxMistakes()));
    if (b->numMistakes==b->getMaxMistakes()){
        // Create the message box
        QMessageBox messageBox;

        // Set the text and caption of the message box
        messageBox.setText("Game over, restart the application to play again.");
        messageBox.setWindowTitle("Game Over");

        // Add a close button to the message box
        messageBox.setStandardButtons(QMessageBox::Close);

        // Show the message box and wait for the user to click the close button
        messageBox.exec();

        // Close the application
        qApp->quit();
    }
  }
}

