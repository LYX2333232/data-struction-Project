#ifndef DIALOGSTICKUP_H
#define DIALOGSTICKUP_H

#include <QDialog>
#include "qpushbutton.h"
#include "qdebug.h"

namespace Ui {
class Dialogstickup;
}

class Dialogstickup : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogstickup(QWidget *parent = nullptr);
    ~Dialogstickup();

    int select=1;       //选择哪种粘贴方式
    int select1=0;      //条件替换中的比较运算符选择
    int select2=0;      //条件替换中的比较对象选择
    double num;         //条件替换中的比较数值
    bool yesorno=false;     //是否进行粘贴

private slots:
    void on_checkBoxstickup_toggled(bool checked);

    void on_checkBoxadd_toggled(bool checked);

    void on_checkBoxsub_toggled(bool checked);

    void on_checkBoxif_toggled(bool checked);

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBoxselect_currentIndexChanged(int index);

    void on_comboBoxnumorother_currentIndexChanged(int index);

private:
    Ui::Dialogstickup *ui;
};

#endif // DIALOGSTICKUP_H
