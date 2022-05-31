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

    if(item->checkState(0) == Qt::Checked)
    {
        //output_Model->clear();
        QString txt = item->text(cloumn);
        QStandardItem *sd_item = new QStandardItem(txt);
        output_Model->appendRow(sd_item);

        for(int i = 0;i < item->childCount();i++)//根节点,全部信号
        {
            //设置tree所有子节点被选中
            item->child(i)->setCheckState(cloumn,Qt::Checked);

            //这里不用appendRow,因为设置了checkstate,系统自动调用onItemChanged_In,执行子节点
            //设置list view 显示所有信号
            //QString txt = item->child(i)->text(cloumn);
            //QStandardItem *sd_item = new QStandardItem(txt);
            //input_Model->appendRow(sd_item);
        }

        //父项根据所有子项的勾选状态设置勾选状态
        auto parentItem = item->parent();
        if(parentItem && (parentItem->checkState(0) != Qt::Checked))
        {
            auto friendCount = parentItem->childCount();
            bool allFriendIsCheck = true;
            for(int j = 0; j < friendCount; ++j)
            {
                if(parentItem->child(j)->checkState(0) != Qt::Checked)
                {
                    allFriendIsCheck = false;
                    break;
                }
            }
            if(allFriendIsCheck)
            {
                parentItem->setCheckState(0, Qt::Checked);
            }
            else
            {
                parentItem->setCheckState(0, Qt::PartiallyChecked);
            }
        }
    }
    else if(item->checkState(0) == Qt::Unchecked)
    {
        auto childCount = item->childCount();
        //设置子项相同勾选状态
        for(int i = 0; i < childCount; ++i){
            item->child(i)->setCheckState(0, Qt::Unchecked);
        }
        if(cloumn < output_Model->rowCount())
        {
            //删除listview的item
            delteOutputListView(item->text(cloumn));
        }
        //父项根据所有子项的勾选状态设置勾选状态
        auto parentItem = item->parent();
        if(parentItem && (parentItem->checkState(0) != Qt::Unchecked)){
            auto friendCount = parentItem->childCount();
            bool allFriendIsUncheck = true;
            for(int j = 0; j < friendCount; ++j){
                if(parentItem->child(j)->checkState(0) != Qt::Unchecked){
                    allFriendIsUncheck = false;
                    break;
                }
            }
            if(allFriendIsUncheck){
                parentItem->setCheckState(0, Qt::Unchecked);
            } else{
                parentItem->setCheckState(0, Qt::PartiallyChecked);
            }
        }
    } else if(item->checkState(0) == Qt::PartiallyChecked){
        auto parentItem = item->parent();
        if(parentItem){ //设置父项相同勾选状态
            parentItem->setCheckState(0, Qt::PartiallyChecked);
        }
    }

    ui->outputlistView->setModel(output_Model);
}

void MainWindow::onInputDataChange(QString txt)
{
    qDebug()<<"data change :"<<txt;
}

void MainWindow::onInputDataFinished()
{
    qDebug()<<"data finish";
}

