#include "dialogstickup.h"
#include "ui_dialogstickup.h"

Dialogstickup::Dialogstickup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogstickup)
{
    ui->setupUi(this);

    //一开始隐藏警告信息
    ui->labelinformation->setVisible(false);
    //条件替换的选项框一开始也隐藏
    ui->groupBox->setVisible(false);
    ui->lineEdit->setVisible(false);
}

Dialogstickup::~Dialogstickup()
{
    delete ui;
}

//直接替换
void Dialogstickup::on_checkBoxstickup_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBoxif->setChecked(false);
        ui->checkBoxadd->setChecked(false);
        ui->checkBoxsub->setChecked(false);

        select=1;
        ui->labelinformation->setVisible(false);
    }
    else
    {
        select=0;
    }
}
//相加替换
void Dialogstickup::on_checkBoxadd_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBoxif->setChecked(false);
        ui->checkBoxstickup->setChecked(false);
        ui->checkBoxsub->setChecked(false);

        select=3;
        ui->labelinformation->setVisible(true);
    }
    else
    {
        select=0;
        ui->labelinformation->setVisible(false);
    }
}
//相减替换
void Dialogstickup::on_checkBoxsub_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBoxif->setChecked(false);
        ui->checkBoxadd->setChecked(false);
        ui->checkBoxstickup->setChecked(false);

        select=4;
        ui->labelinformation->setVisible(true);
    }
    else
    {
        select=0;
        ui->labelinformation->setVisible(false);
    }
}
//按条件替换
void Dialogstickup::on_checkBoxif_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBoxstickup->setChecked(false);
        ui->checkBoxadd->setChecked(false);
        ui->checkBoxsub->setChecked(false);

        select=2;
        ui->groupBox->setVisible(true);
    }
    else
    {
        select=0;
        ui->groupBox->setVisible(false);
    }
}

//确定是否进行粘贴
void Dialogstickup::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        yesorno=true;
        close();
    }
    else
    {
        yesorno=false;
        select=0;
        close();
    }
}

//条件替换中的用于比较的数值
void Dialogstickup::on_lineEdit_textChanged(const QString &arg1)
{
    num=arg1.toDouble();
}
//条件替换中的比较运算符选择
void Dialogstickup::on_comboBoxselect_currentIndexChanged(int index)
{
    select1=index;
}
//条件替换中的比较对象选择
void Dialogstickup::on_comboBoxnumorother_currentIndexChanged(int index)
{
    select2=index;
    //若比较对象选择的是于某个数值比较，则使数值输入框显示出来
    if(index==1) ui->lineEdit->setVisible(true);
    else ui->lineEdit->setVisible(false);
}
