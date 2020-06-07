#include "fileio.h"

FileIO::FileIO() : QObject(){}

void FileIO::writeData( QString data, QString path){
    QFile file(path);


    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << data;

        file.close();
    }
}

void FileIO::appendData(QString data, QString path){
    QFile file(path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << data;
        file.close();
    }else{
        // TODO informat IO error
    }
}


QString FileIO::readData(QString path){
    QString str;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        str = stream.readAll();
        file.close();
    }else{
        // TODO informat IO error
    }

    return str;
}
