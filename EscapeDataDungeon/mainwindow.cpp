#include "MainWindow.h"
#include "ui_MainWindow.h"      // UI elements for MainWindow
#include <QFontDatabase>        // For loading custom fonts dynamically
#include <QString>              // Qt string class
#include <QMessageBox>          // Pop-up message dialogs
#include <QGraphicsOpacityEffect> // For fade-in/fade-out animations
#include <QPropertyAnimation>   // Animations of properties like opacity, geometry
#include <QTimer>               // Timer events (used for element animation and room countdown)
#include <QLabel>               //For displaying text (puzzle, hearts, timer)
#include <QGraphicsColorizeEffect> // Colorize effects (used in Trap Room)
#include <cmath>                // For math functions like log2() for BST/Heap visualization
#include <stack>                // Stack container (used for health tracking)
#include <queue>                // Queue container (used for queue and array visualization)
#include <vector>               // Vector container (used to store puzzle elements)
using namespace std;
// CONSTRUCTOR
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Initialize the UI from Qt Designer file
    ui->setupUi(this);

    // ENTER KEY CONNECT
    // When user presses ENTER in the input line edit, it triggers the submit button click
    connect(ui->answerLineEdit, &QLineEdit::returnPressed,
            ui->submitButton, &QPushButton::click);

    ui->answerLineEdit->setStyleSheet( // designing of ans input
        "QLineEdit {"
        "   background-color: rgba(10, 20, 50, 180);"
        "   color: white;"
        "   font-size: 10pt;"
        "   font-weight: bold;"
        "   border: 2px solid rgba(100, 200, 255, 180);"
        "   border-radius: 8px;"
        "   padding: 5px 10px;"
        "}"
        );

    ui->submitButton->setStyleSheet( // designing of submit button
        "QPushButton {"
        "   background-color: rgba(10, 20, 50, 200);"
        "   color: white;"
        "   font-size: 10pt;"
        "   font-weight: bold;"
        "   border: 2px solid rgba(100, 200, 255, 180);"
        "   border-radius: 15px;"
        "   padding: 3px;"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(0, 100, 255, 180);" // changes color on press
        "}"
        );

    // INITIALIZE GAME ENGINE
    //Handles puzzle logic,health, current room, and answer validation.
    engine = new GameEngine();

    // Connect the engine's signal for key collection to a slot in MainWindow
    // jab gameEngine ka signal ayega tw mainwindow ka func(slot) as a response chlega
    connect(engine, &GameEngine::keyCollectedSignal, this, &MainWindow::onKeyCollected);

    //ELEMENT DISPLAY TIMER
    // Animate puzzle elements one by one.
    displayIndex = 0;
    elementTimer = new QTimer(this);
    //Every timeout triggers showNextElement()
    connect(elementTimer, &QTimer::timeout, this, &MainWindow::showNextElement);

    //LOAD CUSTOM FONT
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Gildsley DEMO.otf");
    customFont = QFontDatabase::applicationFontFamilies(fontId).at(0);
    // customFont will be applied to room labels for aesthetic appearance

    // INITIALIZE TIMER LABEL
    timerLabel = new QLabel(this); //create timerlabel
    timerLabel->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");
    timerLabel->setGeometry(550, 20, 100, 30); // Top-right corner
    remainingTime = 30; // 30 seconds per room
    timerLabel->setText("00:30"); // Initialize text

    // ROOM COUNTDOWN TIMER
    // Executes every 1 second to decrease remainingTime
    roomTimer = new QTimer(this);
    connect(roomTimer, &QTimer::timeout, [this]() {
        remainingTime--; // decrease timer by 1 second

        // Convert seconds into mm:ss format for display
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        timerLabel->setText(QString("Time: %1:%2")
                                .arg(minutes, 2, 10, QChar('0'))
                                .arg(seconds, 2, 10, QChar('0')));

        // TIME UP HANDLING
        if (remainingTime <= 0) {
            engine->submitAnswer(""); // Auto submit empty answer
            animateHealthLoss();      // Deduct one health

            if(engine->isGameOver()){ // Player has no remaining health
                QMessageBox::critical(this, "Game Over", "Time's up! You lost all your health!");
                this->close();
                return;
            }

            engine->moveToNextRoom(); // Move to next room
            loadRoom();               // Load UI and puzzle for the new room
        }
    });
    roomTimer->start(1000); // Timer triggers every 1 second

    // LOAD FIRST ROOM
    loadRoom(); // Calls the function to initialize puzzle, background, and DSA visualization
}

