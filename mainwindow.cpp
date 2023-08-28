#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcolordialog.h"
#include "qdebug.h"
#include "qframe.h"
#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //默认窗口大小
    this->resize(1600,800);

    //窗口标题
    this->setWindowTitle("电子表格");

    //状态栏参数初始化
    tableRow=new QLabel(" 行："+QString::number(ui->tableWidget->rowCount(),10)+"  ",this);
    tableColumn=new QLabel(" 列："+QString::number(ui->tableWidget->columnCount(),10)+"  ",this);
    ui->statusBar->addWidget(tableRow);
    ui->statusBar->addWidget(tableColumn);

    //默认字体样式和主题颜色初始化
    defaultfont=new QFont("微软雅黑",9);
    defaultcolor=new QColor(0,0,0);
    defaulttheme=new QColor(255,255,255);

    //保存和另存为按钮初始化为不可点击
    ui->pushButtonSave->setDisabled(true);
    ui->pushButtonSaveAs->setDisabled(true);

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//状态栏行列显示更新函数
void MainWindow::updataStatusBar()
{
    tableRow->setText(" 行："+QString::number(ui->tableWidget->rowCount(),10)+"  ");
    tableColumn->setText(" 列："+QString::number(ui->tableWidget->columnCount(),10)+"  ");
}

//表格初始化函数
void MainWindow::init()
{
    int row=ui->tableWidget->rowCount();
    int column=ui->tableWidget->columnCount();

    isFunction=new int*[ui->tableWidget->rowCount()];
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        isFunction[i]=new int[ui->tableWidget->columnCount()];
    }
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->rowCount();j++)
        {
            isFunction[i][j]=0;
        }
    }

    Functions=new QString*[ui->tableWidget->rowCount()];
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        Functions[i]=new QString[ui->tableWidget->columnCount()];
    }
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            //为每个单元格创建item对象并赋予默认的内容、字体、颜色
            if(ui->tableWidget->item(i,j)==nullptr)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
                ui->tableWidget->item(i,j)->setFont(*defaultfont);
                ui->tableWidget->item(i,j)->setTextColor(*defaultcolor);
                ui->tableWidget->item(i,j)->setBackgroundColor(*defaulttheme);
            }
        }
}


//单元格字体样式
void MainWindow::on_fontTypeBox_currentFontChanged(const QFont &f)
{
    //获取选定的单元格后改变其使用的字体
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    for(int i=0;i<list.size();i++)
    {
        list[i]->setFont(f);    //f即改变的字体样式
    }
}
//单元格字体大小
void MainWindow::on_fontSizeBox_valueChanged(int arg1)
{
    //获取选定的单元格并改变其字体大小
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    for(int i=0;i<list.size();i++)
    {
        QFont f=list[i]->font();
        f.setPointSize(arg1);   //arg1即为改变的数值
        list[i]->setFont(f);
    }
}
//单元格内容加粗按钮
void MainWindow::on_checkBoxBold_toggled(bool checked)
{
    if(checked)
    {
        //加粗
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            QFont f=list[i]->font();
            f.setBold(true);
            list[i]->setFont(f);
        }
    }
    else
    {
        //不加粗
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();

        for(int i=0;i<list.size();i++)
        {
            QFont f=list[i]->font();
            f.setBold(false);
            list[i]->setFont(f);
        }
    }
}
//单元格内容倾斜按钮
void MainWindow::on_checkBoxItalics_toggled(bool checked)
{
    if(checked)
    {
        //倾斜
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            QFont f=list[i]->font();
            f.setItalic(true);
            list[i]->setFont(f);
        }
    }
    else
    {
        //不倾斜
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            QFont f=list[i]->font();
            f.setItalic(false);
            list[i]->setFont(f);
        }
    }
}
//单元格内容下划线按钮
void MainWindow::on_checkBoxUnderline_toggled(bool checked)
{
    if(checked)
    {
        //下划线
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems(); 
        for(int i=0;i<list.size();i++)
        {
            QFont f=list[i]->font();
            f.setUnderline(true);
            list[i]->setFont(f);
        }
    }
    else
    {
        //不下划线
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            QFont f=list[i]->font();
            f.setUnderline(false);
            list[i]->setFont(f);
        }
    }
}
//单元格字体颜色按钮
void MainWindow::on_pushButtonFontColor_clicked()
{
    //唤出颜色选择对话框并选择颜色
    QColor color = QColorDialog::getColor(*defaultcolor);
    //改变选中单元格的字体颜色
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    for(int i=0;i<list.size();i++)
    {
        list[i]->setTextColor(color);
    }
}
//单元格背景颜色（主题颜色按钮）
void MainWindow::on_pushButtonThemeColor_clicked()
{
    //唤出颜色选择对话框并选择颜色
    QColor color = QColorDialog::getColor(*defaulttheme);
    //改变选中范围内的单元格的背景颜色
    QList<QTableWidgetSelectionRange>list = ui->tableWidget->selectedRanges();
    for(int i=0;i<list.size();i++)
    {
        for(int j=list[i].topRow();j<=list[i].bottomRow();j++)
        {
            for(int k=list[i].leftColumn();k<=list[i].rightColumn();k++)
            {
                ui->tableWidget->item(j,k)->setBackgroundColor(color);
            }
        }
    }
}

//单元格内容居左/居中/居右
void MainWindow::on_pushButtonLeft_toggled(bool checked)
{
    //内容居左
    if(checked)
    {
        //按钮图片切换及回弹另外两个格式按钮
        ui->pushButtonLeft->setIcon(QIcon(":/image/left_on.png"));
        ui->pushButtonCenter->setChecked(false);
        ui->pushButtonRight->setChecked(false);

        //选中的单元格内容进行居左设置
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            list[i]->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        }
    }
    else
    {
        ui->pushButtonLeft->setIcon(QIcon(":/image/left.png"));

        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            list[i]->setTextAlignment(Qt::AlignVCenter);
        }
    }
}
void MainWindow::on_pushButtonCenter_toggled(bool checked)
{
    //内容居中
    if(checked)
    {
        //按钮图片切换及回弹另外两个格式按钮
        ui->pushButtonCenter->setIcon(QIcon(":/image/center_on.png"));
        ui->pushButtonLeft->setChecked(false);
        ui->pushButtonRight->setChecked(false);

        //选中的单元格进行内容居中设置
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            list[i]->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        }
    }
    else
    {
        ui->pushButtonCenter->setIcon(QIcon(":/image/center.png"));

        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            list[i]->setTextAlignment(Qt::AlignVCenter);
        }
    }
}
void MainWindow::on_pushButtonRight_toggled(bool checked)
{
    //内容居右
    if(checked)
    {
        //按钮图片切换及回弹另外两个格式按钮
        ui->pushButtonRight->setIcon(QIcon(":/image/right_on.png"));
        ui->pushButtonLeft->setChecked(false);
        ui->pushButtonCenter->setChecked(false);

        //选中的单元格进行内容居右设置
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            list[i]->setTextAlignment(Qt::AlignVCenter|Qt::AlignRight);
        }
    }
    else
    {
        ui->pushButtonRight->setIcon(QIcon(":/image/right.png"));

        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            list[i]->setTextAlignment(Qt::AlignVCenter);
        }
    }
}

//单击单元格时改变编辑页面显示参数
void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    //字体与字体大小
    ui->fontTypeBox->setCurrentFont(ui->tableWidget->item(row,column)->font());
    ui->fontSizeBox->setValue(ui->tableWidget->item(row,column)->font().pointSize());

    //字体加粗,倾斜,下划线
    if(ui->tableWidget->item(row,column)->font().bold()) ui->checkBoxBold->setCheckState(Qt::CheckState::Checked);
    else ui->checkBoxBold->setCheckState(Qt::CheckState::Unchecked);
    if(ui->tableWidget->item(row,column)->font().italic()) ui->checkBoxItalics->setCheckState(Qt::CheckState::Checked);
    else ui->checkBoxItalics->setCheckState(Qt::CheckState::Unchecked);
    if(ui->tableWidget->item(row,column)->font().underline()) ui->checkBoxUnderline->setCheckState(Qt::CheckState::Checked);
    else ui->checkBoxUnderline->setCheckState(Qt::CheckState::Unchecked);

    //内容居左居中居右
    if(ui->tableWidget->item(row,column)->textAlignment()==128)
    {
        ui->pushButtonLeft->setChecked(false);
        ui->pushButtonCenter->setChecked(false);
        ui->pushButtonRight->setChecked(false);
    }
    else if(ui->tableWidget->item(row,column)->textAlignment()==129)
    {
        ui->pushButtonLeft->setChecked(true);
    }
    else if(ui->tableWidget->item(row,column)->textAlignment()==132)
    {
        ui->pushButtonCenter->setChecked(true);
    }
    else if(ui->tableWidget->item(row,column)->textAlignment()==130)
    {
        ui->pushButtonRight->setChecked(true);
    }
}

//自动换行按钮
void MainWindow::on_pushButtonWordwrap_toggled(bool checked)
{
    if(checked)
    {
        //使得表格输入时实现自动换行
        connect(ui->tableWidget,&QTableWidget::itemChanged,ui->tableWidget,&QTableWidget::resizeRowsToContents);

        //改变按钮样式
        QPalette pal = ui->pushButtonWordwrap->palette();
        pal.setColor(QPalette::Button,*new QColor(128,128,128));
        ui->pushButtonWordwrap->setPalette(pal);
    }
    else
    {
        //撤销自动换行
        disconnect(ui->tableWidget,&QTableWidget::itemChanged,ui->tableWidget,&QTableWidget::resizeRowsToContents);

        //改变按钮样式
        QPalette pal = ui->pushButtonWordwrap->palette();
        pal.setColor(QPalette::Button,*new QColor(255,255,255));
        ui->pushButtonWordwrap->setPalette(pal);
    }
}

