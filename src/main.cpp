#include <QtGui/QApplication>
#include "MainWindow.h"
#include <Settings.h>
#include <QuickOpenDialog.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Krill Surfing Humpback Whales");
    a.setApplicationName("CaptainOates");
    a.setApplicationVersion("1.0");
    Settings s;
    MainWindow w;
    w.show();
    QuickOpenDialog qod;

    qod.setFileList(s.recentFiles());
    if(qod.exec() == QDialog::Accepted)
    {
        qDebug() << "Selected files are" << qod.selectedFiles();
    }

    return a.exec();
}
