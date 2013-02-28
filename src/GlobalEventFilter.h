#ifndef GLOBALEVENTFILTER_H
#define GLOBALEVENTFILTER_H


#include <QEvent>
#include <QListWidget>
#include <QWidget>

/** The GlobalEventFilter monitors events on the entire subtree of QWidgets under root.

@note The GlobalEventFilter instance is automatically deleted along with the QWidget being tracked. */

class GlobalEventFilter : public QListWidget
{
    Q_OBJECT

public:
    GlobalEventFilter(QWidget *root);

signals:
    void triggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event);


private:
    class GlobalEventFilterPrivate *d;
};


#endif // GLOBALEVENTFILTER_H