//行插入
void MainWindow::on_pushButtonRowInsert_clicked()
{
    //唤出插入对话框选择插入行数及位置
    DialogInsert* w=new DialogInsert();
    w->exec();

    //确认是否插入
    if(w->yesorno)
    {
        //way为1时在当前选中范围之下插入,为0时在表尾插入
        if(w->way)
        {
            QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
            if(list.size()==0)
            {
                QMessageBox::critical(this,"错误","未选中任何单元格！");
            }
            else if(list.size()>1)
            {
                QMessageBox::critical(this,"错误","选中多个单元格区域！");
            }
            else {
                int row=list[0].bottomRow();
                for(int i=0;i<w->num;i++)
                {
                    row++;
                    ui->tableWidget->insertRow(row);    //循环插入多行

                    //对新插入的单元格进行初始化
                    for(int j=0;j<ui->tableWidget->columnCount();j++)
                    {
                        ui->tableWidget->setItem(row,j,new QTableWidgetItem(""));
                        ui->tableWidget->item(row,j)->setFont(*defaultfont);
                        ui->tableWidget->item(row,j)->setTextColor(*defaultcolor);
                        ui->tableWidget->item(row,j)->setBackgroundColor(*defaulttheme);
                    }
                }
            }
        }
        else {
            for(int i=0;i<w->num;i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());    //循环插入多行

                //对新插入的单元格进行初始化
                for(int j=0;j<ui->tableWidget->columnCount();j++)
                {
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,j,new QTableWidgetItem(""));
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,j)->setFont(*defaultfont);
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,j)->setTextColor(*defaultcolor);
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,j)->setBackgroundColor(*defaulttheme);
                }
            }
        }
    }

    delete w;
    updataStatusBar();
}
//列插入
void MainWindow::on_pushButtonColumnInsert_clicked()
{
    //唤出插入对话框选择插入列数及位置
    DialogInsert* w=new DialogInsert();
    w->exec();

    //确认是否插入
    if(w->yesorno)
    {
        //way为1时在当前选中范围之后插入,为0时在表尾插入
        if(w->way)
        {
            QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
            if(list.size()==0)
            {
                QMessageBox::critical(this,"错误","未选中任何单元格！");
            }
            else if(list.size()>1)
            {
                QMessageBox::critical(this,"错误","选中多个单元格区域！");
            }
            else {
                int colum=list[0].rightColumn();
                for(int i=0;i<w->num;i++)
                {
                    colum++;
                    ui->tableWidget->insertColumn(colum);   //循环插入多列

                    //对新插入的单元格进行初始化
                    for(int j=0;j<ui->tableWidget->rowCount();j++)
                    {
                        ui->tableWidget->setItem(j,colum,new QTableWidgetItem(""));
                        ui->tableWidget->item(j,colum)->setFont(*defaultfont);
                        ui->tableWidget->item(j,colum)->setTextColor(*defaultcolor);
                        ui->tableWidget->item(j,colum)->setBackgroundColor(*defaulttheme);
                    }
                }
            }
        }
        else {
            for(int i=0;i<w->num;i++)
            {
                ui->tableWidget->insertColumn(ui->tableWidget->columnCount());    //循环插入多列

                //对新插入的单元格进行初始化
                for(int j=0;j<ui->tableWidget->rowCount();j++)
                {
                    ui->tableWidget->setItem(j,ui->tableWidget->columnCount()-1,new QTableWidgetItem(""));
                    ui->tableWidget->item(j,ui->tableWidget->columnCount()-1)->setFont(*defaultfont);
                    ui->tableWidget->item(j,ui->tableWidget->columnCount()-1)->setTextColor(*defaultcolor);
                    ui->tableWidget->item(j,ui->tableWidget->columnCount()-1)->setBackgroundColor(*defaulttheme);
                }
            }
        }
    }

    delete w;
    updataStatusBar();
}
//行删除
void MainWindow::on_pushButtonRowDelete_clicked()
{
    //获取要删除的范围
    QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
    if(list.size()==0)
    {
        QMessageBox::critical(this,"错误","未选中任一行/单元格！");
    }
    else if(list.size()>1)
    {
        QMessageBox::critical(this,"错误","选中多个单元格区域!");
    }
    else {
        //确认是否删除
        if(QMessageBox::Ok==QMessageBox::question(this,"是否确认","是否确认要删除指定的行？",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
        {
            for(int i=list[0].topRow();i<=list[0].bottomRow();i++)
            {
                ui->tableWidget->removeRow(list[0].topRow());       //循环删除多行
                updataStatusBar();
            }
        }
    }
}
//列删除
void MainWindow::on_pushButtonColumnDelete_clicked()
{
    //获取要删除的范围
    QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
    if(list.size()==0)
    {
        QMessageBox::critical(this,"错误","未选中任一列/单元格！");
    }
    else if(list.size()>1)
    {
        QMessageBox::critical(this,"错误","选中多个单元格区域!");
    }
    else {
        //确认是否删除
        if(QMessageBox::Ok==QMessageBox::question(this,"是否确认","是否确认要删除指定的列？",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
        {
            for(int i=list[0].leftColumn();i<=list[0].rightColumn();i++)
            {
                ui->tableWidget->removeColumn(list[0].leftColumn());    //循环删除多列
                updataStatusBar();
            }
        }

    }
}
//全表删除
void MainWindow::on_pushButtonTableDelete_clicked()
{
    //确认是否删除
    if(QMessageBox::Ok==QMessageBox::question(this,"是否确认","是否确认要删除全表？",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
        ui->tableWidget->clear();       //全表删除
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);
        updataStatusBar();
    }
}

//复制按钮
void MainWindow::on_pushButtonCopy_clicked()
{
    //获取要复制的范围
    QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
    if(list.size()==0)
    {
        QMessageBox::critical(this,"错误","未选中任何单元格用于复制！");
    }
    else if(list.size()>1)
    {
        QMessageBox::critical(this,"错误","选中多个单元格区域！");
    }
    else {
        QString text_copy;      //用于储存复制的内容
        for(int i=list[0].topRow();i<=list[0].bottomRow();i++)
        {
            for(int j=list[0].leftColumn();j<=list[0].rightColumn();j++)
            {
                //记录同一行的单元格内容并用\t分隔开(若单元格内容为空则记为特殊标记)
                if(ui->tableWidget->item(i,j)->text()=="") text_copy.append("此单元格为空，未编辑过");
                else text_copy.append(ui->tableWidget->item(i,j)->text());
                text_copy.append("\t");
            }
            //每行以\n分隔开来
            text_copy.append("\n");
        }
        text_copy.append("\n");
        QApplication::clipboard()->setText(text_copy);      //最后将复制的内容存入剪切板中
    }
}
//粘贴按钮（未添加相加等功能）
void MainWindow::on_pushButtonPaste_clicked()
{
    //获取要进行粘贴的位置
    QList<QTableWidgetSelectionRange> list = ui->tableWidget->selectedRanges();
    if(list.size()==0)
    {
        QMessageBox::critical(this,"错误","未选中任何单元格用于粘贴！");
    }
    else if(list.size()>1)
    {
        QMessageBox::critical(this,"错误","选中多个单元格区域！");
    }
    else
    {
        //唤出粘贴选择按钮
        Dialogstickup* w=new Dialogstickup();
        w->exec();

        if(w->yesorno)
        {
            int row=list[0].topRow(),colum=list[0].leftColumn();

            //从剪切板中取出要粘贴的内容
            QString text_paste=QApplication::clipboard()->text();

            //以\n为分隔符,划分出每一行的内容
            QStringList row_list=text_paste.split("\n",QString::SkipEmptyParts);
            for(int i=0;i<row_list.size();i++)
            {
                //如果粘贴后内容行数会超出此时的表格最大行数,则后续的行无需进行粘贴
                if(row+i>=ui->tableWidget->rowCount()) break;

                //以\t为分隔符,划分出某一行内每一列的内容,即每个单元格的内容
                QStringList colum_list=row_list[i].split("\t",QString::SkipEmptyParts);
                for(int j=0;j<colum_list.size();j++)
                {
                    //如果粘贴后内容列数会超出此时的表格最大列数,则后续的列无需进行粘贴
                    if(colum+j>=ui->tableWidget->columnCount()) break;

                    //直接替换
                    if(w->select==1)
                    {
                        //根据单元格内容进行粘贴,有特殊标记则置空
                        if(colum_list[j]=="此单元格为空，未编辑过") ui->tableWidget->item(row+i,colum+j)->setText("");
                        else ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                    }
                    //相加后替换
                    else if(w->select==3)
                    {
                        Change c;
                        //判断是否两个数据均为数字，是则相加后替换，否则不替换
                        if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                        {
                            double num1=colum_list[j].toDouble();
                            double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                            double num3=num1+num2;
                            ui->tableWidget->item(row+i,colum+j)->setText(QString::number(num3,'f',2));
                        }
                        else continue;
                    }
                    //相减后替换
                    else if(w->select==4)
                    {
                        Change c;
                        //判断是否两个数据均为数字，是则相减后替换，否则不替换
                        if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                        {
                            double num1=colum_list[j].toDouble();
                            double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                            double num3=num2-num1;
                            ui->tableWidget->item(row+i,colum+j)->setText(QString::number(num3,'f',2));
                        }
                        else continue;
                    }
                    //按条件替换
                    else if(w->select==2)
                    {
                        Change c;
                        if(w->select2==0)
                        {
                            switch (w->select1) {
                            case 0://原数据大于粘贴数据
                                if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num1=colum_list[j].toDouble();
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2>num1) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 1://原数据大于等于粘贴数据
                                if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num1=colum_list[j].toDouble();
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2>=num1) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 2://原数据小于粘贴数据
                                if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num1=colum_list[j].toDouble();
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2<num1) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 3://原数据小于等于粘贴数据
                                if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num1=colum_list[j].toDouble();
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2<=num1) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 4://原数据不等于粘贴数据
                                if(c.isNum(colum_list[j])&&c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num1=colum_list[j].toDouble();
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2!=num1) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            }
                        }
                        else if(w->select2==1)
                        {
                            switch (w->select1) {
                            case 0://原数据大于粘贴数据
                                if(c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2>w->num) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 1://原数据大于等于粘贴数据
                                if(c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2>=w->num) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 2://原数据小于粘贴数据
                                if(c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2<w->num) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 3://原数据小于等于粘贴数据
                                if(c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2<=w->num) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            case 4://原数据不等于粘贴数据
                                if(c.isNum(ui->tableWidget->item(row+i,colum+j)->text()))
                                {
                                    double num2=ui->tableWidget->item(row+i,colum+j)->text().toDouble();
                                    if(num2!=w->num) ui->tableWidget->item(row+i,colum+j)->setText(colum_list[j]);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        delete w;
    }
}

//新建按钮
void MainWindow::on_pushButtonNew_clicked()
{
    //唤出新建对话框
    DialogNew *d=new DialogNew();
    d->exec();
    if(d->check)
    {
        //先删除原先的表格
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);

        ui->tableWidget->setRowCount(d->row);
        ui->tableWidget->setColumnCount(d->column);
        //初始化整个表格
        init();
        url="";
        ui->pushButtonSave->setDisabled(true);//将保存按钮变为不可点击
        ui->pushButtonSaveAs->setDisabled(false);//将另存为的按钮变为可点击

        updataStatusBar();
    }
    delete d;
}
//保存按钮
void MainWindow::on_pushButtonSave_clicked()
{
    Change change;      //调用类型转变函数的类

    QFile file(url);       //打开文件路径
    if(file.open(QIODevice::ReadWrite))//写入内容
    {
        //清空原来的数据
        file.resize(0);
        //记录总的行列数
        int row=ui->tableWidget->rowCount();
        int column=ui->tableWidget->columnCount();
        QString result="";
        result+="rows=\n";
        result+=QString::number(row)+"\n";      //记录行数
        result+="columns=\n";
        result+=QString::number(column)+"\n\n";   //记录列数

        //判断具体的某个单元格内的属性
        for(int x=0;x<row;x++)
        {
            for(int y=0;y<column;y++)
            {
                if(ui->tableWidget->item(x,y)){
                    result+="row=\n";
                    result+=QString::number(x)+"\n";
                    result+="column=\n";
                    result+=QString::number(y)+"\n";    //记录单元格的坐标

                    if(isFunction[x][y]==1)//如果是公式
                    {
                        result+="formula=\n";
                        result+=Functions[x][y]+"\n";//记录单元格的公式
                    }
                    else{
                        result+="text=\n";
                        result+=ui->tableWidget->item(x,y)->text()+"\n";        //记录单元格的内容（以字符串的形式）
                    }

                    result+="textColor=(red,green,blue,色调,饱和度,数值,透明度)\n";
                    result+=change.toString(ui->tableWidget->item(x,y)->textColor());       //记录文本的颜色

                    result+="backgroundColor=(red,green,blue,色调,饱和度,数值,透明度)\n";
                    result+=change.toString(ui->tableWidget->item(x,y)->backgroundColor()); //记录背景颜色

                    result+="font=(family,size,加粗,倾斜,下划线)\n";
                    result+=change.toString(ui->tableWidget->item(x,y)->font());    //记录文本字体

                    result+="textAlignment=\n";
                    result+=QString::number(ui->tableWidget->item(x,y)->textAlignment())+"\n";  //记录对齐方式
                    result+="\n";
                    //用char *的格式记录（去除引号）
                    file.write(change.deleteQuote(result));
                    result="";
                }
            }
        }

        file.close();
    }
}
//另存为按钮
void MainWindow::on_pushButtonSaveAs_clicked()
{
    Change change;      //调用类型转变函数的类

    QFileDialog *fd=new QFileDialog();
    url=fd->getSaveFileName(nullptr,"保存文件","");    //记录文件的地址
        QFile file(url);

    if(file.open(QIODevice::ReadWrite))     //写入内容
    {
        //清空原来的数据
        file.resize(0);
        //记录总的行列数
        int row=ui->tableWidget->rowCount();
        int column=ui->tableWidget->columnCount();

        QString result="";
        result+="rows=\n";
        result+=QString::number(row)+"\n";      //记录行数
        result+="columns=\n";
        result+=QString::number(column)+"\n\n";   //记录列数

        for(int x=0;x<row;x++)
        {
            for(int y=0;y<column;y++)
            {

                if(ui->tableWidget->item(x,y)){
                    result+="row=\n";
                    result+=QString::number(x)+"\n";
                    result+="column=\n";
                    result+=QString::number(y)+"\n";    //记录单元格的坐标

                    if(isFunction[x][y]==1)//如果是公式
                    {
                        result+="formula=\n";
                        result+=Functions[x][y]+"\n";//记录单元格的公式
                    }
                    else{
                        result+="text=\n";
                        result+=ui->tableWidget->item(x,y)->text()+"\n";        //记录单元格的内容（以字符串的形式）
                    }

                    result+="textColor=(red,green,blue,色调,饱和度,数值,透明度)\n";
                    result+=change.toString(ui->tableWidget->item(x,y)->textColor());       //记录文本的颜色

                    result+="backgroundColor=(red,green,blue,色调,饱和度,数值,透明度)\n";
                    result+=change.toString(ui->tableWidget->item(x,y)->backgroundColor()); //记录背景颜色

                    result+="font=(family,size,加粗,倾斜,下划线)\n";
                    result+=change.toString(ui->tableWidget->item(x,y)->font());    //记录文本字体

                    result+="textAlignment=\n";
                    result+=QString::number(ui->tableWidget->item(x,y)->textAlignment())+"\n";  //记录对齐方式
                    result+="\n";
                    //用char *的格式记录（去除引号）
                    file.write(change.deleteQuote(result));
                    result="";
                }
            }
        }

        file.close();
        ui->pushButtonSave->setDisabled(false);//将保存按钮设置为可点击状态
    }
    delete fd;
}//打开按钮
void MainWindow::on_pushButtonOpen_clicked()
{
    Change change;      //调用类型转变函数的类

    QFileDialog*fd=new QFileDialog();
    QString Name=fd->getOpenFileName(nullptr,"打开文件","");//记录文件的地址
        if(Name=="")return;
    QFile file(Name);
    int lines=0;

    if(file.open(QIODevice::ReadWrite))//读取内容（也许后续会保存修改）
    {
        int row,column;     //总的行列数
        int x;      //行
        int y;      //列
        QString text;       //单元格内容
        QColor color;       //文本的颜色
        QColor background;  //背景颜色
        QFont font;     //文本字体
        int align;      //对齐方式

        QString line;       //用于一行一行读取

        //行列数的确定
        //行数
        line=file.readLine();
        lines++;
        if(line!="rows=\n")//判断格式
        {
            QMessageBox::warning(nullptr,"出错","第"+QString::number(lines)+"行出错，应为'rows=\n'");
            return;
        }
        line=file.readLine();//读取存储的数据
        lines++;
        row=line.toInt();

        //列数
        line=file.readLine();
        lines++;
        if(line!="columns=\n")//判断格式
        {
            QMessageBox::warning(nullptr,"出错","第"+QString::number(lines)+"行出错，应为'columns=\n'");
            return;
        }
        line=file.readLine();
        lines++;
        column=line.toInt();

        ui->tableWidget->setRowCount(row);
        ui->tableWidget->setColumnCount(column);
        updataStatusBar();


        init();     //初始化表格
        if(file.atEnd())return;
        line=file.readLine();//读取分隔的一个换行

        while(!file.atEnd())
        {
            line=file.readLine();
            lines++;
            if(line!="row=\n")//判断格式
            {
                QMessageBox::warning(nullptr,"出错","第"+QString::number(lines)+"行出错，应为'row=\n'");
                return;
            }
            line=file.readLine();
            lines++;
            x=line.toInt();     //某一行
            if(x>=row){
                QMessageBox::warning(nullptr,"出错","第"+QString::number(lines)+"行出错，单元格的行坐标大于总的行坐标");
                return;
            }

            line=file.readLine();
            lines++;
            if(line!="column=\n")//判断格式
            {
                QMessageBox::warning(nullptr,"出错","第"+QString::number(lines)+"行出错，应为'column=\n'");
                return;
            }
            line=file.readLine();
            lines++;
            y=line.toInt();     //某一列
            if(y>=column){
                QMessageBox::warning(nullptr,"出错","第"+QString::number(lines)+"行出错，单元格的列坐标大于总的列坐标");
                return;
            }

            line=file.readLine();
            lines++;
            while(line!="\n")//记录中是以额外的一个换行代表一个单元格的结束，因此用这个条件判断是否完成一个单元格的读取
            {
                if(line=="text=\n"){
                    line=file.readLine();
                    lines++;
                    text="";            //单元格内容
                    for(int i=0;i<line.size()-1;i++)
                    {
                        text+=line[i];
                    }
                    ui->tableWidget->item(x,y)->setText(text);
                }
                else if(line=="formula=\n"){
                    line=file.readLine();
                    lines++;
                    ui->tableWidget->item(x,y)->setText(line);
                }
                else if(line=="textColor=(red,green,blue,色调,饱和度,数值,透明度)\n"){
                    line=file.readLine();
                    lines++;
                    color=change.toQColor(line);    //文本的颜色
                    ui->tableWidget->item(x,y)->setTextColor(color);
                }
                else if(line=="backgroundColor=(red,green,blue,色调,饱和度,数值,透明度)\n"){
                    line=file.readLine();
                    lines++;
                    background=change.toQColor(line);//背景颜色
                    ui->tableWidget->item(x,y)->setBackgroundColor(background);
                }
                else if(line=="font=(family,size,加粗,倾斜,下划线)\n"){
                    line=file.readLine();
                    lines++;
                    font=change.toQFont(line);      //文本字体
                    ui->tableWidget->item(x,y)->setFont(font);
                }
                else if(line=="textAlignment=\n"){
                    line=file.readLine();
                    lines++;
                    align=line.toInt();     //对齐方式
                    ui->tableWidget->item(x,y)->setTextAlignment(align);
                }

                line=file.readLine();
                lines++;
            }
        }
        file.close();

        //改变保存和另存为按钮的状态
        ui->pushButtonSaveAs->setDisabled(false);
        ui->pushButtonSave->setDisabled(false);
    }
    delete fd;

    //存储下打开的文件路径
    url=Name;
}

//全表查询
void MainWindow::on_pushButtonAllSearch_clicked()
{
    int count=0;    //记录查询结果的数量
    bool ok=false;  //判断是否点击了查询按钮

    //设置查询条件窗口格式
    QInputDialog  *dia=new QInputDialog(this);
    QString text= dia->getText(this,"查询条件","请输入：",QLineEdit::Normal,"",&ok);
    dia->setAttribute(Qt::WA_DeleteOnClose);

    //设置查询结果窗口格式
    QTableWidget *result=new QTableWidget();
    result->setColumnCount(4);
    result->setHorizontalHeaderLabels(QStringList()<<"表格"<<"行"<<"列"<<"值");
    result->resize(510,400);
    result->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    result->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中

    //选中全表范围
    QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(0, 0,ui->tableWidget->rowCount()-1,ui->tableWidget->columnCount()-1);
    ui->tableWidget->setRangeSelected(range, true);

    //对选中的每一个单元格查询
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    for(int i=0;i<list.length();i++)
    {
        QString str =list[i]->data(Qt::DisplayRole).toString();
        //如果查询成功，将结果记录在查询结果窗口
        if(str.contains(text))
        {
            count++;
            result->insertRow(result->rowCount());
            result->setItem(result->rowCount()-1,0,new QTableWidgetItem("MyExcel"));
            result->setItem(result->rowCount()-1,1,new QTableWidgetItem(QString::number(list[i]->row()+1)));
            result->setItem(result->rowCount()-1,2,new QTableWidgetItem(QString::number(list[i]->column()+1)));
            result->setItem(result->rowCount()-1,3,new QTableWidgetItem(str));
            for(int j=0;j<4;j++)
            {
                result->item(result->rowCount()-1, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);   //显示格式设置
            }

         }
    }

    result->setWindowTitle(QString::number(count)+"个单元格被找到");
    //点击输出窗口中的一行，将表格中与其对应的一个单元格选中
    connect(result,&QTableWidget::cellClicked,[=](){
       QString str= result->item(result->currentRow(),1)->text();
       int hang=str.toInt();
       QString str2= result->item(result->currentRow(),2)->text();
       int lie=str2.toInt();
       ui->tableWidget->setCurrentCell(hang-1,lie-1);
     });

    //查询结果为空输出警告信息
    if(count==0&&ok)
    {
        QMessageBox::warning(this,"warning","无法找到你所查找的内容！");
    }
    //查询结果不为空显示输出窗口
    if(count!=0&&ok)
    {
        result->show();
    }
}
//按行查询
void MainWindow::on_pushButtonRowSearch_clicked()
{
    bool ok=false;      //判断是否点击了查询按钮
    int count=0;        //记录查询结果的数量

    //设置查询条件窗口格式
    QInputDialog  *dia=new QInputDialog(this);

    //设置查询结果窗口格式
    QTableWidget *result=new QTableWidget();
    result->setColumnCount(4);
    result->setHorizontalHeaderLabels(QStringList()<<"表格"<<"行"<<"列"<<"值");
    result->resize(510,400);
    result->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    result->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中

    //按行选中
    QList<QTableWidgetItem*>list1 = ui->tableWidget->selectedItems();
    for(int i=0;i<list1.size();i++)
    {
        QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(list1[i]->row(), 0,list1[i]->row(),ui->tableWidget->columnCount()-1);
        ui->tableWidget->setRangeSelected(range, true);
    }

    if(QMessageBox::Ok==QMessageBox::question(this,"ques","是否已选好行",QMessageBox::Ok|QMessageBox::No))
    {
        //输入查询条件
        QString text= dia->getText(this,"查询条件","请输入：",QLineEdit::Normal,"",&ok);
        dia->setAttribute(Qt::WA_DeleteOnClose);

        //查询所选行里的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.length();i++)
        {
            QString str =list[i]->data(Qt::DisplayRole).toString();
            //如果查询成功，将结果记录在查询结果窗口
            if(str.contains(text))
            {
                count++;
                result->insertRow(result->rowCount());
                result->setItem(result->rowCount()-1,0,new QTableWidgetItem("MyExcel"));
                result->setItem(result->rowCount()-1,1,new QTableWidgetItem(QString::number(list[i]->row()+1)));
                result->setItem(result->rowCount()-1,2,new QTableWidgetItem(QString::number(list[i]->column()+1)));
                result->setItem(result->rowCount()-1,3,new QTableWidgetItem(str));
                for(int j=0;j<4;j++)
                {
                    result->item(result->rowCount()-1, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                }

            }
        }

        result->setWindowTitle(QString::number(count)+"个单元格被找到");
        //点击输出窗口中的一行，将表格中与其对应的一个单元格选中
        connect(result,&QTableWidget::cellClicked,[=](){
           QString str= result->item(result->currentRow(),1)->text();
           int hang=str.toInt();
           QString str2= result->item(result->currentRow(),2)->text();
           int lie=str2.toInt();
           ui->tableWidget->setCurrentCell(hang-1,lie-1);
         });
    }

    //查询结果为空输出警告信息
    if(count==0&&ok)
    {
        QMessageBox::warning(this,"warning","无法找到你所查找的内容！");
    }
    //查询结果不为空显示输出窗口
    if(count!=0&&ok)
    {
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        result->show();
    }
}
//按列查询
void MainWindow::on_pushButtonColumnSearch_clicked()
{
    bool ok=false;      //判断是否点击了查询按钮
    int count=0;        //记录查询结果的数量

    //设置查询条件窗口格式
    QInputDialog  *dia=new QInputDialog(this);

    //设置查询结果窗口格式
    QTableWidget *result=new QTableWidget();
    result->setColumnCount(4);
    result->setHorizontalHeaderLabels(QStringList()<<"表格"<<"行"<<"列"<<"值");
    result->resize(510,400);
    result->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    result->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中

    //按列选中
    QList<QTableWidgetItem*>list1 = ui->tableWidget->selectedItems();
    for(int i=0;i<list1.size();i++)
    {
        QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(0, list1[i]->column(),ui->tableWidget->rowCount()-1,list1[i]->column());
        ui->tableWidget->setRangeSelected(range, true);
    }

    if(QMessageBox::Ok==QMessageBox::question(this,"ques","是否已选好列",QMessageBox::Ok|QMessageBox::No))
    {
        //输入查询条件
        QString text= dia->getText(this,"查询条件","请输入：",QLineEdit::Normal,"",&ok);
        dia->setAttribute(Qt::WA_DeleteOnClose);

        //查询所选列里的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.length();i++)
        {
            QString str =list[i]->data(Qt::DisplayRole).toString();
            //如果查询成功，将结果记录在查询结果窗口
            if(str.contains(text))
            {
                count++;
                result->insertRow(result->rowCount());
                result->setItem(result->rowCount()-1,0,new QTableWidgetItem("MyExcel"));
                result->setItem(result->rowCount()-1,1,new QTableWidgetItem(QString::number(list[i]->row()+1)));
                result->setItem(result->rowCount()-1,2,new QTableWidgetItem(QString::number(list[i]->column()+1)));
                result->setItem(result->rowCount()-1,3,new QTableWidgetItem(str));
                for(int j=0;j<4;j++)
                {
                    result->item(result->rowCount()-1, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                }

            }
        }

        result->setWindowTitle(QString::number(count)+"个单元格被找到");
        //点击输出窗口中的一行，将表格中与其对应的一个单元格选中
        connect(result,&QTableWidget::cellClicked,[=](){
           QString str= result->item(result->currentRow(),1)->text();
           int hang=str.toInt();
           QString str2= result->item(result->currentRow(),2)->text();
           int lie=str2.toInt();
           ui->tableWidget->setCurrentCell(hang-1,lie-1);
          });
    }

    //查询结果为空输出警告信息
    if(count==0&&ok)
    {
        QMessageBox::warning(this,"warning","无法找到你所查找的内容！");
    }
    //查询结果不为空显示输出窗口
    if(count!=0&&ok)
    {
       ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
       result->show();
    }

}
//选中块查询
void MainWindow::on_pushButtonBlockSearch_clicked()
{
    bool ok=false;      //判断是否点击了查询按钮
    int count=0;        //记录查询结果的数量

    //设置查询条件窗口格式
    QInputDialog *dia=new QInputDialog(this);

    //设置查询结果窗口格式
    QTableWidget *result=new QTableWidget();
    result->setColumnCount(4);
    result->setHorizontalHeaderLabels(QStringList()<<"表格"<<"行"<<"列"<<"值");
    result->resize(510,400);
    result->setWindowTitle(QString::number(count)+"个单元格被找到");
    result->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    result->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中

    if(QMessageBox::Ok==QMessageBox::question(this,"ques","是否已选好块",QMessageBox::Ok|QMessageBox::No))
    {
        //输入查询条件
        QString text= dia->getText(this,"查询条件","请输入：",QLineEdit::Normal,"",&ok);
        dia->setAttribute(Qt::WA_DeleteOnClose);

        //查询所选块里的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.length();i++)
        {
            QString str =list[i]->data(Qt::DisplayRole).toString();
            //如果查询成功，将结果记录在查询结果窗口
            if(str.contains(text))
            {
                count++;
                result->insertRow(result->rowCount());
                result->setItem(result->rowCount()-1,0,new QTableWidgetItem("MyExcel"));
                result->setItem(result->rowCount()-1,1,new QTableWidgetItem(QString::number(list[i]->row()+1)));
                result->setItem(result->rowCount()-1,2,new QTableWidgetItem(QString::number(list[i]->column()+1)));
                result->setItem(result->rowCount()-1,3,new QTableWidgetItem(str));
                for(int j=0;j<4;j++)
                {
                    result->item(result->rowCount()-1, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                }

            }
        }

        result->setWindowTitle(QString::number(count)+"个单元格被找到");
        //点击输出窗口中的一行，将表格中与其对应的一个单元格选中
        connect(result,&QTableWidget::cellClicked,[=](){
            QString str= result->item(result->currentRow(),1)->text();
            int hang=str.toInt();
            QString str2= result->item(result->currentRow(),2)->text();
            int lie=str2.toInt();
            ui->tableWidget->setCurrentCell(hang-1,lie-1);
        });
    }

    //查询结果为空输出警告信息
    if(count==0&&ok)
    {
        QMessageBox::warning(this,"warning","无法找到你所查找的内容！");
    }
    //查询结果不为空显示输出窗口
    if(count!=0&&ok)
    {
        result->show();
    }
}

//列升序
void MainWindow::on_pushButtonColumnSort1_clicked()
{
    //选中所选单元格的一整列
    QList<QTableWidgetItem*>list1 = ui->tableWidget->selectedItems();
    for(int i=0;i<list1.size();i++)
    {
        QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(0, list1[i]->column(),ui->tableWidget->rowCount()-1,list1[i]->column());
        ui->tableWidget->setRangeSelected(range, true);
    }

    if(QMessageBox::Yes==QMessageBox::question(this,"ques","是否已选好要排序的一列",QMessageBox::Yes|QMessageBox::No))
    {
        //剔除掉选中单元格中没有内容的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            if(list[i]->text()=="")
            {
                list.removeAt(i);
                i--;
            }
        }
        //判断剔除后还有没有数据用于排序
        if(list.size()==0)
        {
            QMessageBox::warning(this,"warning","所选区域没有数据！");
            return;
        }

        //不可选择多列数据进行排序
        int m=1;
        for(;m<list.size();m++)
        {
            if(list[m]->column()!=list[0]->column())
            {
                break;
            }
        }
        if(m!=list.size())
        {
            QMessageBox::warning(this,"warning","选中了多列具有数据的列，请重新选择！");
            return;
        }

        //选择排序方式
        QMessageBox mm(QMessageBox::Question,"ques","请选择排序方式",QMessageBox::Yes|QMessageBox::No);
        mm.button(QMessageBox::Yes)->setText("字符串排序");
        mm.button(QMessageBox::No)->setText("数值排序");
        int flag=mm.exec();

        //临时列表存储选中单元格的内容，用以辅助后续排序
        QStringList list1;
        int number=list.size();
        for(int i=0;i<number;i++)
        {
           QString str =list[i]->text();
           list1.append(str);

           ui->tableWidget->item(list[i]->row(),list[i]->column())->setText("");
        }

        //字符串排序
        if(flag==QMessageBox::Yes)
        {
            QMessageBox c(QMessageBox::Question,"ques","是否大小写敏感",QMessageBox::Yes|QMessageBox::No);
            c.button(QMessageBox::Yes)->setText("是");
            c.button(QMessageBox::No)->setText("否");
            int cap=c.exec();

           if(cap==QMessageBox::Yes){
                //使用冒泡排序
                QString temp="";
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list1[j].compare(list1[j+1])>0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                        }
                    }
                }
           }
           else{
                QString temp="";
                QStringList list2;
                for(int i=0;i<number;i++)//大写转化为小写进行比较，同时保留原来的显示方式
                {
                    QString str=list1[i];
                    str=str.toLower();
                    list2.append(str);
                }
                //使用冒泡排序
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j].compare(list2[j+1])>0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;

                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
           }

            //排序后把数据放回去
            for(int i=0;i<number;i++)
            {
                ui->tableWidget->item(i,list[i]->column())->setText(list1[i]);
            }
        }

        //数值排序
        if(flag==QMessageBox::No)
        {

            QList<double> list2;
            bool ok=true;
            for(int i=0;i<number;i++)
            {
                list2.append(list1[i].toDouble(&ok));
                //不允许有非数值数据
                if(!ok)
                {
                    QMessageBox::warning(this,"warning","选中列存在非数值数据！");
                    for(int j=0;j<number;j++)
                    {
                       ui->tableWidget->item(list[j]->row(),list[j]->column())->setText(list1[j]);
                    }
                    break;
                }
            }
            if(ok)
            {
                //使用冒泡排序
                double temp=0;
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j]>list2[j+1])
                        {
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
                for(int i=0;i<number;i++)
                {
                    ui->tableWidget->item(i,list[i]->column())->setText(QString::number(list2[i],'g',2));
                }
            }
        }
    }
}
//列降序
void MainWindow::on_pushButtonColumnSort2_clicked()
{
    //选中所选单元格的一整列
    QList<QTableWidgetItem*>list1 = ui->tableWidget->selectedItems();
    for(int i=0;i<list1.size();i++)
    {
        QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(0, list1[i]->column(),ui->tableWidget->rowCount()-1,list1[i]->column());
        ui->tableWidget->setRangeSelected(range, true);
    }

    if(QMessageBox::Yes==QMessageBox::question(this,"ques","是否已选好要排序的一列",QMessageBox::Yes|QMessageBox::No))
    {
        //剔除掉选中单元格中没有内容的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            if(list[i]->text()=="")
            {
                list.removeAt(i);
                i--;
            }
        }
        //判断剔除后还有没有数据用于排序
        if(list.size()==0)
        {
            QMessageBox::warning(this,"warning","所选区域没有数据！");
            return;
        }

        //不可选择多列数据进行排序
        int m=1;
        for(;m<list.size();m++)
        {
            if(list[m]->column()!=list[0]->column())
            {
                break;
            }
        }
        if(m!=list.size())
        {
            QMessageBox::warning(this,"warning","选中了多列具有数据的列，请重新选择！");
            return;
        }

        //选择排序方式
        QMessageBox mm(QMessageBox::Question,"ques","请选择排序方式",QMessageBox::Yes|QMessageBox::No);
        mm.button(QMessageBox::Yes)->setText("字符串排序");
        mm.button(QMessageBox::No)->setText("数值排序");
        int flag=mm.exec();

        //临时列表存储选中单元格的内容，用以辅助后续排序
        QStringList list1;
        int number=list.size();
        for(int i=0;i<number;i++)
        {
           QString str =list[i]->text();
           list1.append(str);

           ui->tableWidget->item(list[i]->row(),list[i]->column())->setText("");
        }

        //字符串排序
        if(flag==QMessageBox::Yes)
        {
            QMessageBox c(QMessageBox::Question,"ques","是否大小写敏感",QMessageBox::Yes|QMessageBox::No);
            c.button(QMessageBox::Yes)->setText("是");
            c.button(QMessageBox::No)->setText("否");
            int cap=c.exec();

           if(cap==QMessageBox::Yes){
                //使用冒泡排序
                QString temp="";
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list1[j].compare(list1[j+1])<0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                        }
                    }
                }
           }
           else{
                QString temp="";
                QStringList list2;
                for(int i=0;i<number;i++)//大写转化为小写进行比较，同时保留原来的显示方式
                {
                    QString str=list1[i];
                    str=str.toLower();
                    list2.append(str);
                }
                //使用冒泡排序
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j].compare(list2[j+1])<0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
           }
            //排序后把数据放回去
            for(int i=0;i<number;i++)
            {
                ui->tableWidget->item(i,list[i]->column())->setText(list1[i]);
            }
        }

        //数值排序
        if(flag==QMessageBox::No)
        {

            QList<double> list2;
            bool ok=true;
            for(int i=0;i<number;i++)
            {
                list2.append(list1[i].toDouble(&ok));
                //不允许有非数值数据
                if(!ok)
                {
                    QMessageBox::warning(this,"warning","选中列存在非数值数据！");
                    for(int j=0;j<number;j++)
                    {
                       ui->tableWidget->item(list[j]->row(),list[j]->column())->setText(list1[j]);
                    }
                    break;
                }
            }
            if(ok)
            {
                //使用冒泡排序
                double temp=0;
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j]<list2[j+1])
                        {
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
                for(int i=0;i<number;i++)
                {
                    ui->tableWidget->item(i,list[i]->column())->setText(QString::number(list2[i],'g',2));
                }
            }
        }
    }
}
//行升序
void MainWindow::on_pushButtonRowSort1_clicked()
{
    //选中所选单元格的一整行
    QList<QTableWidgetItem*>list1 = ui->tableWidget->selectedItems();
    for(int i=0;i<list1.size();i++)
    {
        QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(list1[i]->row(), 0, list1[i]->row(), ui->tableWidget->columnCount()-1);
        ui->tableWidget->setRangeSelected(range, true);
    }

    if(QMessageBox::Yes==QMessageBox::question(this,"ques","是否已选好要排序的一列",QMessageBox::Yes|QMessageBox::No))
    {
        //剔除掉选中单元格中没有内容的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            if(list[i]->text()=="")
            {
                list.removeAt(i);
                i--;
            }
        }
        //判断剔除后还有没有数据用于排序
        if(list.size()==0)
        {
            QMessageBox::warning(this,"warning","所选区域没有数据！");
            return;
        }

        //不可选择多行数据进行排序
        int m=1;
        for(;m<list.size();m++)
        {
            if(list[m]->row()!=list[0]->row())
            {
                break;
            }
        }
        if(m!=list.size())
        {
            QMessageBox::warning(this,"warning","选中了多行具有数据的行，请重新选择！");
            return;
        }

        //选择排序方式
        QMessageBox mm(QMessageBox::Question,"ques","请选择排序方式",QMessageBox::Yes|QMessageBox::No);
        mm.button(QMessageBox::Yes)->setText("字符串排序");
        mm.button(QMessageBox::No)->setText("数值排序");
        int flag=mm.exec();

        //临时列表存储选中单元格的内容，用以辅助后续排序
        QStringList list1;
        int number=list.size();
        for(int i=0;i<number;i++)
        {
           QString str =list[i]->text();
           list1.append(str);

           ui->tableWidget->item(list[i]->row(),list[i]->column())->setText("");
        }

        //字符串排序
        if(flag==QMessageBox::Yes)
        {
            QMessageBox c(QMessageBox::Question,"ques","是否大小写敏感",QMessageBox::Yes|QMessageBox::No);
            c.button(QMessageBox::Yes)->setText("是");
            c.button(QMessageBox::No)->setText("否");
            int cap=c.exec();

           if(cap==QMessageBox::Yes){
                //使用冒泡排序
                QString temp="";
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list1[j].compare(list1[j+1])>0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                        }
                    }
                }
           }
           else{
                QString temp="";
                QStringList list2;
                for(int i=0;i<number;i++)//大写转化为小写进行比较，同时保留原来的显示方式
                {
                    QString str=list1[i];
                    str=str.toLower();
                    list2.append(str);
                }
                //使用冒泡排序
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j].compare(list2[j+1])>0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
           }
            //使用冒泡排序
            QString temp="";
            for (int i=0; i<number-1; i++)
            {
                for (int j=0; j<number-1-i; j++)
                {
                    if (list1[j].compare(list1[j+1])>0)
                    {
                        temp = list1[j];
                        list1[j] = list1[j+1];
                        list1[j+1] = temp;
                    }
                }
            }
            //排序后把数据放回去
            for(int i=0;i<number;i++)
            {
                ui->tableWidget->item(list[i]->row(),i)->setText(list1[i]);
            }
        }

        //数值排序
        if(flag==QMessageBox::No)
        {
            QList<double> list2;
            bool ok=true;
            for(int i=0;i<number;i++)
            {
                list2.append(list1[i].toDouble(&ok));
                //不允许有非数值数据
                if(!ok)
                {
                    QMessageBox::warning(this,"warning","选中行存在非数值数据！");
                    for(int j=0;j<number;j++)
                    {
                       ui->tableWidget->item(list[j]->row(),list[j]->column())->setText(list1[j]);
                    }
                    break;
                }
            }
            if(ok)
            {
                //使用冒泡排序
                double temp=0;
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j]>list2[j+1])
                        {
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
                for(int i=0;i<number;i++)
                {
                    ui->tableWidget->item(list[i]->row(),i)->setText(QString::number(list2[i],'g',2));
                }
            }
        }
    }
}
//行降序
void MainWindow::on_pushButtonRowSort2_clicked()
{
    //选中所选单元格的一整行
    QList<QTableWidgetItem*>list1 = ui->tableWidget->selectedItems();
    for(int i=0;i<list1.size();i++)
    {
        QTableWidgetSelectionRange range  = QTableWidgetSelectionRange(list1[i]->row(), 0, list1[i]->row(), ui->tableWidget->columnCount()-1);
        ui->tableWidget->setRangeSelected(range, true);
    }

    if(QMessageBox::Yes==QMessageBox::question(this,"ques","是否已选好要排序的一列",QMessageBox::Yes|QMessageBox::No))
    {
        //剔除掉选中单元格中没有内容的单元格
        QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
        for(int i=0;i<list.size();i++)
        {
            if(list[i]->text()=="")
            {
                list.removeAt(i);
                i--;
            }
        }
        //判断剔除后还有没有数据用于排序
        if(list.size()==0)
        {
            QMessageBox::warning(this,"warning","所选区域没有数据！");
            return;
        }

        //不可选择多行数据进行排序
        int m=1;
        for(;m<list.size();m++)
        {
            if(list[m]->row()!=list[0]->row())
            {
                break;
            }
        }
        if(m!=list.size())
        {
            QMessageBox::warning(this,"warning","选中了多行具有数据的行，请重新选择！");
            return;
        }

        //选择排序方式
        QMessageBox mm(QMessageBox::Question,"ques","请选择排序方式",QMessageBox::Yes|QMessageBox::No);
        mm.button(QMessageBox::Yes)->setText("字符串排序");
        mm.button(QMessageBox::No)->setText("数值排序");
        int flag=mm.exec();

        //临时列表存储选中单元格的内容，用以辅助后续排序
        QStringList list1;
        int number=list.size();
        for(int i=0;i<number;i++)
        {
           QString str =list[i]->text();
           list1.append(str);

           ui->tableWidget->item(list[i]->row(),list[i]->column())->setText("");
        }

        //字符串排序
        if(flag==QMessageBox::Yes)
        {
            QMessageBox c(QMessageBox::Question,"ques","是否大小写敏感",QMessageBox::Yes|QMessageBox::No);
            c.button(QMessageBox::Yes)->setText("是");
            c.button(QMessageBox::No)->setText("否");
            int cap=c.exec();

           if(cap==QMessageBox::Yes){
                //使用冒泡排序
                QString temp="";
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list1[j].compare(list1[j+1])<0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                        }
                    }
                }
           }
           else{
                QString temp="";
                QStringList list2;
                for(int i=0;i<number;i++)//大写转化为小写进行比较，同时保留原来的显示方式
                {
                    QString str=list1[i];
                    str=str.toLower();
                    list2.append(str);
                }
                //使用冒泡排序
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j].compare(list2[j+1])<0)
                        {
                            temp = list1[j];
                            list1[j] = list1[j+1];
                            list1[j+1] = temp;
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
           }
            //排序后把数据放回去
            for(int i=0;i<number;i++)
            {
                ui->tableWidget->item(list[i]->row(),i)->setText(list1[i]);
            }
        }

        //数值排序
        if(flag==QMessageBox::No)
        {
            QList<double> list2;
            bool ok=true;
            for(int i=0;i<number;i++)
            {
                list2.append(list1[i].toDouble(&ok));
                //不允许有非数值数据
                if(!ok)
                {
                    QMessageBox::warning(this,"warning","选中行存在非数值数据！");
                    for(int j=0;j<number;j++)
                    {
                       ui->tableWidget->item(list[j]->row(),list[j]->column())->setText(list1[j]);
                    }
                    break;
                }
            }
            if(ok)
            {
                //使用冒泡排序
                double temp=0;
                for (int i=0; i<number-1; i++)
                {
                    for (int j=0; j<number-1-i; j++)
                    {
                        if (list2[j]<list2[j+1])
                        {
                            temp = list2[j];
                            list2[j] = list2[j+1];
                            list2[j+1] = temp;
                        }
                    }
                }
                //排序后把数据放回去
                for(int i=0;i<number;i++)
                {
                    ui->tableWidget->item(list[i]->row(),i)->setText(QString::number(list2[i],'g',2));
                }
            }
        }
    }
}
//求和公式
void MainWindow::on_pushButtonSum_clicked()
{
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    double sum=0;
    QString str;
    for(int i=0;i<list.length();i++)
    {
        str=list[i]->data(Qt::DisplayRole).toString();
        sum+=str.toDouble();
    }
    QString s=QString::number(sum);
    bool ok=false;
    int r=0,c=0;
    QString rr,cc;//需要插入的位置
    rr=QInputDialog::getText(this, tr("求和插入位置"),
                               tr("求和插入行数"), QLineEdit::Normal,
                               "", &ok);
    cc=QInputDialog::getText(this, tr("求和插入位置"),
                               tr("求和插入列数"), QLineEdit::Normal,
                               "", &ok);
    r=rr.toInt();
    c=cc.toInt();
    ui->tableWidget->setItem(r-1,c-1,new QTableWidgetItem(s));
}

