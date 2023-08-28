#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>
#include <QMessageBox>
#include "change.h"
#include "qpushbutton.h"

namespace Ui {
class DialogNew;
}

class DialogNew : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNew(QWidget *parent = nullptr);

    int row;        //返回输入的行数
    int column;     //返回输入的列数
    bool check;     //判断选择了哪个按钮

    ~DialogNew();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_RowInAll_textChanged(const QString &arg1);

    void on_ColumnInAll_textChanged(const QString &arg1);

private:
    Ui::DialogNew *ui;
};

#endif // DIALOGNEW_H
