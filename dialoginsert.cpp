#include "dialoginsert.h"
#include "ui_dialoginsert.h"

DialogInsert::DialogInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInsert)
{
    ui->setupUi(this);

    //一开始隐藏警告信息
    ui->label_2->setVisible(false);
    //初始化各类参数
    num=0;
    way=false;
    yesorno=false;
    //对话框标题
    this->setWindowTitle("插入...");
}

DialogInsert::~DialogInsert()
{
    delete ui;
}

//way为false表示插入位置在表尾
void DialogInsert::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        way=false;
        ui->checkBox_2->setChecked(false);
    }
}

//way为true表示插入位置在当前选中的单元格的行或列之后
void DialogInsert::on_checkBox_2_toggled(bool checked)
{
    if(checked)
    {
        way=true;
        ui->checkBox->setChecked(false);
    }
}

//插入数目输入
void DialogInsert::on_lineEdit_textChanged(const QString &arg1)
{
    int num1=arg1.toInt();
    double num2=arg1.toDouble();
    //一旦输入的数目不为整数，则显示警告信息
    if((double)num1!=num2)
    {
        ui->label_2->setVisible(true);
        num=0;
    }
    else
    {
        ui->label_2->setVisible(false);
        num=num1;
    }
}

//是否确认要插入按钮
void DialogInsert::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        yesorno=true;
        close();
    }
    else
    {
        yesorno=false;
        close();
    }
}