//求平均值公式
void MainWindow::on_pushButtonAvg_clicked()
{
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    double sum=0;
    double avg=0;
    int num=0;
    QString str;
    for(int i=0;i<list.length();i++)
    {
        str=list[i]->data(Qt::DisplayRole).toString();
        if(str=="")
        {
            break;
        }
        sum+=str.toDouble();
        num++;
    }
    avg=sum/num;
    QString a=QString::number(avg);
    bool ok=false;
    int r=0,c=0;
    QString rr,cc;
    rr=QInputDialog::getText(this, tr("平均值插入位置"),
                               tr("平均值插入行数"), QLineEdit::Normal,
                               "", &ok);
    cc=QInputDialog::getText(this, tr("平均值插入位置"),
                               tr("平均值插入列数"), QLineEdit::Normal,
                               "", &ok);
    r=rr.toInt();
    c=cc.toInt();
    ui->tableWidget->setItem(r-1,c-1,new QTableWidgetItem(a));
}

//求最大值公式
void MainWindow::on_pushButtonMax_clicked()
{
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    double max;
    QString str;
    str=list[0]->data(Qt::DisplayRole).toString();
    max=str.toDouble();
    for(int i=0;i<list.length();i++)
    {
        str=list[i]->data(Qt::DisplayRole).toString();
        if(str=="")
        {
            break;
        }
        double temp;
        temp=str.toDouble();
        if(temp>max)
        {
            max=temp;
        }
    }
    QString a=QString::number(max);
    bool ok=false;
    int r=0,c=0;
    QString rr,cc;
    rr=QInputDialog::getText(this, tr("最大值插入位置"),
                               tr("最大值插入行数"), QLineEdit::Normal,
                               "", &ok);
    cc=QInputDialog::getText(this, tr("最大值插入位置"),
                               tr("最大值插入列数"), QLineEdit::Normal,
                               "", &ok);
    r=rr.toInt();
    c=cc.toInt();
    ui->tableWidget->setItem(r-1,c-1,new QTableWidgetItem(a));
}

