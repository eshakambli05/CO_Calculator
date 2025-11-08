#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Sample data for testing
    Faculty faculty("Dr. John Doe", "john.doe@univ.edu", "Computer Science");
    Course course("CS101", "Data Structures");
    // Add more sample setup in MainWindow if needed

    MainWindow window;
    window.show();

    return app.exec();
}
