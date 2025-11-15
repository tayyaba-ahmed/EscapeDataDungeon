#ifndef STORYDIALOG_H
#define STORYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <queue>
#include <QString>
using namespace std;

class StoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StoryDialog(QWidget *parent = nullptr);
    ~StoryDialog();

private slots:
    void startStory();      // Triggered when Start button is clicked
    void showNextSlide();   // Triggered when Next button is clicked

private:
    // Loading screen
    QProgressBar* loadingBar;
    QTimer* loadingTimer;
    int loadingValue;

    // Story slides
    QLabel* slideLabel;     // Displays story slides
    QLabel* slideLabel1;    // Loading label
    queue<QString> slideQueue;

    // Buttons
    QPushButton* startButton;
    QPushButton* nextButton;

    // Fade effects
    QGraphicsOpacityEffect* effect;         // For slideLabel
    QGraphicsOpacityEffect* buttonEffect;   // For startButton
    QGraphicsOpacityEffect* loadingEffect;  // Optional, for loading animation
};

#endif
