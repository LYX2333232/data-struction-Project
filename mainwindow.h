#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlabel.h"
#include "QTableWidgetSelectionRange"
#include "dialoginsert.h"
#include "qclipboard.h"
#include "dialognew.h"
#include "change.h"
#include "dialogstickup.h"
#include <QFileDialog>
#include "qstring.h"
#include "qinputdialog.h"
#include <cmath>
#include <ctime>
#include <QVector>
#include <QMenu>
#include <QAction>
#include <bits/stdc++.h>
#include <QStack>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //状态栏参数
    QLabel* tableRow;
    QLabel* tableColumn;
    //状态栏更新函数
    void updataStatusBar();

    //默认字体样式与主题颜色
    QFont* defaultfont;
    QColor* defaultcolor;
    QColor* defaulttheme;

    //打开的文件路径
    QString url="";

    //表格初始化函数
    void init();

    //判断公式数组
    int **isFunction;
    //记录公式内容数组
    QString **Functions;

private slots:
    void on_fontTypeBox_currentFontChanged(const QFont &f);

    void on_fontSizeBox_valueChanged(int arg1);

    void on_checkBoxBold_toggled(bool checked);

    void on_checkBoxItalics_toggled(bool checked);

    void on_checkBoxUnderline_toggled(bool checked);

    void on_pushButtonFontColor_clicked();

    void on_pushButtonThemeColor_clicked();

    void on_pushButtonLeft_toggled(bool checked);

    void on_pushButtonCenter_toggled(bool checked);

    void on_pushButtonRight_toggled(bool checked);

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButtonWordwrap_toggled(bool checked);

    void on_pushButtonRowInsert_clicked();

    void on_pushButtonColumnInsert_clicked();

    void on_pushButtonRowDelete_clicked();

    void on_pushButtonColumnDelete_clicked();

    void on_pushButtonTableDelete_clicked();

    void on_pushButtonCopy_clicked();

    void on_pushButtonPaste_clicked();

    void on_pushButtonNew_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonSaveAs_clicked();

    void on_pushButtonOpen_clicked();


    void on_pushButtonAllSearch_clicked();

    void on_pushButtonRowSearch_clicked();

    void on_pushButtonColumnSearch_clicked();

    void on_pushButtonBlockSearch_clicked();

    void on_pushButtonColumnSort1_clicked();

    void on_pushButtonColumnSort2_clicked();

    void on_pushButtonRowSort1_clicked();

    void on_pushButtonRowSort2_clicked();

    void on_pushButtonSum_clicked();

    void on_pushButtonAvg_clicked();

    void on_pushButtonMax_clicked();

    void on_pushButtonMin_clicked();

    void on_pushButtonFuntion_clicked();

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    int Priority(QString data);

    int mask_data(QString expression, QString *mask_buffer);

    int re_polish(QString *mask_buffer,QString *repolish,int length);

    double repolish_calculat(QString *repolish,int length);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
