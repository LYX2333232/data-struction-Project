#include "dialognew.h"
#include "ui_dialognew.h"

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);

    //一开始隐藏警告信息
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);

    //对话框标题
    this->setWindowTitle("新建表格");
}

DialogNew::~DialogNew()
{
    delete ui;
}

//确定与否按钮组
void DialogNew::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        check=true;
        close();
    }
    else
    {
        check=false;
        close();
    }
}

//行数输入
void DialogNew::on_RowInAll_textChanged(const QString &arg1)
{
    int num1=arg1.toInt();
    double num2=arg1.toDouble();
    //输入行数不为整数则显示警告信息
    if((double)num1!=num2)
    {
        ui->label_3->setVisible(true);
        row=0;
    }
    else
    {
        ui->label_3->setVisible(false);
        row=num1;
    }
}

//列数输入
void DialogNew::on_ColumnInAll_textChanged(const QString &arg1)
{
    int num1=arg1.toInt();
    double num2=arg1.toDouble();
    //输入行数不为整数则显示警告信息
    if((double)num1!=num2)
    {
        ui->label_4->setVisible(true);
        column=0;
    }
    else
    {
        ui->label_4->setVisible(false);
        column=num1;
    }
}
