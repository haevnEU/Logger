#include "logger.h"

Logger::Logger(QString name) : QObject(nullptr){
    this->loggerName = name;
    logLevelNames.append("ALL");
    logLevelNames.append("Debug");
    logLevelNames.append("INFO");
    logLevelNames.append("WARN");
    logLevelNames.append("ERROR");
    logLevelNames.append("FATAL");
}

void Logger::exportHtml(){

    FileIO& fileHandler = FileIO::getInstance();

    QString path = fileHandler.logPath();
    path.append("/").append(loggerName).append(".html");
    QString in = fileHandler.readData(path);
    QString out = "";
    QStringList tags = in.split("\n");
    QStringList oldEntries;
    for(QString tag : tags){
        if(tag.contains("<p")){
            oldEntries.append(tag.replace("\t", ""));
        }
    }

    out.append("<!DOCTYPE html>\n");
    out.append("<html>\n");
    out.append("\t<head>\n");
    out.append("\t\t<title>Log of ").append(loggerName).append("</title>\n");
    out.append("\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
    out.append("\t\t<style>\n");
    out.append("\t\t\tp{font-family: \"Source Code Pro\", Arial;color: White}\n");
    out.append("\t\t\th1{font-family: \"Source Code Pro\", Arial;color: White}\n");
    out.append("\t\t\tbody{background-color: #16131c}\n");
    out.append("\t\t\t.info{color: Green;; font-size: 18px;}\n");
    out.append("\t\t\t.debug{color: Blue;; font-size: 18px;}\n");
    out.append("\t\t\t.warning{color: Yellow;; font-size: 18px;}\n");
    out.append("\t\t\t.error{color: Tomato;; font-size: 18px;}\n");
    out.append("\t\t\t.fatal{color: Red;; font-size: 18px;}\n");
    out.append("\t\t\t.warning{color: Yellow;}\n");
    out.append("\t\t\t.collapsible { background-color: #25252e;  color: white; cursor: pointer; padding: 18px; width: 100%; border: none; text-align: left; outline: none; font-size: 15px; }\n");
    out.append("\t\t\t.active, .collapsible:hover { background-color: #0b0b12; }\n");
    out.append("\t\t\t.content { padding: 0 18px; display: none; overflow: hidden; background-color: #272733; }\n");
    out.append("\t\t</style>\n");
    out.append("\t</head>\n\t<body>\n");
    out.append("\t\t<h1>Module Log file of : ").append(loggerName).append("</h1>");


    QString color;
    QStringList entries2;
    for(QString log : logEntries){
        if(log.contains("INFO")){
            color = "info";
        }else if(log.contains("DEBUG")){
            color = "debug";
        }else if(log.contains("WARN")){
            color = "warning";
        }else if(log.contains("ERROR")){
            color = "error";
        }else if(log.contains("FATAL")){
            color = "fatal";
        }else if(log.contains("ALL")){
            color = "White";
        }
        entries2.append(QString("<p class=\"").append(color).append("\">").append(log).append("</p>"));
    }

    QStringList fatalEntries;
    QStringList errorEntries;
    QStringList warnEntries;
    QStringList debugEntries;
    QStringList infoEntries;

    QStringList allEntries;

    for(QString entry : oldEntries){
        if(entry.contains("INFO")){
            infoEntries.append(entry);
        }else if(entry.toUpper().contains("DEBUG")){
            debugEntries.append(entry);
        }else if(entry.toUpper().contains("WARN")){
            warnEntries.append(entry);
        }else if(entry.toUpper().contains("ERROR")){
            errorEntries.append(entry);
        }else if(entry.toUpper().contains("FATAL")){
            fatalEntries.append(entry);
        }
    }

    for(QString entry : entries2){

        QStringList tmp = entry.split(":")[0].split("][");
        ulong time = tmp[1].replace("[","").replace("]", "").toULong();
        QDateTime time2 = time2.fromSecsSinceEpoch(time);
        QString tm = time2.toString("ddd MMMM/dd/yyyy-hh:mm:ss AP");
        entry.replace(QString::number(time), tm);
        if(entry.contains("INFO")){
            infoEntries.append(entry);
        }else if(entry.toUpper().contains("DEBUG")){
            debugEntries.append(entry);
        }else if(entry.toUpper().contains("WARN")){
            warnEntries.append(entry);
        }else if(entry.toUpper().contains("ERROR")){
            errorEntries.append(entry);
        }else if(entry.toUpper().contains("FATAL")){
            fatalEntries.append(entry);
        }
    }


    QString info = createHtmlCollapsibleItem(infoEntries, "Info");
    QString debug = createHtmlCollapsibleItem(debugEntries, "Debug");
    QString warn = createHtmlCollapsibleItem(warnEntries, "Warn");
    QString error = createHtmlCollapsibleItem(errorEntries, "Error");
    QString fatal = createHtmlCollapsibleItem(fatalEntries, "Fatal");
    QString all = createHtmlCollapsibleItem(allEntries, "All");
    out = out.append("\n");
    out = out.append(info).append("\n");
    out = out.append(warn).append("\n");
    out = out.append(fatal).append("\n");
    out = out.append(error).append("\n");
    out = out.append(debug).append("\n");

    out.append("<br>\n");
    out.append("<br>\n");
    out.append("<p>Created with ").append(name).append(" ").append(state).append(" ").append(version).append("</p>\n");
    out.append("<p>Log buil time: ").append(QDateTime::currentDateTime().toString("ddd MMMM/dd/yyyy-hh:mm:ss AP")).append("</p>\n\n");
    out.append("<p>This tool is available under the <a href= "">MIT</a> license</p>\n");
    out.append("<p>Visit the <a href = "">Repository</a> to clone the project</p>\n");
    out.append("\t\t<script>\n");
    out.append("\t\t\tvar coll = document.getElementsByClassName(\"collapsible\");var i;for (i = 0; i < coll.length; i++) { coll[i].addEventListener(\"click\", function() { this.classList.toggle(\"active\");  var content = this.nextElementSibling; if (content.style.display === \"block\") { content.style.display = \"none\";} else {content.style.display = \"block\";}});}");
    out.append("\n\t\t</script>\n");
    out.append("\t</body>\n</html>");


    fileHandler.writeData(out, path);
    logEntries.clear();
}

QString Logger::createHtmlCollapsibleItem(QStringList items, QString name){
    QString result = "";

    result.append("\t\t\t<button type=\"button\" class=\"collapsible\">").append(name).append(" [Total entries: ").append(QString::number(items.size())).append("]"
                                                                                                                                                                "</button>\n");
    result.append("\t\t\t<div class=\"content\">\n");
    for(QString item : items){
        result.append("\t\t\t\t").append(item).append("\n");
    }
    result.append("\t\t\t</div>");

    return  result;
}

void Logger::write(){

    FileIO& fileHandler = FileIO::getInstance();
    QString str;
    for(QString log : logEntries){
        str.append(log).append("\n");
    }
    QString path = fileHandler.logPath();
    path.append("/").append(loggerName).append(".log");
    fileHandler.appendData(str, path);
    exportHtml();
    logEntries.clear();
}

void Logger::write(QString message){
    logEntries.append(message);

    if(entries < logEntries.size()){
        write();
    }
}

void Logger::setBuffer(int entries){
    this->entries = entries;
    write();
}

void Logger::log(QString message, LogLevel level){
    if(!logging){
        return;
    }
    if(level < minimumRequiredLoggLevel){
        return;
    }
    QString tmpMessage = "[" + logLevelNames[level];
    tmpMessage += "]";
    uint timestamp = QDateTime::currentDateTime().toTime_t();
    tmpMessage.append("[").append(QString::number(timestamp)).append("]:");
    tmpMessage.append(message);
    write(tmpMessage);
}

void Logger::log(QString message, QString className, int line, LogLevel level){
    if(!logging){
        return;
    }
    if(level < minimumRequiredLoggLevel){
        return;
    }
    QString tmpMessage = "[" + logLevelNames[level];
    tmpMessage += "]";
    tmpMessage.append("[").append(className);
    tmpMessage.append("][").append(QString::number(line));
    uint timestamp = QDateTime::currentDateTime().toTime_t();
    tmpMessage.append("][").append(QString::number(timestamp)).append("]:");
    tmpMessage.append(message);
    write();
}


void Logger::logOff(){
    logging = false;
}

void Logger::logOn(bool intermidate){
    logging = true;
    if(intermidate){
        setBuffer(0);
    }
}

void Logger::logOn(LogLevel level, bool intermidate){
    logging = true;
    setLogLevel(level);
    if(intermidate){
        setBuffer(0);
    }
}

void Logger::setLogLevel(LogLevel level){
    minimumRequiredLoggLevel = level;
}

void Logger::flush(){
    int e = entries;
    setBuffer(0);
    write();
    setBuffer(e);
}
