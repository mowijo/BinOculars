#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QStringList>

class Settings : public QSettings
{
public:
    Settings();
    ~Settings();

    QStringList recentFiles();
    void addRecentFile(const QString &file);
    void clearRecentFilesList();

    void setLastOpenBrowserDirectory(const QString &dir);
    QString lastOpenBrowserDirectory() const;


    QStringList commandHistoryFor(const QString &filename);
    void setCommandHistoryFor(const QString &filename, const QStringList &history);

private:
    Settings(const Settings &other);
    Settings& operator==(const Settings &other);
    class SettingsPrivate *d;
    friend class SettingsPrivate;
};



#endif // SETTINGS_H
