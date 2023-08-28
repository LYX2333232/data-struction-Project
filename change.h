
#ifndef CHANGE_H
#define CHANGE_H


#include <QObject>
#include<QString>
#include<QColor>
#include<QFont>
#include<QDebug>
#include<QByteArray>
#include<QStringList>
#include<QTableWidget>

class Change : public QObject
{
    Q_OBJECT
public:
    explicit Change(QObject *parent = nullptr);

    char* deleteQuote(QString x);       //去除引号

    QString toString(QColor x);         //从QColor 转变为 QString
    QColor toQColor(QString x);         //从QByteArray 转变为 QColor
    QString toString(QFont x);          //从QFont 转变为 QString
    QFont toQFont(QString x);           //从QString 转变为 QFont

    bool isNum(QString x);              //判断字符串是否一个数值
signals:

};

#endif // CHANGE_H
