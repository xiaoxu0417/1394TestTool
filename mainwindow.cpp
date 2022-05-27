#include "mainwindow.h"
#include "ui_mainwindow.h"

extern "C"
{
    #include "dll.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化input和output tree wiget
    initTreeWiget();

    //绑定槽函数
    connectWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::delteOutputListView(QString text)
{
    //找到text的索引,将其删除
    //input_Model->findItems(text);//返回QList
    for(int i = 0;i < output_Model->rowCount();i++)
    {
        QModelIndex curIndex =output_Model->index(i,0);
        QStandardItem *curItem = output_Model->itemFromIndex(curIndex);
        QString curItemName = curItem->text();
        if(curItemName == text)
        {
            output_Model->removeRow(i);
        }
    }
}

void MainWindow::delteInputListView(QString text)
{
    //找到text的索引,将其删除
    //input_Model->findItems(text);//返回QList
    for(int i = 0;i < input_Model->rowCount();i++)
    {
        QModelIndex curIndex =input_Model->index(i,0);
        QStandardItem *curItem = input_Model->itemFromIndex(curIndex);
        QString curItemName = curItem->text();
        if(curItemName == text)
        {
            input_Model->removeRow(i);
        }
    }
}

//输出tree widget事件处理
void MainWindow::onItemChanged_Out(QTreeWidgetItem *item, int cloumn)
{
    qDebug() <<item->text(cloumn) <<"Cl:"<<cloumn<<" CK:"<<item->checkState(0)<<" child:"<<item->childCount();
    if(item->childCount() > 0)//根节点,全部信号
    {
        if(item->checkState(0) == Qt::Checked)
        {
            output_Model->clear();
            for(int i = 0;i < item->childCount();i++)
            {
                //设置tree所有子节点被选中
                item->child(i)->setCheckState(cloumn,Qt::Checked);

                //这里不用appendRow,因为设置了checkstate,系统自动调用onItemChanged_In,执行子节点
                //设置list view 显示所有信号
                //QString txt = item->child(i)->text(cloumn);
                //QStandardItem *sd_item = new QStandardItem(txt);
                //input_Model->appendRow(sd_item);
            }
        }
        else if(item->checkState(0) == Qt::Unchecked)
        {
            output_Model->clear();
            for(int i = 0;i < item->childCount();i++)
            {
                //设置tree所有子节点均未被选中
                item->child(i)->setCheckState(cloumn,Qt::Unchecked);
            }
        }
    }
    else//子节点,一个信号
    {
        if(item->checkState(0) == Qt::Checked)
        {
            QString txt = item->text(cloumn);
            QStandardItem *sd_item = new QStandardItem(txt);
            output_Model->appendRow(sd_item);
            item->parent()->setCheckState(cloumn,Qt::PartiallyChecked);
        }
        else
        {
            if(cloumn < output_Model->rowCount())
            {
                //删除listview的item
                delteOutputListView(item->text(cloumn));
            }

        }
    }
    ui->outputlistView->setModel(output_Model);
}

//输入tree widget事件处理
void MainWindow::onItemChanged_In(QTreeWidgetItem *item, int cloumn)
{
    qDebug() <<item->text(cloumn) <<"Cl:"<<cloumn<<" CK:"<<item->checkState(0)<<" child:"<<item->childCount();
    if(item->childCount() > 0)//根节点,全部信号
    {
        if(item->checkState(0) == Qt::Checked)
        {
            input_Model->clear();
            for(int i = 0;i < item->childCount();i++)
            {
                //设置tree所有子节点被选中
                item->child(i)->setCheckState(cloumn,Qt::Checked);

                //这里不用appendRow,因为设置了checkstate,系统自动调用onItemChanged_In,执行子节点
                //设置list view 显示所有信号
                //QString txt = item->child(i)->text(cloumn);
                //QStandardItem *sd_item = new QStandardItem(txt);
                //input_Model->appendRow(sd_item);
            }
        }
        else if(item->checkState(0) == Qt::Unchecked)
        {
            input_Model->clear();
            for(int i = 0;i < item->childCount();i++)
            {
                //设置tree所有子节点均未被选中
                item->child(i)->setCheckState(cloumn,Qt::Unchecked);
            }
        }
    }
    else//子节点,一个信号
    {
        if(item->checkState(0) == Qt::Checked)
        {
            QString txt = item->text(cloumn);
            QStandardItem *sd_item = new QStandardItem(txt);
            input_Model->appendRow(sd_item);
            //设置状态后会再调用一次itemchange
            item->parent()->setCheckState(cloumn,Qt::PartiallyChecked);
        }
        else if(item->checkState(0) == Qt::Unchecked)
        {
            if(cloumn < input_Model->rowCount())
            {
                //删除listview的item
                delteInputListView(item->text(cloumn));
            }

        }
    }
    ui->inputlistView->setModel(input_Model);
}

void MainWindow::connectWidget()
{
    connect(ui->inputtreeWidget, &QTreeWidget::itemChanged, this, &MainWindow::onItemChanged_In);
    connect(ui->outputtreeWidget, &QTreeWidget::itemChanged, this, &MainWindow::onItemChanged_Out);
}

void MainWindow::doTimerService()
{
    //QTime相减
    end = QTime::currentTime();//获取当前时间
    int m_iTestTime = begin.msecsTo(end)/1000;
    ulong ulHour = m_iTestTime / 3600;
    ulong ulMinute = (m_iTestTime - ulHour * 3600) / 60;
    ulong ulSecond = (m_iTestTime - ulHour * 3600 - ulMinute * 60);

    QString strTime = QString("%1:%2:%3").arg(ulHour,2, 10, QChar('0')).arg(ulMinute,2, 10, QChar('0') ).arg(ulSecond,2, 10, QChar('0'));

    ui->lcdNumber_counting->display(strTime);
    qDebug()<<m_iTestTime;
}
void MainWindow::initTreeWiget()
{
    input_Model = new QStandardItemModel(this);
    output_Model = new QStandardItemModel(this);

    QStringList in_head;
    in_head << tr("数据输入:");

    QStringList out_head;
    out_head <<"数据输出:";

    //m_inputTreeWidget = new QTreeWidget;
    //m_inputTreeWidget->setHeaderLabels(headers);

    //第一个跟节点 debug
    auto item_oil_in = new QTreeWidgetItem;
    item_oil_in->setText(0, "oil");
    item_oil_in->setCheckState(0, Qt::Unchecked);
    //m_inputTreeWidget->addTopLevelItem(item);
    for (int i = 0;i <30; i++)
    {
        auto ch = new QTreeWidgetItem(QStringList()<<"oil"+QString::number(i));
        ch->setCheckState(0,Qt::Unchecked);//默认没有check box
        item_oil_in->addChild(ch);
    }

    //第二个跟节点
    auto item_fire_in = new QTreeWidgetItem;
    item_fire_in->setText(0, "fire");
    item_fire_in->setCheckState(0, Qt::Unchecked);
    for (int i = 0;i <10; i++)
    {
        auto ch = new QTreeWidgetItem(QStringList()<<"fire_"+QString::number(i));
        ch->setCheckState(0,Qt::Unchecked);//默认没有check box
        item_fire_in->addChild(ch);
    }

    ui->inputtreeWidget->setHeaderLabels(in_head);
    ui->inputtreeWidget->addTopLevelItem(item_oil_in);
    ui->inputtreeWidget->addTopLevelItem(item_fire_in);
    ui->inputtreeWidget->expandAll();

    //===============out put===================
    //第一个跟节点 debug
    auto item_oil_out = new QTreeWidgetItem;
    item_oil_out->setText(0, "oil");
    item_oil_out->setCheckState(0, Qt::Unchecked);

    for (int i = 0;i <30; i++)
    {
        auto ch = new QTreeWidgetItem(QStringList()<<"oil"+QString::number(i));
        ch->setCheckState(0,Qt::Unchecked);//默认没有check box
        item_oil_out->addChild(ch);
    }
    ui->outputtreeWidget->addTopLevelItem(item_oil_out);
    ui->outputtreeWidget->expandAll();
    ui->outputtreeWidget->setHeaderLabels(out_head);

    //
    bUseCounting = false;
    countTimer = new QTimer(this);
    countTimer->setInterval(100);
    //connect(countTimer,SIGNAL(timeout()),this,SLOT(MainWindow::doTimerService));
    connect(countTimer,&QTimer::timeout,this,&MainWindow::doTimerService);
    //ui->lcdNumber_counting->setStyleSheet(QLCDNumber{color: red});
    ui->lcdNumber_counting->setFont(QFont("Times",12,QFont::Black));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    bUseCounting = arg1 == 2?true:false;
    //qDebug() <<bUseCounting <<" "<< arg1;
    if(bUseCounting)
    {
        ui->pushButton_start_counting->setEnabled(false);
        //ui->pushButton_stop_counting->setEnabled(false);
        //ui->pushButton_clear_counting->setEnabled(false);
    }
    else
    {
        ui->pushButton_start_counting->setEnabled(true);
        //ui->pushButton_stop_counting->setEnabled(true);
        //ui->pushButton_clear_counting->setEnabled(true);
    }
}

void MainWindow::on_pushButton_process_clicked()
{
    if(bUseCounting)
    {
        countTimer->start();
        begin = QTime::currentTime();//获取当前时间
    }
}

void MainWindow::on_pushButton_start_counting_clicked()
{
    if(!bUseCounting)
    {
        countTimer->start();
        begin = QTime::currentTime();//获取当前时间
    }
    ui->pushButton_start_counting->setEnabled(false);
}

void MainWindow::on_pushButton_stop_counting_clicked()
{
    if(countTimer->isActive())
    {
        countTimer->stop();
        end = QTime::currentTime();//获取当前时间
        if(!bUseCounting)
        {
            ui->pushButton_start_counting->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_clear_counting_clicked()
{
//    if(!countTimer->isActive())
//    {
//        ui->lcdNumber_counting->display(0);
//        ui->pushButton_start_counting->setEnabled(true);
//        ui->pushButton_stop_counting->setEnabled(false);
//    }
    if(countTimer->isActive())
    {
        countTimer->stop();
    }
    ui->lcdNumber_counting->display(0);
}