// DESTRUCTOR
MainWindow::~MainWindow()
{
    delete engine; // Free GameEngine
    delete ui;     // Free UI resources
}

//LOAD ROOM
// This function sets up the room UI, puzzle data, animations, health stack
void MainWindow::loadRoom() {
    // Ensures a fresh start for each room when we clear everything
    ui->puzzleDisplay->clear(); // Clear previous puzzle
    displayIndex = 0;           // Reset index for element animation
    remainingTime = 30;         // Reset timer
    // CLEAR OLD DATA
    elementQueue = queue<int>(); // Clear queue
    while(!healthStack.empty()){ // Clear previous health hearts
        healthStack.top()->deleteLater();
        healthStack.pop();
    }
    minHeap = priority_queue<int, vector<int>, greater<int>>(); // Clear heap
    //RESET TIMER DISPLAY
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    timerLabel->setText(QString("Time: %1:%2")
                            .arg(minutes, 2, 10, QChar('0'))
                            .arg(seconds, 2, 10, QChar('0')));

    // ROOM NAMES
    vector<QString> roomNames = {
        "Array Alley",
        "Stack Chamber",
        "Queue Corridor",
        "Heap Heights",
        "BST Bridge",
        "Linked List Hall",
        "Trap Room"
    };
    int index = engine->getCurrentRoomIndex(); //returns the number of completed rooms
    QString roomName;
    //Shows current room name based on engine’s room index.
     //Handles out-of-range indices gracefully.
    if (index >= 0 && index < roomNames.size())
        roomName = roomNames[index];
    else
        roomName = "Unknown Room";

    // Display room name
    ui->roomNameLabel->show(); //room name ka qlabel show hga
    ui->roomNameLabel->setText(roomName); // qlabel pe text set kia
    ui->roomNameLabel->setStyleSheet( //designing of it
        QString("color: white; font-size: 22pt; font-family: '%1';").arg(customFont)
        );

    // Change submit button text for Linked List Room
    if(engine->getCurrentRoomIndex() == 5)
        ui->submitButton->setText("SECRET");
    else
        ui->submitButton->setText("Submit");

    PuzzleBase* puzzle = engine->getCurrentPuzzle(); // Get current puzzle
    if(!puzzle) return; // If no puzzle, exit

    //BACKGROUND SETUP
    QString roomBg;
    switch(engine->getCurrentRoomIndex()) {
    case 0: roomBg = ":/images/1.jpeg"; break;
    case 1: roomBg = ":/images/2.jpeg"; break;
    case 2: roomBg = ":/images/3.jpeg"; break;
    case 3: roomBg = ":/images/4.jpeg"; break;
    case 4: roomBg = ":/images/5.jpeg"; break;
    case 5: roomBg = ":/images/6.jpeg"; break;
    case 6: roomBg = ""; break; // Trap Room handled separately
    default: roomBg = ":/images/1.jpeg"; break;
    }

    // Trap Room has red pulsating background effect
    if(engine->getCurrentRoomIndex() == 6){
        this->setStyleSheet("QMainWindow { background-color: rgb(120, 0, 0); }");
        QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(this);
        effect->setColor(Qt::red);
        this->setGraphicsEffect(effect);
        QPropertyAnimation* pulse = new QPropertyAnimation(effect, "strength");
        pulse->setDuration(800);
        pulse->setStartValue(0.2);
        pulse->setEndValue(0.9);
        pulse->setEasingCurve(QEasingCurve::InOutQuad);
        pulse->setLoopCount(-1); // Infinite loop
        pulse->start();
    } else {
        // Normal rooms with background image
        this->setStyleSheet(
            QString("QMainWindow { background-image: url(%1); "
                    "background-repeat: no-repeat; "
                    "background-position: center;}").arg(roomBg)
            );
    }

    // QUESTION LABEL STYLING
    if(engine->getCurrentRoomIndex() == 6) {
        // Trap Room: transparent background for question label
        ui->questionLabel->setStyleSheet(
            "color: white; font-size: 10.5pt; font-weight: bold; background-color: rgba(0,0,0,0); border-radius: 0px; padding: 0px;"
            );
    } else {
        // Other rooms: semi-transparent box behind question
        ui->questionLabel->setStyleSheet(
            "color: white; font-size: 10.5pt; font-weight: bold; background-color: rgba(10,20,50,128); border-radius: 10px; padding-left:10px; padding:10px;"
            );
    }

    ui->questionLabel->setText(QString::fromStdString(puzzle->getQuestion())); //questionLabel me textSet kia jyega

    // DELETE OLD ELEMENT LABELS
    QList<QLabel*> qtBoxes = ui->puzzleDisplay->findChildren<QLabel*>("stackBox");
    for(QLabel* b : qtBoxes) b->deleteLater();

    // LOAD PUZZLE DATA (vectors)
    currentData.clear();
    if(ArrayPuzzle* arr = dynamic_cast<ArrayPuzzle*>(puzzle)) currentData = arr->getData();
    else if(StackPuzzle* st = dynamic_cast<StackPuzzle*>(puzzle)) currentData = st->getData();
    else if(QueuePuzzle* q = dynamic_cast<QueuePuzzle*>(puzzle)) currentData = q->getData();
    else if(HeapPuzzle* h = dynamic_cast<HeapPuzzle*>(puzzle)) currentData = h->getData();
    else if(LinkedListPuzzle* l = dynamic_cast<LinkedListPuzzle*>(puzzle)) currentData = l->getData();
    else if(BSTPuzzle* bst = dynamic_cast<BSTPuzzle*>(puzzle)) currentData = bst->getData();

    // FILL QUEUE & HEAP
    // currentData → vector<int> containing the numbers for the current puzzle
    // elementQueue → queue<int> used to animate puzzle elements on the screen in order.
    for(auto it = currentData.begin(); it != currentData.end(); ++it){
        elementQueue.push(*it); // Queue for animation
    }

    // HEALTH STACK
    //Loop through each health point
    for(int i = 0; i < engine->getHealth(); ++i){
        QLabel* heart = new QLabel("❤", ui->healthLabel);//This creates a small box with a heart symbol inside it.
                                                        // ui->healthLabel is the container on the screen where the heart will appear.
        heart->setStyleSheet("color: white; font-size: 18pt;");
        heart->setGeometry(10 + i*25, 0, 20, 20);
        heart->show(); // show heart
        healthStack.push(heart); //push heart into stack
    }

    //START ELEMENT ANIMATION
    elementTimer->stop(); //stop() ensures any previous animation is stopped before starting a new one
    displayIndex = 0;
    if(!currentData.empty()) elementTimer->start(200); //currentData is the vector of numbers/nodes for the current puzzle.
                                                       //If it is not empty, start the timer to animate elements.
    else ui->puzzleDisplay->hide(); //If there’s nothing to display, hide the puzzle display

    // Refresh health display
    animateRoomTransition();   // Fade-in animation
    ui->answerLineEdit->setFocus(); // Focus input box
}

