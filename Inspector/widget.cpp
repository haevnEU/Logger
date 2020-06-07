#include "widget.h"

#include <QTextEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QRadioButton>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent){

    QPalette pal = this->palette();

    pal.setColor(QPalette::Base, QColor(0, 0, 204, (255 * 0.25)));
    pal.setColor(QPalette::Window, QColor(102, 0, 204, (255 * 0.1)));
    pal.setColor(QPalette::Text, Qt::white);
    pal.setColor(QPalette::WindowText, Qt::white);

    this->setPalette(pal);
    QGridLayout* layout = new QGridLayout(this);
    QVBoxLayout* l = new QVBoxLayout(this);
    QPushButton* btLoadLog = new QPushButton("Open Log");

    QPushButton* btRefresh = new QPushButton("Refresh Log");

    log = new QTextEdit(this);
    log->setPlaceholderText("Open a log");
    log->setFontWeight(16);
    QRadioButton* rbAll = new QRadioButton("All", this);
    QRadioButton* rbDebug = new QRadioButton("Debug", this);
    QRadioButton* rbInfo = new QRadioButton("Info", this);
    QRadioButton* rbWarn = new QRadioButton("Warn", this);
    QRadioButton* rbError = new QRadioButton("Error", this);
    QRadioButton* rbFatal = new QRadioButton("Fatal", this);

    l->addWidget(btLoadLog);
    l->addWidget(btRefresh);
    l->addWidget(rbAll);
    l->addWidget(rbDebug);
    l->addWidget(rbInfo);
    l->addWidget(rbWarn);
    l->addWidget(rbError);
    l->addWidget(rbFatal);
    layout->addLayout(l, 0, 0);
    layout->addWidget(log, 0, 1, 7, 1);

    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(rbAll);
    group->addButton(rbDebug);
    group->addButton(rbInfo);
    group->addButton(rbWarn);
    group->addButton(rbError);
    group->addButton(rbFatal);
    log->setReadOnly(true);

    setLayout(layout);
    connect(rbAll, &QRadioButton::clicked, this, [=](bool ignored){
        setText(val.split("\n"));
        log->setPlaceholderText("Empty logfile");
    });

    connect(rbDebug, &QRadioButton::clicked, this, [=](bool ignored){
        setText(debug);
        log->setPlaceholderText("No debug entries found");
    });

    connect(rbInfo, &QRadioButton::clicked, this, [=](bool ignored){
        setText(info);
        log->setPlaceholderText("No info entries found");
    });

    connect(rbWarn, &QRadioButton::clicked, this, [=](bool ignored){
        setText(warn);
        log->setPlaceholderText("No warning entries found");
    });

    connect(rbError, &QRadioButton::clicked, this, [=](bool ignored){
        setText(error);
        log->setPlaceholderText("No error entries found");
    });

    connect(rbFatal, &QRadioButton::clicked, this, [=](bool ignored){
        setText(fatal);
        log->setPlaceholderText("No fatal entries found");
    });

    connect(btLoadLog, &QPushButton::clicked, this, [=](bool ignored){
        QFile file;
        path =  QFileDialog::getOpenFileName(this, tr("Open log file"), "C:\\ProgramData\\HexEditor\\logs", tr("log file (*.log);; log file (*html)"));;
        val ="";
        file.setFileName(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
           while (!in.atEnd()){
               val += in.readLine().append('\n') ;
           }
           file.close();

           if(path.endsWith(".html") || path.endsWith(".html")){
               isHtml = true;
           }else{
               isHtml = false;
           }
           rbAll->setChecked(true);
           rbAll->clicked();
        }
        createFiler();
    });


    connect(btRefresh, &QPushButton::clicked, this, [=](bool ignored){
        QFile file;
        val ="";
        if(path == ""){
            return;
        }
        file.setFileName(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream in(&file);
           while (!in.atEnd()){
               val += in.readLine().append('\n') ;
           }
           file.close();
        }
        createFiler();
    });

    setMinimumSize(750, 500);
    showMaximized();
}

void Widget::createFiler(){
    QStringList vals = val.split('\n');
    all.clear();
    debug.clear();
    info.clear();
    warn.clear();
    error.clear();
    fatal.clear();
    for(QString line : vals){
        if(line.toLower().contains("all")){
            all.append(line.replace("[ALL]","").replace("[All]", "").replace("[all]", ""));
        }else if(line.toLower().contains("debug")){
            debug.append(line.replace("[DEBUG]","").replace("[Debug]", "").replace("[debug]", ""));
        }else if(line.toLower().contains("info")){
            info.append(line.replace("[INFO]","").replace("[Info]", "").replace("[info]", ""));
        }else if(line.toLower().contains("warn")){
            warn.append(line.replace("[WARN]","").replace("[Warn]", "").replace("[warn]", ""));
        }else if(line.toLower().contains("error")){
            error.append(line.replace("[ERROR]","").replace("[Error]", "").replace("[error]", ""));
        }else if(line.toLower().contains("fatal")){
            fatal.append(line.replace("[FATAL]","").replace("[Fatal]", "").replace("[fatal]", ""));
        }
    }
}

void Widget::setText(QStringList data){
    log->clear();

    if(isHtml){
        QString data2 ="";
        for(QString line : data){
            data2 += line;
            data2 += "\n";
        }

        log->setHtml(data2);
    }else{
        for(QString line : data){
             log->append(line);
        }
    }
    QTextCursor cursor =log->textCursor();
   log->selectAll();
   log->setFontPointSize(14);
   log->setTextCursor( cursor );
}
Widget::~Widget()
{
}

