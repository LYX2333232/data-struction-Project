#ifndef DIALOGINSERT_H
#define DIALOGINSERT_H

#include <QDialog>
#include "qdialogbuttonbox.h"
#include "qpushbutton.h"

namespace Ui {
class DialogInsert;
}

class DialogInsert : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInsert(QWidget *parent = nullptr);
    ~DialogInsert();

    int num;        //插入的数目
    bool yesorno;   //是否确认
    bool way;       //插入的位置

private slots:
    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogInsert *ui;
};

#endif // DIALOGINSERT_H
