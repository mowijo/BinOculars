#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    friend class TableViewPrivate;
    class TableViewPrivate *d;

};

#endif // TABLEVIEW_H
