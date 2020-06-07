#ifndef WIDGET_H
#define WIDGET_H

#include <QTextEdit>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
    QString val;
    QString path;
    void createFiler();

    QStringList all;
    QStringList debug;
    QStringList info;
    QStringList warn;
    QStringList error;
    QStringList fatal;

    bool isHtml;
    QTextEdit* log;
    void setText(QStringList data);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

};
#endif // WIDGET_H
