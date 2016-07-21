#include "mainwindow.h"

#include <QApplication>
#include <QFileInfo>
#include <QDir>

void copyWebChannelJs() {
    // Copy dynamically the js file from the QT directory
    // due to its GPL2 license
    QFileInfo jsFileInfo(BUILD_DIR "/qwebchannel.js");
    if (!jsFileInfo.exists()
            && !QFile::copy(":/qtwebchannel/qwebchannel.js", jsFileInfo.absoluteFilePath())) {
        qFatal("Unabled to copy QT's webchannel to executable directory");
    }
}

int main(int argc, char *argv[])
{
    copyWebChannelJs();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
