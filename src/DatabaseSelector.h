#ifndef DATABASESELECTOR_H
#define DATABASESELECTOR_H

#include <QListView>

class DatabaseSelector : public QListView
{
    Q_OBJECT
public:
    explicit DatabaseSelector(QObject *parent = 0);
    
    void setCurrentDatabaseIndex(int index);

signals:
    void current
    
public slots:
    void selectNext();
    void selectPrevious();

private:
    class DatabaseSelectorPrivate *d;
};

#endif // DATABASESELECTOR_H
