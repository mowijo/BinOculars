#ifndef DATABASESELECTOR_H
#define DATABASESELECTOR_H


#include <QEvent>
#include <QListWidget>
#include <QWidget>

/** The DatabaseSelector monitors events on the entire subtree of QWidgets under root. */

class DatabaseSelector : public QListWidget
{
    Q_OBJECT

public:
    DatabaseSelector(QWidget *root);

signals:
    void databaseIndexSelected(int index);

public slots:
    void setCurrentDatabaseIndex(int index);
    void setDatabaseList(const QStringList& list);

protected:
    bool eventFilter(QObject *obj, QEvent *event);


private:
    class DatabaseSelectorPrivate *d;
    friend class DatabaseSelectorPrivate;
};


#endif // DATABASESELECTOR_H
