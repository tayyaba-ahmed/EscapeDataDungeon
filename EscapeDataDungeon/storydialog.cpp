#include "StoryDialog.h"
#include <QVBoxLayout> // Used for arranging widgets vertically
#include <QHBoxLayout> // Used for arranging widgets horizontally
#include <QPropertyAnimation> //Provides fade-in/fade-out animations for labels/buttons
#include <QTimer> // Controls the loading progress bar updates over time
#include <QGraphicsDropShadowEffect> // Adds shadow effect to labels/buttons for better visibility
#include <QFontDatabase> //Allows loading and using custom fonts in the UI

// Constructor for the StoryDialog class
// Sets up the initial loading screen, story slides, buttons, and animations
// currentSlide(0) → Keeps track of which story slide is currently visible.
// loadingValue(0) → Progress bar value starts at 0.
StoryDialog::StoryDialog(QWidget *parent)
    : QDialog(parent), loadingValue(0)
{
    // Set fixed dialog size
    this->setFixedSize(650, 450);

    // Initial loading background image
    this->setStyleSheet(
        "QDialog {"
        "  background-image: url(:/images/main.jpeg);"
        "  background-repeat: no-repeat;"
        "  background-position: center;"
        "}"
        );

    // Main layout setup
    QVBoxLayout* mainLayout = new QVBoxLayout(this); //Main vertical layout for the dialog
    mainLayout->setContentsMargins(30, 30, 30, 30); //Padding around layout edges.

    QVBoxLayout* bottomLayout = new QVBoxLayout(); // bottom vertical layout to hold loading label, progress bar, and start button
    bottomLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter); //Aligns widgets to the bottom and center horizontally

    // slideLabel1 shows the loading message
    slideLabel1 = new QLabel("Loading the Data Dungeon...", this); //ui ke bajaye code me qlabel banrha
    slideLabel1->setAlignment(Qt::AlignCenter); //Aligns widget in the centre
    slideLabel1->setStyleSheet( //designing for slidelabel1
        "font-size: 20px;"
        "color: #ffffff;"
        "padding: 15px;"
        "border-radius: 15px;"
        );

    //Adds a soft black shadow behind the slidelabel1
    // means loading ka label zada clear dikhega
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);//control softness of shadow
    shadow->setColor(Qt::black);
    shadow->setOffset(0, 0); //shadow is directly behind the text
    slideLabel1->setGraphicsEffect(shadow);

    bottomLayout->addWidget(slideLabel1); //slidelabel1 ko bottomlayout me add kia hai taake it shows on bottom
    bottomLayout->addSpacing(25); //bottomlayout me jitne widgets he sabke bich 25px ka distance rkhta he
    // Loading bar setup
    loadingBar = new QProgressBar(this); //Creates a horizontal progress bar.
    loadingBar->setRange(0, 100); //Ranges from 0 to 100
    loadingBar->setValue(0);//Initial value 0.
    loadingBar->setTextVisible(true);
    loadingBar->setAlignment(Qt::AlignCenter);
    loadingBar->setFixedWidth(400); //Fixed width of 400 pixels
    loadingBar->setStyleSheet( //designing for loading bar
        "QProgressBar {"
        "  border: 2px solid #444;"
        "  border-radius: 12px;"
        "  height: 30px;"
        "  background: rgba(255,255,255,0.1);"
        "  text-align: center;"
        "}"
        //Gradient green fill for progress (chunk).
        "QProgressBar::chunk {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00ff88, stop:1 #00cc99);"
        "  border-radius: 12px;"
        "}"
        );
    bottomLayout->addWidget(loadingBar);//loading bar ko bottomlayout me add kia hai taake it shows on bottom

    // Start button setup (hidden initially)
    //Initially hidden, only shows after loading completes
    startButton = new QPushButton("Start Game", this); // creates a start button
    startButton->setFixedWidth(180); //fixed width of 180px
    startButton->setStyleSheet( //designing for startbutton
        "QPushButton {"
        "  background: #00cc99;"
        "  color: #fff;"
        "  font-weight: bold;"
        "  font-size: 16px;"
        "  padding: 8px;"
        "  border-radius: 12px;"
        "}"
        "QPushButton:hover {"
        "  background: #00ff88;"
        "}"
        );
    startButton->hide(); // hidden until loading completes
    bottomLayout->addWidget(startButton, 0, Qt::AlignHCenter); //loading bar ko bottomlayout me add kia hai taake it shows on bottom

    mainLayout->addLayout(bottomLayout); //bottomlayout ko mainlayout me add krdia

    // Story label setup (hidden initially)
    // slideLabel shows the story slides
    slideLabel = new QLabel(this); //ui ke bajaye code me qlabel banrha
    slideLabel->setAlignment(Qt::AlignCenter);//to align in center
    slideLabel->setStyleSheet( //designing for story label
        "font-size: 20px;"
        "color: #ffffff;"
        "font-weight: bold;"
        "padding: 15px;"
        "border-radius: 12px;"
        );
    slideLabel->hide();//hidden until user clicks start
    mainLayout->addWidget(slideLabel, 1, Qt::AlignCenter); //mainlayout me direct center me add kia

    // Next button setup (hidden initially)
    nextButton = new QPushButton("Next", this);  // creates a next button
    nextButton->setFixedWidth(120); //fixed width of 120px
    nextButton->setStyleSheet( //designing for next button
        "QPushButton {"
        "  background: #00cc99;"
        "  color: #fff;"
        "  font-weight: bold;"
        "  font-size: 16px;"
        "  padding: 8px;"
        "  border-radius: 12px;"
        "}"
        "QPushButton:hover {"
        "  background: #00ff88;"
        "}"
        );
    nextButton->hide(); //hidden until user clicks start
    mainLayout->addWidget(nextButton, 0, Qt::AlignCenter);//mainlayout me direct center me add kia

    // story slides text
    // slides ka queue he..usme 3no ko push krdia jo sbse pehli slide he wh sbsee pehle show hgi
    slideQueue.push(
        "You awaken in a dark, mysterious dungeon…<br>"
        "Surrounded by corrupted data and broken algorithms.<br>"
        "The malevolent AI, MAZD, has corrupted the kingdom’s data."
        );

    slideQueue.push(
        "<p align='justify'>Instructions:<br>"
        "To escape, you must navigate the dungeon room by room.<br>"
        "1) Each room hides a challenge: stacks, queues, arrays, heaps,<br> BSTs… and even a deadly trap.<br>"
        "2) You have only 3 lives—one mistake could cost you dearly.<br>"
        "3) Find the key to gain health but beware, there is only 1 key.<br>"
        "4) Pay attention to clues. A secret code word could be anywhere.<br>"
        "In Trap Room, you must enter the secret word to escape the dungeon.</p>"
        );

    slideQueue.push("The fate of the digital kingdom depends on you!");

    // Load custom fonts
    int fontId = QFontDatabase::addApplicationFont(":/fonts/F.otf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily);
    customFont.setPointSize(18);
    customFont.setBold(true);
    //inn sabka font custom hoga jo humne google se download kia hai
    slideLabel1->setFont(customFont);
    slideLabel->setFont(customFont);
    startButton->setFont(customFont);
    nextButton->setFont(customFont);

    // Fade effect for story label
    effect = new QGraphicsOpacityEffect(slideLabel);
    slideLabel->setGraphicsEffect(effect);
    effect->setOpacity(1.0);

    // Loading bar animation
    loadingTimer = new QTimer(this);
    connect(loadingTimer, &QTimer::timeout, this, [this]() {
        loadingValue++;
        loadingBar->setValue(loadingValue);

        if (loadingValue >= 100) {
            loadingTimer->stop();
            loadingBar->hide();

            slideLabel1->setText("Enter the game at your own risk...");
            startButton->show();
            startButton->setFocus(); //enter krne pr start button click hga

        }
    });
    loadingTimer->start(25); // update every 25ms

    // These are Qt signal-slot connections.
    //In Qt, signals are emitted when something happens (like a button click),
    // and slots are functions that respond to those signals.
    // Connect button signals to slots
    connect(startButton, &QPushButton::clicked, this, &StoryDialog::startStory); //QPushButton::clicked this is signal and in return
                                                                                 //startStory(slot) is the func that respond to that signal

    connect(nextButton, &QPushButton::clicked, this, &StoryDialog::showNextSlide);//QPushButton::clicked this is signal and in return
                                                                                  //shownNextSlide(slot) is the func that respond to that signal
}

