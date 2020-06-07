/**
  * @file logger.h
  * @details This file handles the logging of application messages.
  * @author Nils Milewski (haevn)
  * @since 1.0.0.0
  */
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <QMap>
#include <QDateTime>
#include "fileio.h"
/**
  * @brief The LogLevel enum describes different logging level
  * @details This enum contains all possible logging level.
  *          It can be used to describe a log message or a
  *          required minimum logging level. <br>
  *          \p ALL enables logging for every level <br>
  *          \p Debug Used for debugging messages <br>
  *          \p INFO Used for information, like state changed etc. <br>
  *          \p WARN Used for none system critical events, e.g. Reconnect <br>
  *          \p ERROR Used for semi system critical events, e.g. Connection dropped <br>
  *          \p FATAL Used for system critical events, e.g. Not enough memory <br>
  *          \p Off Disables the logging
  * @author Nils Milewski (haevn)
  * @date 06/07/2020
  * @version 1.0.0.0
  * @since 1.0.0.0
 */
enum LogLevel{
    ALL = 0, Debug = 1, INFO = 2, WARN = 3, ERROR = 4, FATAL = 5, OFF = 10
};
/**
  * @brief The Logger class allows logging of some application message.
  * @details This class handles logging information from the application.
  *          Different log level are supported. This class should allways
  *          be access over loggerhandler#getLogger
  * @author Nils Milewski (haevn)
  * @date 06/07/2020
  * @version 1.0.0.0
  * @since 1.0.0.0
 */
class Logger : public QObject{

    Q_OBJECT

    const QString name = "Logging tool";
    const QString state = "Alpha";
    const QString version = "1.0.0.0";

    /**
     * @brief loggerName Name of the logger
     */
    QString loggerName;

    /**
     * @brief logging If true the logging is enabled
     */
    bool logging = false;

    /**
     * @brief entries Describes how many entries are allowed until the log is written to file
     */
    int entries = 100;

    /**
     * @brief logEntries Actual log entries
     */
    QStringList logEntries;

    /**
     * @brief write Writes the log into a file
     */
    void write();

    /**
     * @brief write Appends a log entry into the log list
     * @details This method will call @a logger::write if @p entries are exceed
     * @param message Message to append into the log list
     */
    void write(QString message);

    /**
     * @brief logLevelNames
     */
    QStringList logLevelNames;

    /**
     * @brief minimumRequiredLoggLevel This attribute is the required minium level to log the a message
     */
    LogLevel minimumRequiredLoggLevel = ALL;

    /**
     * @brief createHtmlCollapsibleItem Internal usage. Creates a html collapsible item
     * @param items Items which should be created inside the group
     * @param loggerName Name of the logger
     * @return HTML collapsible item
     */
    QString createHtmlCollapsibleItem(QStringList items, QString loggerName);

public:
    /**
     * @brief Logger CTOR
     * @param loggerName Name associtated with this logger
     */
    explicit Logger(QString loggerName);

    /**
     * @brief logOff Disables logging
     */
    void logOff();

    /**
     * @brief logOn Enable logging
     * @param intermidate If true the logger will immedialty write the entry into a text file
     */
    void logOn(bool intermidate = false);

    /**
     * @brief logOn Enable logging
     * @param level Describes the minium required log level for logging
     * @param intermidate If true the logger will immedialty write the entry into a text file
     */
    void logOn(LogLevel level, bool intermidate = false);

    /**
     * @brief setLogLevel Sets the required minimum log level
     * @param level New required log level minimum
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief setBuffer Sets the buffer for the loglist
     * @details This method overrides when the logger should be flushed.
     *          Calling this method will allways flush the logger.
     * @param entries Maximum entries
     */
    void setBuffer(int entries);

    /**
     * @brief flush Writes the logger to a file
     */
    void flush();

    /**
     * @brief log Logs a message
     * @param message Message which should be logged
     * @param level Level of the message, default is info
     */
    void log(QString message, LogLevel level = INFO);

    /**
     * @brief log Logs a message with given class name and line number
     * @param message Message which should be logged
     * @param className Name of the class where the log was called
     * @param line Line where the log was called
     * @param level Level of the log entry, default DEBUG
     * @deprecated 1.0.0.0
     */
    void log(QString message, QString className, int line, LogLevel level = Debug);

    /**
     * @brief exportHtml This method creates a html file as log
     */
    void exportHtml();

signals:

};


#endif // LOGGER_H
