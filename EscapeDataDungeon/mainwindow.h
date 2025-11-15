#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <queue>
#include <stack>
#include <vector>
#include "GameEngine.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submitButton_clicked(); // Triggered when user submits an answer
    void showNextElement();         // Animate puzzle elements step by step
    void onKeyCollected();          // Triggered when key is collected in game

private:
    Ui::MainWindow *ui;

    // DSA structures
    queue<int> elementQueue;                                 // For queue/array animation
    priority_queue<int, vector<int>, greater<int>> minHeap;  // For heap visualization
    stack<QLabel*> healthStack;                              // For displaying health hearts

    // Game state
    GameEngine* engine;           // Handles puzzle logic, health, rooms, answers
    QLabel* timerLabel;           // Displays remaining time
    QTimer* roomTimer;            // Room countdown timer
    int remainingTime;            // Seconds remaining
    vector<int> currentData;      // Current puzzle data (array/stack/etc)
    int displayIndex;             // Current index for element animation
    QTimer* elementTimer;         // Timer for step-by-step element display
    QLabel* roomNameLabel;        // Displays current room name

    QString customFont;           // Custom font for room labels

    // Methods
    void loadRoom();               // Load current room, puzzle, and UI
    void animateHealthLoss();      // Animate loss of one health heart
    void animateRoomTransition();  // Fade-in animation for new room
};

#endif
