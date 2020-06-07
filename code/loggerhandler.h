/**
  * @file loggerhandler.h
  * @details This file contains a managed interaction for logging.
  * @author Nils Milewski (haevn)
  * @since 1.0.0.0
  */
#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include "logger.h"

#include <QMap>

/**
  * @brief LoggerHandler handles different loggers.
  * @details This class is used for a managed interaction between different logger.
  *          The handler is implemented as a singleton object, it is not required to delete
  *          the object.
  *          A new logger can be called from a static call to getLogger(String).
  *          It will return a pointer to the logger or creates a new one.
  *          If the application quits all acuired logger will be flushed and save into a file.
  *          This class also frees used resources.
  * @author Nils Milewski (haevn)
  * @date 06/07/2020
  * @version 1.0.0.0
  * @since 1.0.0.0
 */
class LoggerHandler{

private:

    /**
     * @brief loggers This map contains all created logger
     */
    QMap<QString, Logger*> loggers;

    /**
     * @brief LoggerHandler CTOR
     */
    LoggerHandler(){}

    /**
     * @brief getInstance This returns a refference to the only existing object.
     * @details This method creates a new instance if none exists and return a
     *          reference to the previous created instance. If an instance allready
     *          exists the reference will be returned
     * @return Reference to the only existing instance
     */
    static LoggerHandler& getInstance(){
        static LoggerHandler instance;
        return instance;
    }

public:

    /**
     * @brief getLogger This static method returns a logger
     * @details If a logger asociated with \p name exists a pointer to the instance
     *          will be returned. If theres no instance associated with \p name a new
     *          one will be created and returned.
     * @param name Name of the logger
     * @return Pointer to a logger associtated with \p name
     */
    static Logger* getLogger(QString name){

        LoggerHandler& handler = getInstance();

        if(!handler.loggers.contains(name)){
            handler.loggers.insert(name, new Logger(name));
        }
        return handler.loggers[name];
    }

    ~LoggerHandler(){
        for(QString key : loggers.keys()){
            loggers[key]->flush();
            delete(loggers[key]);
            loggers.remove(key);
        }
    }

};
#endif // LOGGERHANDLER_H
