#ifndef QUICKOPENDIALOG_H
#define QUICKOPENDIALOG_H

#include <QDialog>
#include <QStringList>

class QuickOpenDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QuickOpenDialog(QWidget *parent = 0);
    ~QuickOpenDialog();
    void setFileList(QStringList files);
    QStringList selectedFiles() const;
    bool shouldIgnoreNextTime() const;


protected:
    void keyPressEvent(QKeyEvent *);

private:
    class QuickOpenDialogPrivate *d;
};

#endif // QUICKOPENDIALOG_H