//求最小值公式
void MainWindow::on_pushButtonMin_clicked()
{
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    double min;
    QString str;
    str=list[0]->data(Qt::DisplayRole).toString();
    min=str.toDouble();
    for(int i=0;i<list.length();i++)
    {
        str=list[i]->data(Qt::DisplayRole).toString();
        if(str=="")
        {
            break;
        }
        double temp;
        temp=str.toDouble();
        if(temp<min)
        {
            min=temp;
        }
    }
    QString a=QString::number(min);
    bool ok=false;
    int r=0,c=0;
    QString rr,cc;
    rr=QInputDialog::getText(this, tr("最小值插入位置"),
                               tr("最小值插入行数"), QLineEdit::Normal,
                               "", &ok);
    cc=QInputDialog::getText(this, tr("最小值插入位置"),
                               tr("最小值插入列数"), QLineEdit::Normal,
                               "", &ok);
    r=rr.toInt();
    c=cc.toInt();
    ui->tableWidget->setItem(r-1,c-1,new QTableWidgetItem(a));
}


/*获取操作符优先级*/
int MainWindow::Priority(QString data)
{
    int priority;
    if(data == "(")
        priority = 1;
    else if(data == "+" || data == "-")
        priority = 2;
    else if(data == "*" || data == "/")
        priority = 3;
    else if (data == ")")
        priority = 4;
    else
        priority = -1;
    return priority;
}

