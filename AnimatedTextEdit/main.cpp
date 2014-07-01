
// main.cpp
#include <QtGui>
#include<QApplication>
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include "animatedTextEdit.h"
int main(int argc, char* argv[])
{
        QApplication app(argc, argv);
        Window window;
        window.show();
        return app.exec();
}
