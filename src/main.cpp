#include <QDebug>
#include <QtGui/QApplication>

#include <gui/MainWindow.h>
#include <gui/QuickOpenDialog.h>
#include <gui/Settings.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Captain Oates & the Krill Surfing Humpback Whales");
    a.setApplicationName("Binoculars");
    a.setApplicationVersion("1.0");
    Settings s;
    MainWindow w;
    w.show();


    if(s.recentFiles().count() > 0)
    {
        QuickOpenDialog qod;
        if(qod.shouldShow())
        {
            qod.setFileList(s.recentFiles());
            qod.exec();
            foreach(QString filename, qod.selectedFiles())
            {
                w.openFile(filename);
            }
        }
    }

    return a.exec();
}
