#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QCoreApplication>

#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

class FileIO : public QObject{
    Q_OBJECT

    FileIO();
public:
    static FileIO& getInstance(){
        static FileIO instance;
        return instance;
    }

    static QString rootPath(){
        QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
        locations.removeOne(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        locations.removeOne(QCoreApplication::applicationDirPath());
        locations.removeOne(QCoreApplication::applicationDirPath() + QLatin1String("/data"));
        return locations[0];
    }

    static QString desktopPath(){
        return QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0];
    }

    static QString logPath(){
        return rootPath().append("/logs");
    }

    static QString addonPath(){
        return rootPath().append("/addons");
    }

    static QString tmpPath(){
        return rootPath().append("/tmp");
    }

    void writeData(QString path, QString data);

    void appendData(QString path, QString data);

    QString readData(QString path);
};

#endif // FILEIO_H