/*将表达式的数据，操作符分割，依次存入mask_buffer数组中*/
int MainWindow::mask_data(QString expression, QString *mask_buffer)
{
    int i,k = 0,cnt = 0;
    QString::iterator p = expression.begin();
    int length = expression.length();
    for(i = 0 ; i < length ; i += cnt,k++)
    {
        cnt = 0;
        if(*p >= '0' && *p <= '9')
        {
            QString temp = *p;
            p ++;
            cnt ++;
            while((*p >= '0' && *p <= '9') || *p == '.')
            {
                temp += *p;
                p++;
                cnt ++;
            }
            mask_buffer[k] = temp;
        }else
        {
            QString temp = *p;
            p++;
            cnt ++;
            mask_buffer[k] = temp;
        }
    }
    return k;
}

/*将获取到的分割好的表达式数组，转化为逆波兰表达式，存入数组repolish中*/
int MainWindow::re_polish(QString *mask_buffer,QString *repolish,int length)
{
    QStack<QString> st2;
    int i = 0;
    for(int j = 0 ; j < length ; j++)
    {
        if(mask_buffer[j] != "(" && mask_buffer[j] != ")" && mask_buffer[j] != "+" && mask_buffer[j] != "-" && mask_buffer[j] != "*" && mask_buffer[j] != "/" )
        {
            repolish[i++] = mask_buffer[j];
        }
        else if(mask_buffer[j] == "(")
        {
            st2.push(mask_buffer[j]);
        }
        else if(mask_buffer[j] == ")")
        {
            while(st2.top() != "(")
            {
                repolish[i++] = st2.top();
                st2.pop();
            }
            if(st2.top() == "(")
                st2.pop();
        }
        else if(st2.empty() || Priority(mask_buffer[j]) > Priority(st2.top()))
            st2.push(mask_buffer[j]);
        else
        {
            while(Priority(mask_buffer[j]) <= Priority(st2.top()))
            {
                repolish[i++] = st2.top();
                st2.pop();
                if(st2.empty())
                    break;
            }
            st2.push(mask_buffer[j]);
        }
    }
    while(!st2.empty())
    {
        repolish[i++] = st2.top();
        st2.pop();
    }
    return i;
}

