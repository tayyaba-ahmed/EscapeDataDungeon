#include "StoryDialog.h"
#include "MainWindow.h"
#include <QApplication>

// -------------------- Entry Point --------------------
// This is where the Qt application starts
int main(int argc, char *argv[])
{
    // Create a Qt application object, required for any Qt app
    QApplication a(argc, argv);

    // Show the introductory story/dialog before the main game window
    StoryDialog story;

    // exec() displays the dialog modally and waits for user action
    // If the user presses "OK" (Accepted), proceed to main window
    if (story.exec() == QDialog::Accepted) {
        MainWindow w;  // Create the main game window
        w.show();      // Display the main window
        return a.exec(); // Enter Qt's event loop to handle UI events
    }

    // If the story dialog was rejected or closed, exit the application
    return 0;
}
