#include "Settings.h"

#include <QSet>
#include <QString>
#include <QDebug>

class SettingsPrivate
{
private:
    Settings *p;

public:
    QSet<QString> recentfiles;
    bool recentfilesloaded;

    SettingsPrivate(Settings *p)
    {
        this->p = p;
        recentfilesloaded = false;
    }

    void loadRecentFiles()
    {
        if(recentfilesloaded) return;
        recentfiles = QSet<QString>::fromList(p->value("RecentFiles").toStringList());
        recentfilesloaded = true;
    }
};

Settings::Settings()
{
    d = new SettingsPrivate(this);

}

Settings::~Settings()
{
    delete d;
}

QStringList Settings::recentFiles()
{
    d->loadRecentFiles();
    return d->recentfiles.toList();
}

void Settings::addRecentFile(const QString &file)
{
    d->loadRecentFiles();
    if(d->recentfiles.contains(file)) return;
    d->recentfiles << file;
    setValue("RecentFiles", QVariant(d->recentfiles.toList()));
}

void Settings::clearRecentFilesList()
{
    d->recentfilesloaded = true;
    d->recentfiles.clear();
    setValue("RecentFiles", QVariant(d->recentfiles.toList()));
}

void Settings::setLastOpenBrowserDirectory(const QString &dir)
{
    setValue("LastOpendFileDir", QVariant(dir));
}

QString Settings::lastOpenBrowserDirectory() const
{
    return value("LastOpendFileDir", "").toString();
}

QStringList Settings::commandHistoryFor(const QString &filename)
{
    QStringList history;
    beginGroup("CommandHistories");
    if(contains(filename))
    {
        QVariant v = value(filename, QStringList());
        if(v.canConvert(QVariant::StringList)) history = v.toStringList();
    }
    endGroup();
    return history;
}

void Settings::setCommandHistoryFor(const QString &filename, const QStringList &history)
{
    beginGroup("CommandHistories");
    setValue(filename, history);
    endGroup();
}