/*计算逆波兰表达式值并显示*/
double MainWindow::repolish_calculat(QString *repolish,int length)
{
    QStack <double> st;
    for(int m = 0 ; m < length ; m ++)
    {
        if(repolish[m] != "+" && repolish[m] != "-" && repolish[m] != "*" && repolish[m] != "/" )
        {
            st.push(repolish[m].toDouble());
        }
        else
        {
            if(repolish[m] == "+")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                st.push(b + a);
            }
            else if(repolish[m] == "-")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                st.push(b - a);
            }
            else if(repolish[m] == "*")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                st.push(b * a);
            }
            else if(repolish[m] == "/")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                if(a != 0)
                   st.push(b/a);
                else
                {
                    QMessageBox msgBox;
                    msgBox.setText("除数为0！");
                    msgBox.exec();
                    return -1;
                }
            }
        }
    }
    QString res = QString::number(st.top(),'g',10);
    return st.top();
}






//其他公式
void MainWindow::on_pushButtonFuntion_clicked()
{


    //公式的规范格式：=ABC(a,b,c,d) ABC为公式名，a和b为开始单元格坐标，c和d为结束单元格坐标
    QString text;
    QList<QTableWidgetItem*>list = ui->tableWidget->selectedItems();
    text=list[0]->data(Qt::DisplayRole).toString();
    if(text[0]=="="&&text[1].isLetter()&&text.contains("(")&&text.contains(")")&&text.contains(","))//判断是否先输入了=，并判断是否输入（，）
    {
        QString formula=text.section('=',1,1);//取公式头，用来判断是什么公式
        QString function=formula.section('(',0,0);
        QString position=formula.section('(',1,1); //获取公式应用的范围
        QString temp=position.section(')',0,0);
        QStringList strlist=temp.split(',');//将坐标按，分隔开
        for(int i=0;i<strlist.length();i++)//判断是否选中的每一格都是纯数字
        {
            QString ss=strlist[i];
            for(int j=0;j<ss.length();j++)
            {
                if(!ss[j].isNumber())//判断，间是否为数字
                {
                    QMessageBox msgBox;
                    msgBox.setText("坐标错误！");
                    msgBox.exec();
                    return;
                }
            }
        }
        isFunction[list[0]->row()][list[0]->column()]=1;
        Functions[list[0]->row()][list[0]->column()]=text;
        if(function=="SUM")//求和函数
        {
            if(!(strlist.length()==4))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            QString position_x1=position.section(',',0,0);//开始单元格x坐标
            QString position_y1=temp.section(',',1,1);//开始单元格y坐标
            QString position_x2=temp.section(',',2,2);//结束单元格x坐标
            QString position_y2=temp.section(',',3,3);//结束单元格y坐标
            double sum=0;
            int x1=position_x1.toInt();int y1=position_y1.toInt();
            int x2=position_x2.toInt();int y2=position_y2.toInt();
            if(x1>x2)//将坐标调整为开始坐标<结束坐标
            {
                int tem=x2;
                x2=x1;
                x1=tem;
            }
            if(y1>y2)
            {
                int tem=y2;
                y2=y1;
                y1=tem;
            }
            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {
                    QString s=ui->tableWidget->item(i-1,j-1)->text();
                    sum+=s.toDouble();
                }
            }
            QString summary=QString::number(sum);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(summary);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double sum=0;
                for(int i=x1;i<=x2;i++)
                {
                    for(int j=y1;j<=y2;j++)
                    {
                        QString s=ui->tableWidget->item(i-1,j-1)->text();
                        sum+=s.toDouble();
                    }
                }
                QString summary=QString::number(sum);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(summary);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="AVG")//平均值函数
        {
            if(!(strlist.length()==4))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            QString position_x1=position.section(',',0,0);//开始单元格x坐标
            QString position_y1=temp.section(',',1,1);//开始单元格y坐标
            QString position_x2=temp.section(',',2,2);//结束单元格x坐标
            QString position_y2=temp.section(',',3,3);//结束单元格y坐标
            double sum=0,avg=0,num=0;
            int x1=position_x1.toInt();int y1=position_y1.toInt();
            int x2=position_x2.toInt();int y2=position_y2.toInt();
            if(x1>x2)
            {
                int tem=x2;
                x2=x1;
                x1=tem;
            }
            if(y1>y2)
            {
                int tem=y2;
                y2=y1;
                y1=tem;
            }
            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {
                    QString s=ui->tableWidget->item(i-1,j-1)->text();
                    sum+=s.toDouble();num++;
                }
            }
            avg=sum/num;
            QString average=QString::number(avg);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(average);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double sum=0,avg=0;
                int n=0;
                for(int i=x1;i<=x2;i++)
                {
                    for(int j=y1;j<=y2;j++)
                    {
                        QString s=ui->tableWidget->item(i-1,j-1)->text();
                        sum+=s.toDouble();
                        n++;
                    }
                }
                avg=sum/num;
                QString average=QString::number(avg);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(average);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="MAX")//最大值函数
        {
            if(!(strlist.length()==4))
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            QString position_x1=position.section(',',0,0);//开始单元格x坐标
            QString position_y1=temp.section(',',1,1);//开始单元格y坐标
            QString position_x2=temp.section(',',2,2);//结束单元格x坐标
            QString position_y2=temp.section(',',3,3);//结束单元格y坐标
            double max;
            int x1=position_x1.toInt();int y1=position_y1.toInt();
            int x2=position_x2.toInt();int y2=position_y2.toInt();
            if(x1>x2)
            {
                int tem=x2;
                x2=x1;
                x1=tem;
            }
            if(y1>y2)
            {
                int tem=y2;
                y2=y1;
                y1=tem;
            }
            QString init=ui->tableWidget->item(x1,y1)->text();//初始化max值
            max=init.toDouble();
            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {
                    QString s=ui->tableWidget->item(i-1,j-1)->text();
                    if(s=="")//如果当前单元格为空，则不计入
                    {
                        break;
                    }
                    double temp=s.toDouble();
                    if(temp>max)
                    {
                        max=temp;
                    }
                }
            }
            QString maximum=QString::number(max);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(maximum);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                QString init=ui->tableWidget->item(x1,y1)->text();//初始化max值
                double max=init.toDouble();
                for(int i=x1;i<=x2;i++)
                {
                    for(int j=y1;j<=y2;j++)
                    {
                        QString s=ui->tableWidget->item(i-1,j-1)->text();
                        if(s=="")//如果当前单元格为空，则不计入
                        {
                            break;
                        }
                        double temp=s.toDouble();
                        if(temp>max)
                        {
                            max=temp;
                        }
                    }
                }
                QString maximum=QString::number(max);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(maximum);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="MIN")//最小值函数
        {
            if(!(strlist.length()==4))
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            QString position_x1=position.section(',',0,0);//开始单元格x坐标
            QString position_y1=temp.section(',',1,1);//开始单元格y坐标
            QString position_x2=temp.section(',',2,2);//结束单元格x坐标
            QString position_y2=temp.section(',',3,3);//结束单元格y坐标
            double min;
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            int x2=position_x2.toInt();
            int y2=position_y2.toInt();
            if(x1>x2)
            {
                int tem=x2;
                x2=x1;
                x1=tem;
            }
            if(y1>y2)
            {
                int tem=y2;
                y2=y1;
                y1=tem;
            }
            QString init=ui->tableWidget->item(x1,y1)->text();
            min=init.toDouble();
            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {
                    QString s=ui->tableWidget->item(i-1,j-1)->text();
                    if(s=="")//如果当前单元格为空，则不计入，避免0的情况
                    {
                        break;
                    }
                    double temp=s.toDouble();
                    if(temp<min)
                    {
                        min=temp;
                    }
                }
            }
            QString minimum=QString::number(min);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(minimum);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                QString init=ui->tableWidget->item(x1,y1)->text();//初始化max值
                double min=init.toDouble();
                for(int i=x1;i<=x2;i++)
                {
                    for(int j=y1;j<=y2;j++)
                    {
                        QString s=ui->tableWidget->item(i-1,j-1)->text();
                        if(s=="")//如果当前单元格为空，则不计入
                        {
                            break;
                        }
                        double temp=s.toDouble();
                        if(temp<min)
                        {
                            min=temp;
                        }
                    }
                }
                QString minimum=QString::number(min);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(minimum);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="COUNT")//计数函数
        {
            if(!(strlist.length()==4))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            QString position_x1=position.section(',',0,0);//开始单元格x坐标
            QString position_y1=temp.section(',',1,1);//开始单元格y坐标
            QString position_x2=temp.section(',',2,2);//结束单元格x坐标
            QString position_y2=temp.section(',',3,3);//结束单元格y坐标
            double num=0;
            int x1=position_x1.toInt();int y1=position_y1.toInt();
            int x2=position_x2.toInt();int y2=position_y2.toInt();
            if(x1>x2)
            {
                int tem=x2;
                x2=x1;
                x1=tem;
            }
            if(y1>y2)
            {
                int tem=y2;
                y2=y1;
                y1=tem;
            }
            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {

                    QString s=ui->tableWidget->item(i-1,j-1)->text();
                    if(s=="")//如果当前单元格为空，则不计入
                    {
                        break;
                    }
                    num++;
                }
            }
            QString number=QString::number(num);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                int num=0;
                for(int i=x1;i<=x2;i++)
                {
                    for(int j=y1;j<=y2;j++)
                    {

                        QString s=ui->tableWidget->item(i-1,j-1)->text();
                        if(s=="")//如果当前单元格为空，则不计入
                        {
                            break;
                        }
                        num++;
                    }
                }
                QString number=QString::number(num);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="POWER")//幂函数
        {
            if(!(strlist.length()==2))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            double result=0;
            QString position_x1=position.section(',',0,0);//单元格x坐标
            QString position_y1=temp.section(',',1,1);//单元格y坐标
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            double p=temp.section(',',2,2).toDouble();
            QString s=ui->tableWidget->item(x1-1,y1-1)->text();
            if(s=="")//如果当前单元格为空，则不计入
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内无值！");
                msgBox.exec();
                return;
            }
            result=pow(s.toDouble(),p);
            QString number=QString::number(result);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double result=0;
                double p=temp.section(',',2,2).toDouble();
                QString s=ui->tableWidget->item(x1-1,y1-1)->text();
                if(s=="")//如果当前单元格为空，则不计入
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内无值！");
                    msgBox.exec();
                    return;
                }
                result=pow(s.toDouble(),p);
                QString number=QString::number(result);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="SQRT")//开平方
        {
            if(!(strlist.length()==2))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            double result=0;
            QString position_x1=position.section(',',0,0);//单元格x坐标
            QString position_y1=temp.section(',',1,1);//单元格y坐标
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            QString s=ui->tableWidget->item(x1-1,y1-1)->text();
            if(s=="")//如果当前单元格为空，则不计入
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内无值！");
                msgBox.exec();
                return;
            }
            if(s.toDouble()<0)
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内为负值！");
                msgBox.exec();
                return;
            }
            result=sqrt(s.toDouble());
            QString number=QString::number(result);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double result=0;
                QString s=ui->tableWidget->item(x1-1,y1-1)->text();
                if(s=="")//如果当前单元格为空，则不计入
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内无值！");
                    msgBox.exec();
                    return;
                }
                if(s.toDouble()<0)
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内为负值！");
                    msgBox.exec();
                    return;
                }
                result=sqrt(s.toDouble());
                QString number=QString::number(result);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="EXP")//e的n次幂
        {
            if(!(strlist.length()==2))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            double result=0;
            QString position_x1=position.section(',',0,0);//单元格x坐标
            QString position_y1=temp.section(',',1,1);//单元格y坐标
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            QString s=ui->tableWidget->item(x1-1,y1-1)->text();
            if(s=="")//如果当前单元格为空，则不计入
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内无值！");
                msgBox.exec();
                return;
            }
            result=exp(s.toDouble());
            QString number=QString::number(result);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double result=0;
                QString s=ui->tableWidget->item(x1-1,y1-1)->text();
                if(s=="")//如果当前单元格为空，则不计入
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内无值！");
                    msgBox.exec();
                    return;
                }
                result=exp(s.toDouble());
                QString number=QString::number(result);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="MOD")//取余函数
        {
            if(strlist.length()==4)
            {
                QString position_x1=position.section(',',0,0);//开始单元格x坐标
                QString position_y1=temp.section(',',1,1);//开始单元格y坐标
                QString position_x2=temp.section(',',2,2);//结束单元格x坐标
                QString position_y2=temp.section(',',3,3);//结束单元格y坐标
                double result=0;
                int x1=position_x1.toInt();int y1=position_y1.toInt();
                int x2=position_x2.toInt();int y2=position_y2.toInt();
                double n=ui->tableWidget->item(x1,y1)->text().toDouble();
                double m=ui->tableWidget->item(x2,y2)->text().toDouble();
                if(m==0)
                {
                    QMessageBox msgBox;
                    msgBox.setText("除数为0，错误");
                    msgBox.exec();
                    return;
                }
                result=fmod(n,m);
                QString number=QString::number(result);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                        {   ui->tableWidget->blockSignals(true);
                    double result=0;
                    double n=ui->tableWidget->item(x1,y1)->text().toDouble();
                    double m=ui->tableWidget->item(x2,y2)->text().toDouble();
                    if(m==0)
                    {
                        QMessageBox msgBox;
                        msgBox.setText("除数为0，错误");
                        msgBox.exec();
                        return;
                    }
                    result=fmod(n,m);
                    QString number=QString::number(result);
                    ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                    ui->tableWidget->blockSignals(false);});
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误");
                msgBox.exec();
                return;
            }

        }
        else if(function=="LN")//对数函数（以e为底）
        {
            if(!(strlist.length()==2))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            double result=0;
            QString position_x1=position.section(',',0,0);//单元格x坐标
            QString position_y1=temp.section(',',1,1);//单元格y坐标
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            QString s=ui->tableWidget->item(x1-1,y1-1)->text();
            if(s=="")//如果当前单元格为空，则不计入
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内无值！");
                msgBox.exec();
                return;
            }
            if(s.toDouble()<0)
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内为负值！");
                msgBox.exec();
                return;
            }
            result=log(s.toDouble());
            QString number=QString::number(result);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double result=0;
                QString position_x1=position.section(',',0,0);//单元格x坐标
                QString position_y1=temp.section(',',1,1);//单元格y坐标
                int x1=position_x1.toInt();
                int y1=position_y1.toInt();
                QString s=ui->tableWidget->item(x1-1,y1-1)->text();
                if(s=="")//如果当前单元格为空，则不计入
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内无值！");
                    msgBox.exec();
                    return;
                }
                if(s.toDouble()<0)
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内为负值！");
                    msgBox.exec();
                    return;
                }
                result=log(s.toDouble());
                QString number=QString::number(result);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="LOG")//对数函数（自定义底数）
        {
            if(!(strlist.length()==3))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            double result=0;
            QString position_x1=position.section(',',0,0);//单元格x坐标
            QString position_y1=temp.section(',',1,1);//单元格y坐标
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            double n=temp.section(',',2,2).toDouble();
            QString s=ui->tableWidget->item(x1-1,y1-1)->text();
            if(s=="")//如果当前单元格为空，则不计入
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内无值！");
                msgBox.exec();
                return;
            }
            if(s.toDouble()<0)
            {
                QMessageBox msgBox;
                msgBox.setText("当前单元格内为负值！");
                msgBox.exec();
                return;
            }
            result=log(s.toDouble())/log(n);
            QString number=QString::number(result);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
            connect(ui->tableWidget,&QTableWidget::cellChanged,this,[=]()
                    {   ui->tableWidget->blockSignals(true);
                double result=0;
                double n=temp.section(',',2,2).toDouble();
                QString s=ui->tableWidget->item(x1-1,y1-1)->text();
                if(s=="")//如果当前单元格为空，则不计入
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内无值！");
                    msgBox.exec();
                    return;
                }
                if(s.toDouble()<0)
                {
                    QMessageBox msgBox;
                    msgBox.setText("当前单元格内为负值！");
                    msgBox.exec();
                    return;
                }
                result=log(s.toDouble())/log(n);
                QString number=QString::number(result);
                ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
                ui->tableWidget->blockSignals(false);});
        }
        else if(function=="RAND")//随机数生成函数
        {
            if(!(strlist.length()==2))//判断坐标个数是否满足
            {
                QMessageBox msgBox;
                msgBox.setText("坐标错误！");
                msgBox.exec();
                return;
            }
            srand(time(0));
            double result=0;
            QString position_x1=position.section(',',0,0);//单元格x坐标
            QString position_y1=temp.section(',',1,1);//单元格y坐标
            int x1=position_x1.toInt();
            int y1=position_y1.toInt();
            if(x1<=y1)
            {
                QMessageBox msgBox;
                msgBox.setText("范围错误！");
                msgBox.exec();
                return;
            }
            if(x1==0 && y1==1)
            {
                result=rand()/RAND_MAX;
            }
            else
            {
                result=x1+rand()%(y1-x1+1);
            }
            QString number=QString::number(result);
            ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(number);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("公式错误或不存在此公式");
            msgBox.exec();
        }
    }
    else if(text[0]=="=")
    {
        QString expression=text.section('=',1,1);
        QString mask_buffer[100]={"0"},repolish[100]={"0"};
        int length = mask_data(expression,mask_buffer);
        length = re_polish(mask_buffer,repolish,length);
        double result = repolish_calculat(repolish,length);
        QString s=QString::number(result);
        ui->tableWidget->item(list[0]->row(),list[0]->column())->setText(s);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("非公式格式！");
        msgBox.exec();
    }
}






