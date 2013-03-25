#ifndef LOG_H
#define LOG_H

#include <QAbstractItemModel>
#include <QSqlQuery>

class Log : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = 0);
    
    QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    int	columnCount ( const QModelIndex & parent = QModelIndex() ) const ;
    QModelIndex	parent ( const QModelIndex & index ) const;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    bool wasSuccessfull(int row) const;
    bool isRowForErrorStatus(int row) const;

signals:
    void entryAdded(const QSqlQuery &query);

public slots:
    void addEntry(const QSqlQuery &query);


private:
   class LogPrivate *d;
   friend class LogPrivate;
};

#endif // LOG_H
