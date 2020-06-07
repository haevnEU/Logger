#include <QApplication>
#include "loggerhandler.h"
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    LoggerHandler::getLogger("Main")->logOn();
    Logger* log = LoggerHandler::getLogger("Main");

    log->log("Testing log with info", LogLevel::INFO);
    log->log("Testing log with WARN", LogLevel::WARN);
    log->log("Testing log with Debug", LogLevel::Debug);
    log->log("Testing log with ERROR", LogLevel::ERROR);
    log->log("Testing log with FATAL", LogLevel::FATAL);
    log->log("Testing log with info", LogLevel::INFO);



    LoggerHandler::getLogger("Main")->log("Testing log", LogLevel::FATAL);
    LoggerHandler::getLogger("Main")->exportHtml();
    LoggerHandler::getLogger("Main")->flush();
    return a.exec();
}
