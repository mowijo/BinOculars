#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QTreeView>

class LogView : public QTreeView
{
    Q_OBJECT
public:
    explicit LogView(QWidget *parent = 0);
    ~LogView(   );
    
protected:
    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *);

private:
    class LogViewPrivate *d;
};

#endif // LOGVIEW_H