//右键弹出菜单
void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;

    //选中全表
    QAction *selectAll = menu.addAction(tr("全选"));
    connect(selectAll, &QAction::triggered, [=](){
        ui->tableWidget->selectAll();
    });

    //插入分隔线
    menu.addSeparator();

    //复制
    QAction *copy = menu.addAction("复制");
    connect(copy, &QAction::triggered, [=](){
        emit ui->pushButtonCopy->clicked();
    });
    //粘贴
    QAction *Paste = menu.addAction("粘贴");
    connect(Paste, &QAction::triggered, [=](){
        emit ui->pushButtonPaste->clicked();
    });

    menu.addSeparator();

    //插入
    QMenu *insert=menu.addMenu("插入");
    QAction *rowinsert = insert->addAction("行插入");
    QAction *columinsert = insert->addAction("列插入");
    connect(rowinsert, &QAction::triggered, [=](){
        emit ui->pushButtonRowInsert->clicked();
    });
    connect(columinsert, &QAction::triggered, [=](){
        emit ui->pushButtonColumnInsert->clicked();
    });

    //删除
    QMenu *delete1=menu.addMenu("删除");
    QAction *rowdelete = delete1->addAction("行删除");
    QAction *columdelete = delete1->addAction("列删除");
    QAction *alldelete = delete1->addAction("全表删除");
    connect(rowdelete, &QAction::triggered, [=](){
        emit ui->pushButtonRowDelete->clicked();
    });
    connect(columdelete, &QAction::triggered, [=](){
        emit ui->pushButtonColumnDelete->clicked();
    });
    connect(alldelete, &QAction::triggered, [=](){
        emit ui->pushButtonTableDelete->clicked();
    });

    menu.addSeparator();

    //显示菜单
    menu.exec(QCursor::pos());
}