// Show Next Element
// showNextElement() is called by a QTimer every few milliseconds (200 ms in your code).
//Its job is to take the next element from the puzzle data (queue or heap)
//and animate it onto the screen.
void MainWindow::showNextElement() {
    //elementQueue contains elements for Array, Stack, Queue, Linked List puzzles.
    //minHeap contains elements for Heap puzzles.
    //If both are empty, all elements have been displayed → stop the timer.
    if (elementQueue.empty() && minHeap.empty()) {
        elementTimer->stop();
        return;
    }

    int value; //value will hold the next number/node to display
    PuzzleBase* puzzle = engine->getCurrentPuzzle(); //puzzle points to the current puzzle object

    value = elementQueue.front(); //holds the front element
    elementQueue.pop();//pop it


    int i = displayIndex; //Keeps track of which element number we are displaying
    //styling of puzzleDisplay
    ui->puzzleDisplay->setStyleSheet("background-color: rgba(0,0,0,0); border: none; color: white;");
    ui->puzzleDisplay->setAttribute(Qt::WA_TranslucentBackground);
    ui->puzzleDisplay->setAutoFillBackground(false);

    int boxWidth = 60, boxHeight = 50;
    QLabel* box = new QLabel(QString::number(value), ui->puzzleDisplay); //Creates a QLabel for the number.
    //QLabel shows the number and looks like a box (frame style, background color).
    //stackBox is used later to find & delete old boxes.
    box->setAlignment(Qt::AlignCenter);
    box->setFrameStyle(QFrame::Box | QFrame::Raised);
    box->setStyleSheet("background-color: lightblue; font: bold 16px;");
    box->setObjectName("stackBox");
    box->show();

    int xPos = 10, yPos = 10; //Initialize coordinates; exact placement depends on puzzle type

    if(dynamic_cast<StackPuzzle*>(puzzle)) {
        yPos = ui->puzzleDisplay->height() - (i + 1)*(boxHeight + 5); //Stack: vertical stack. First element at bottom, next on top
        xPos = 10;
    } else if(dynamic_cast<QueuePuzzle*>(puzzle) ||
               dynamic_cast<ArrayPuzzle*>(puzzle) ||
               dynamic_cast<LinkedListPuzzle*>(puzzle)) {
        xPos = 10 + i*(boxWidth + 10); //Queue, Array, Linked List: horizontal layout, left to right
        yPos = 10;
    } else if(dynamic_cast<BSTPuzzle*>(puzzle)) {
        int level = floor(log2(i+1));
        int indexInLevel = i - ((1 << level) - 1);
        int nodesInLevel = 1 << level;
        double slotWidth = (double)ui->puzzleDisplay->width() / nodesInLevel;
        xPos = slotWidth*indexInLevel + slotWidth/2 - boxWidth/2;
        yPos = 60 * level;
    } else if(dynamic_cast<HeapPuzzle*>(puzzle)) {
        int level = floor(log2(i+1));
        int indexInLevel = i - ((1 << level) - 1);
        int nodesInLevel = 1 << level;
        int totalWidth = ui->puzzleDisplay->width();
        int xSpacing = totalWidth / (nodesInLevel+1);
        xPos = xSpacing*(indexInLevel+1) - boxWidth/2;
        yPos = 60*level;
    }
    //Animate the box
    box->setGeometry(xPos, 0, boxWidth, boxHeight);
    QPropertyAnimation* anim = new QPropertyAnimation(box, "geometry");
    anim->setDuration(300);
    anim->setStartValue(QRect(xPos,0,boxWidth,boxHeight));
    anim->setEndValue(QRect(xPos,yPos,boxWidth,boxHeight));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    //Increment display index
    displayIndex++;
}


