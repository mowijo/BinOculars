#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

namespace Gui
{


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

} //namespace Gui

#endif // TABLEVIEW_H