//删除指定的item
void MainWindow::deleteListWidgetItem(QString text)
{
#if 1
    int row=0;
    QString line;
    while(row<(ui->inputlistWidget->count()))
    {
        //line = ui->inputlistWidget->item(row)->text();
        QListWidgetItem* pItem = ui->inputlistWidget->item(row);
        line = pItem->text();
        qDebug()<<line;
        qDebug()<<ui->inputlistWidget->item(row);
        if(text==line)
        {
            qDebug()<<"删除成功";
            ui->inputlistWidget->takeItem(row);
        }

        row++;
    }
#else
    if(row < ui->inputlistWidget->count() && row >= 0)
    {
        //删除
        ui->inputlistWidget->takeItem(row);
        qDebug()<<"del:"<<row;
    }
#endif
}
//输入tree widget事件处理
void MainWindow::onItemChanged_In(QTreeWidgetItem *item, int cloumn)
{
    qDebug() <<item->text(cloumn) <<"Cl:"<<cloumn<<" CK:"<<item->checkState(0)<<" child:"<<item->childCount();

    if(item->checkState(0) == Qt::Checked)
    {
        //output_Model->clear();
        if(item->childCount() == 0)//只添加子节点
        {
            QString txt = item->text(cloumn);
            QStandardItem *sd_item = new QStandardItem(txt);
            input_Model->appendRow(sd_item);

            //dataForm *nitem = new dataForm();
            //ui->inputlistWidget->insertItem(0,txt);
            QWidget *widget = new QWidget(ui->inputlistWidget);
            QLabel *Label = new QLabel(widget);
            //Label->setText(txt);
            Label->setFrameShape(QFrame::Box);


            QLineEdit *LineEdit = new QLineEdit(ui->inputlistWidget);
            LineEdit->setText("xuzd");
            //connect(LineEdit,SINGAL(LineEdit::on_lineEdit_textChanged(QString& )),this,SLOT(onInputDataChange()));
            connect(LineEdit,SIGNAL(textChanged(QString)),this,SLOT(onInputDataChange(QString)));
            //connect(LineEdit,SIGNAL(returnPressed()),this,SLOT(onInputDataFinished()));
            connect(LineEdit,SIGNAL(editingFinished()),this,SLOT(onInputDataFinished()));

            //创见水平布局
            QHBoxLayout *horLayout = new QHBoxLayout;
            horLayout->setContentsMargins(0, 0, 0, 0);
            horLayout->setMargin(2);
            horLayout->setSpacing(2);

            horLayout->addWidget(Label,5);
            //horLayout->addStretch(1);
            horLayout->addWidget(LineEdit,1);
            widget->setLayout(horLayout);

            //将widget作为列表的item
            QListWidgetItem *ITEM = new QListWidgetItem();
            ITEM->setText(txt);

            QSize size = ITEM->sizeHint();
            ITEM->setSizeHint(QSize(size.width(), 40));
            ui->inputlistWidget->addItem(ITEM);
            widget->setSizeIncrement(size.width(), 40);
            ui->inputlistWidget->setItemWidget(ITEM, widget);//添加项目,每个item应该自己是一个类

        }
        for(int i = 0;i < item->childCount();i++)//根节点,全部信号
        {
            //设置tree所有子节点被选中
            item->child(i)->setCheckState(cloumn,Qt::Checked);

            //这里不用appendRow,因为设置了checkstate,系统自动调用onItemChanged_In,执行子节点
            //设置list view 显示所有信号
            //QString txt = item->child(i)->text(cloumn);
            //QStandardItem *sd_item = new QStandardItem(txt);
            //input_Model->appendRow(sd_item);
        }

        //父项根据所有子项的勾选状态设置勾选状态,点击父节点,会自动勾选子节点
        auto parentItem = item->parent();
        if(parentItem && (parentItem->checkState(0) != Qt::Checked))
        {
            auto friendCount = parentItem->childCount();
            bool allFriendIsCheck = true;
            for(int j = 0; j < friendCount; ++j)
            {
                if(parentItem->child(j)->checkState(0) != Qt::Checked)
                {
                    allFriendIsCheck = false;
                    break;
                }
            }
            if(allFriendIsCheck)
            {
                parentItem->setCheckState(0, Qt::Checked);
            }
            else
            {
                parentItem->setCheckState(0, Qt::PartiallyChecked);
            }
        }
    }
    else if(item->checkState(0) == Qt::Unchecked)
    {
        auto childCount = item->childCount();
        //设置子项相同勾选状态
        for(int i = 0; i < childCount; ++i)
        {
            item->child(i)->setCheckState(0, Qt::Unchecked);
        }
        if(cloumn < input_Model->rowCount())
        {
            //删除listview的item
            deleteListWidgetItem(item->text(cloumn));
            //deleteListWidgetItem(cloumn);
        }
        //父项根据所有子项的勾选状态设置勾选状态
        auto parentItem = item->parent();
        if(parentItem && (parentItem->checkState(0) != Qt::Unchecked))
        {
            auto friendCount = parentItem->childCount();
            bool allFriendIsUncheck = true;
            for(int j = 0; j < friendCount; ++j)
            {
                if(parentItem->child(j)->checkState(0) != Qt::Unchecked)
                {
                    allFriendIsUncheck = false;
                    break;
                }
            }
            if(allFriendIsUncheck)
            {
                parentItem->setCheckState(0, Qt::Unchecked);
            } else{
                parentItem->setCheckState(0, Qt::PartiallyChecked);
            }
        }
    } else if(item->checkState(0) == Qt::PartiallyChecked)
    {
        auto parentItem = item->parent();
        if(parentItem)
        { //设置父项相同勾选状态
            parentItem->setCheckState(0, Qt::PartiallyChecked);
        }
    }

    //ui->inputlistView->setModel(input_Model);
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

