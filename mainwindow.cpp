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

    loadxml();
    //初始化input和output tree wiget
    //initTreeWiget();

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



//删除指定的item
void MainWindow::deleteListWidgetItem(QString text)
{
#if 1
    int row=0;
    QString line;
    while(row<(ui->inputlistWidget->count()))
    {
        QListWidgetItem* pItem = ui->inputlistWidget->item(row);
        line = pItem->text();
        //qDebug()<<line;
        //qDebug()<<ui->inputlistWidget->item(row);
        if(text==line)
        {
            //qDebug()<<"删除成功:"<<text;
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
    //qDebug() <<item->text(cloumn) <<"Cl:"<<cloumn<<" CK:"<<item->checkState(0)<<" child:"<<item->childCount();

    if(item->checkState(0) == Qt::Checked)
    {

        if(item->childCount() == 0)//只添加子节点
        {
            QString txt = item->text(cloumn);

            //QWidget *widget = new QWidget(ui->inputlistWidget);
            QWidget *widget = new QWidget();
            QLabel *Label = new QLabel(widget);
            //Label->setText(txt);
            Label->setFrameShape(QFrame::Box);


            QLineEdit *LineEdit = new QLineEdit(ui->inputlistWidget);
            LineEdit->setText("0");

            //绑定每个lineEdit的槽函数
            TreeWidgetItemEx *pItem = dynamic_cast<TreeWidgetItemEx*>(item);
            CDataControl *Ctl = new CDataControl(pItem->getBitbegin(),pItem->getBitend(),pItem->getOffset(),pItem->getDatatype());
            connect(LineEdit,SIGNAL(textChanged(QString)),Ctl,SLOT(onInputDataChange(QString)));
            connect(LineEdit,SIGNAL(editingFinished()),Ctl,SLOT(onInputDataFinished()));

            //创建水平布局
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
        }

        //父项根据所有子项的勾选状态设置勾选状态,点击父节点,会自动勾选子节点
        auto parentItem = item->QTreeWidgetItem::parent();

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

        if(cloumn < ui->inputlistWidget->count())
        {
            //删除listview的item
            deleteListWidgetItem(item->text(cloumn));
        }
        //父项根据所有子项的勾选状态设置勾选状态
        auto parentItem = item->QTreeWidgetItem::parent();
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
        auto parentItem = item->QTreeWidgetItem::parent();
        if(parentItem)
        { //设置父项相同勾选状态
            parentItem->setCheckState(0, Qt::PartiallyChecked);
        }
    }
}


void MainWindow::connectWidget()
{
    //新语法
    QObject::connect(ui->inputtreeWidget, &QTreeWidget::itemChanged, this, &MainWindow::onItemChanged_In);
    //旧语法
    //connect(ui->inputtreeWidget, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(onItemChanged_In(QTreeWidgetItem *, int )));

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

void MainWindow::loadxml()
{
    input_Model = new QStandardItemModel(this);

    //QString fullpath = "C:\\Users\\lxl\\Desktop\\1394.xml";
    QString fullpath = "1394.xml";
    QFile file(fullpath);
    if(!file.open(QFile::ReadOnly))
    {
        //return QDomDocument();
        qDebug()<<"open error ";
        return;
    }

    QDomDocument doc;
    QString errormessage;
    if(!doc.setContent(&file,NULL,&errormessage))
    {
        file.close();
        qDebug()<<"set error ";
        return;
    }

    QStringList in_head;
    in_head << tr("数据输入:");

    //根节点:DataBase
    QDomNode root = doc.documentElement();
    QDomNode nodeICD = root.firstChild();

    ui->inputtreeWidget->setHeaderLabels(in_head);
    while(!nodeICD.isNull())
    {
        //遍历输入和输出
        if(nodeICD.isElement())
        {
            QDomElement elemICD = nodeICD.toElement();
            if(elemICD.attribute("type") == "input")
            {
                //遍历输入的各个子系统
                QDomNodeList listSYS= elemICD.childNodes();
                for(int i = 0; i < listSYS.size();i++)
                {
                    auto itemSYS = new TreeWidgetItemEx;
                    QDomNode nodeSYS = listSYS.at(i);
                    QDomElement elemSYS = nodeSYS.toElement();
                    //每个子系统创建一个tree
                    //qDebug()<<elemSYS.attribute("sysname");

                    itemSYS->setText(0, elemSYS.attribute("sysname"));
                    itemSYS->setCheckState(0, Qt::Unchecked);

                    if(nodeSYS.isElement())
                    {
                        //遍历输入的当前子系统的各个信号
                        QDomNodeList listfield= nodeSYS.childNodes();
                        for(int j = 0;j < listfield.size();j++)
                        {
                            QDomNode nodefield = listfield.at(j);
                            QDomElement elemfield = nodefield.toElement();
                            //获取名称
                            QString FieldName = elemfield.attribute("stFieldName");
                            //获取位域范围
                            QString uiBitBegin = elemfield.attribute("uiBitBegin");
                            QString uiBitEnd   = elemfield.attribute("uiBitEnd");
                            //获取类型
                            QString dataType =  elemfield.attribute("dataType");
                            //获取字
                            QString stByteOffset = elemfield.attribute("stByteOffset");
                            //获取意义
                            QDomNodeList listValue = nodefield.childNodes();
                            for(int j =0;j<listValue.size();j++)
                            {
                                QDomNode nodeValue = listValue.at(j);
                                QDomElement elemValue = nodeValue.toElement();
                                QString meaning = elemValue.attribute("strMean");
                                QString value = elemValue.attribute("strValue");
                            }
                            auto ch = new TreeWidgetItemEx();
                            ch->setText(0,QString::number(j+1) + "." + FieldName);
                            ch->setBitend(uiBitEnd.toInt());
                            ch->setBitbegin(uiBitBegin.toInt());
                            ch->setOffset(stByteOffset.toInt());
                            ch->setDatatype(dataType);
                            ch->setCheckState(0,Qt::Unchecked);//默认没有check box
                            itemSYS->addChild(ch);
                        }
                    }
                    //设置tree
                    ui->inputtreeWidget->addTopLevelItem(itemSYS);
                    ui->inputtreeWidget->expandAll();
                }
            }
            else if(elemICD.attribute("type") == "output")
            {
                //qDebug()<<"find output";
            }
            else
            {

            }
            //下一个
            nodeICD = nodeICD.nextSibling();
        }
    }
    //累加bits
}

void MainWindow::initTreeWiget()
{

    //output_Model = new QStandardItemModel(this);

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
    int *p = CDataControl::getIntputdata();
    qDebug()<<"输入"<<*p;
//    if(bUseCounting)
//    {
//        countTimer->start();
//        //begin = QTime::currentTime();//获取当前时间
//    }
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
    if(countTimer->isActive())
    {
        countTimer->stop();
    }
    ui->lcdNumber_counting->display(0);
}

