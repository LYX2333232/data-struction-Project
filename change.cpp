
#include "change.h"

Change::Change(QObject *parent)
    : QObject{parent}
{

}

//去除引号
char* Change::deleteQuote(QString x)
{
    return x.toUtf8().data();
}

//从Qcolor 转变为 Qstring 以 r,g,b,Hue,Sat,Val,Alpha 格式
QString Change::toString(QColor x)
{
    QString result="";
    result+=QString::number(x.red())+","+QString::number(x.green())+","+QString::number(x.blue())+","+QString::number(x.hue())+","+QString::number(x.saturation())+","+QString::number(x.value())+","+QString::number(x.alpha())+"\n";
    return result;
}

//从QString 转变为 QColor
QColor Change::toQColor(QString x)
{
    QColor result;
    QStringList color=x.split(',');
    int r=color.at(0).toInt();
    int g=color.at(1).toInt();
    int b=color.at(2).toInt();
    int Hue=color.at(3).toInt();
    int Sat=color.at(4).toInt();
    int Val=color.at(5).toInt();
    int a=color.at(6).toInt();
    result.setRed(r);
    result.setGreen(g);
    result.setBlue(b);
    result.setHsv(Hue,Sat,Val,a);
    return result;
}

//从QFont 转变为 QString 以 字体类型，字体大小，是否加粗，是否倾斜，是否有下划线 的格式
QString Change::toString(QFont x)
{
    QString result="";
    result+=x.family();//记录字体类型
    result+=",";
    result+=QString::number(x.pointSize());//记录字体大小
    result+=",";

    if(x.bold())
        result+="1";
    else result+="0";//记录是否加粗
    result+=",";
    if(x.italic())
        result+="1";
    else result+="0";//记录是否倾斜
    result+=",";
    if(x.underline())
        result+="1";
    else result+="0";//记录是否有下划线
    result+="\n";
    return result;
}

//从QString 转变为 QFont
QFont Change::toQFont(QString x)
{
    QFont result;
    QString family;//字体类型
    int psize;//字体大小
    bool bold;//是否加粗
    bool italic;//是否倾斜
    bool under;//是否有下划线

    QStringList R=x.split(",");
    family=R.at(0);//字体类型
    psize=R.at(1).toInt();//字体大小
    if(R.at(2)=="1")bold=true;//加粗
    else bold=false;
    if(R.at(3)=="1")italic=true;//倾斜
    else italic=false;
    if(R.at(4)=="1")under=true;//下划线
    else under=false;

    result.setFamily(family);
    result.setPointSize(psize);
    result.setBold(bold);
    result.setItalic(italic);
    result.setUnderline(under);
    return result;
}

//判断字符串是否表示一个数值
bool Change::isNum(QString x)
{
    if(x.size()==0) return false;
    int have=0;
    for(int i=0;i<x.size();i++)
    {
        if(x[i].isDigit())
        {
            continue;
        }
        else if(x[i]=='.')
        {
            have++;
            if(have>1) return false;
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