// Destructor
StoryDialog::~StoryDialog() {}

// Start the story when Start button is clicked
// this is triggered when start button is clicked islye ek hi bar trigger hga
void StoryDialog::startStory()
{
    // Fade out the loading label
    QPropertyAnimation* fadeOutLabel = new QPropertyAnimation(slideLabel1->graphicsEffect(), "opacity");
    fadeOutLabel->setDuration(500);
    fadeOutLabel->setStartValue(1.0);
    fadeOutLabel->setEndValue(0.0);

    // Fade out the start button
    QGraphicsOpacityEffect* startEffect = new QGraphicsOpacityEffect(startButton);
    startButton->setGraphicsEffect(startEffect);
    startEffect->setOpacity(1.0);

    QPropertyAnimation* fadeOutButton = new QPropertyAnimation(startEffect, "opacity");
    fadeOutButton->setDuration(500);
    fadeOutButton->setStartValue(1.0);
    fadeOutButton->setEndValue(0.0);

    fadeOutLabel->start(QPropertyAnimation::DeleteWhenStopped);
    fadeOutButton->start(QPropertyAnimation::DeleteWhenStopped);

    // After fade-out completes, show first story slide
    connect(fadeOutLabel, &QPropertyAnimation::finished, [this]() {
        slideLabel1->hide();  // slidelabel1 hide hoga
        startButton->hide(); //start button hide hoga

        slideLabel->show();
        // agr slide queue empty nae he tw slide label pr uska front show krdo
        if (!slideQueue.empty()) {
            slideLabel->setText(slideQueue.front());
            slideQueue.pop(); // show krne k bd isy pop krdo taake 2nd slide ka text front pr ajye
        }
        // Set first slide background
        this->setStyleSheet(
            "QDialog {" //updating the designing for QDialog
            "background-image: url(:/images/main2.jpeg);"
            "background-repeat: no-repeat;"
            "background-position: center;"
            "}"
            );
        nextButton->show(); //next button show hga
        nextButton->setFocus(); //enter click krne pr ye bh click hojygea
    });
}


// Show next slide when Next button is clicked
// this is triggered when next button is clicked islye har slide k lie after 1st one ye trigger hga
void StoryDialog::showNextSlide()
{
    // Fade out current slide
    QPropertyAnimation* fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(500);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    connect(fadeOut, &QPropertyAnimation::finished, this, [this]() {
        // agr slidequeue empty hgya means all slides done tw Qdialog band hojyega

        if (slideQueue.empty()) {
            accept(); // All slides done
            return;
        }
        // else next slide jo ke front pr agayi hr usy show kro
        slideLabel->setText(slideQueue.front());
        slideQueue.pop();

        // Fade in the new slide
        QPropertyAnimation* fadeIn = new QPropertyAnimation(effect, "opacity");
        fadeIn->setDuration(500);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    });

    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}