void MainWindow::animateHealthLoss(){
    if(!healthStack.empty()){
        QLabel* lost = healthStack.top();
        healthStack.pop();
        lost->deleteLater();
    }
}
//fade animation when new room loads
void MainWindow::animateRoomTransition(){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(ui->puzzleDisplay);
    ui->puzzleDisplay->setGraphicsEffect(effect);
    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(700);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *slide = new QPropertyAnimation(ui->puzzleDisplay, "geometry");
    slide->setDuration(700);
    slide->setStartValue(QRect(ui->puzzleDisplay->x(), -200, ui->puzzleDisplay->width(), ui->puzzleDisplay->height()));
    slide->setEndValue(ui->puzzleDisplay->geometry());
    slide->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::on_submitButton_clicked(){ //jab user ans submit kre
    QString userAnswer = ui->answerLineEdit->text(); //ans userans me store hua
    if(userAnswer.isEmpty()) return; //if ans empty submit,,kch nae hga

    bool correct = engine->submitAnswer(userAnswer.toStdString());//check if ans is correct
    if(!correct) animateHealthLoss();//if ans is wrong tw stack se ek heart pop hua

    if(engine->isGameOver()){
        QMessageBox::critical(this, "Game Over", "You lost all your health!");
        this->close();
        return;
    }

    if(engine->isLastRoom()){
        QMessageBox::information(this, "Victory",
                                 "You escaped the dungeon!\nCode Word: " + QString::fromStdString(engine->getCodeWord()));
        this->close();
        return;
    }

    ui->answerLineEdit->clear(); //input line clear
    loadRoom();//if wrong ans,,whi room reload hua, if correct new room load
}

void MainWindow::onKeyCollected() {
    QMessageBox::information(this, "Key Found!", "You collected the key! Health +1");
}
