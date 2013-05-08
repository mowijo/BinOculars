#include "TestDataBaseProvider.h"
#include <QDir>
#include <QFile>


QString TestDataBaseProvider::createTestDataBaseOnDiskFromString(const QString &filename)
{
    static int i = 1;
    QString outfilename = QDir::tempPath()+"/BinOkularsDataBaseTest-number-"+QString::number(i++);
    temporaryfiles << outfilename;
    QFile out(outfilename);
    out.open(QFile::WriteOnly);

    QFile in(":/TestResources/Model/"+filename);
    in.open(QFile::ReadOnly);
    out.write(in.readAll());
    out.close();
    in.close();
    return outfilename;
}

TestDataBaseProvider::~TestDataBaseProvider()
{
    foreach(QString filename, temporaryfiles)
    {
        QFile::remove(filename);
    }
}
