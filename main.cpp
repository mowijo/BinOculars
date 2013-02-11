#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Morten Inc");
    a.setApplicationName("MORTEN");
    a.setApplicationVersion("1.0");
    MainWindow w;
    w.show();
    
    return a.exec();
}
