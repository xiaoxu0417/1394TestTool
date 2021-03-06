#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    inputword = 0;
    bUseCounting = false;
    m_period = 12.5;
    ConstantTarget = 0;    

    //创建计时器
    countTimer = new QTimer(this);
    countTimer->setInterval(1000);

    //创建周期执行dll线程
    mProThread = new ProcessThread();

    //载入输入输出treewidget
    loadxml();

    //设置UI状态
    initUI();

    //绑定槽函数
    connectWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
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

//删除指定的item
void MainWindow::deleteListWidgetItem(QString text, bool io)
{
#if 1
    int row=0;
    QString line;
    if(io)
    {
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
                break;
            }

            row++;
        }
    }
    else
    {
        while(row<(ui->outputlistWidget->count()))
        {
            QListWidgetItem* pItem = ui->outputlistWidget->item(row);
            line = pItem->text();
            //qDebug()<<line;
            //qDebug()<<ui->inputlistWidget->item(row);
            if(text==line)
            {
                //qDebug()<<"删除成功:"<<text;
                ui->outputlistWidget->takeItem(row);
                break;
            }

            row++;
        }
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

    TreeWidgetItemEx *pItem = dynamic_cast<TreeWidgetItemEx*>(item);
    if(item->checkState(0) == Qt::Checked)
    {
        if(pItem->getB_io())
        {
            inputTag.append(pItem->getNo());
        }
        else
        {
            outputTag.append(pItem->getNo());
        }
        if(item->childCount() == 0)//只添加子节点
        {
            QString txt = item->text(cloumn);

            //QWidget *widget = new QWidget(ui->inputlistWidget);
            QWidget *widget = new QWidget();
            QLabel *Label = new QLabel(widget);
            QLabel *LabelMeaning = new QLabel(widget);
            LabelMeaning->setText(pItem->getInitMeaning());
            LabelMeaning->setFixedWidth(60);
            LabelMeaning->setToolTip(pItem->getInitMeaning());//鼠标悬停信息
            //LabelMeaning->setStyleSheet("QLabel{background:#F50000;}");

            Label->setFrameShape(QFrame::Box);


            QLineEdit *LineEdit = new QLineEdit(ui->inputlistWidget);
            LineEdit->setText("0");

            bool isnew = false;
            //绑定每个lineEdit的槽函数
            //CDataControl *Ctl = new CDataControl(pItem->getBitbegin(),pItem->getBitend(),pItem->getOffset(),pItem->getDatatype(),pItem->getB_io(),inputword,pItem->getMeaningMap());
            CDataControl *Ctl = findCtrl(pItem->getBitbegin(),pItem->getBitend(),pItem->getOffset(),pItem->getDatatype(),pItem->getB_io(),inputword,pItem->getMeaningMap(),&isnew);

            if(isnew)
            {
                connect(Ctl,SIGNAL(updateMeaning(QString)),LabelMeaning,SLOT(setText(QString)));
                connect(Ctl,SIGNAL(updateMeaningstyle(QString)),LabelMeaning,SLOT(setStyleSheet(QString)));
                connect(Ctl,SIGNAL(updateDllInPutdata()),mProThread,SLOT(getNewInputDataFromUI()));
                //输入
                if(pItem->getB_io())
                {
                    connect(LineEdit,SIGNAL(textChanged(QString)),Ctl,SLOT(slot_onInputDataChange(QString)));
                    connect(LineEdit,SIGNAL(editingFinished()),Ctl,SLOT(slot_onInputDataFinished()));
                    connect(this,SIGNAL(ClearAllData()),Ctl,SLOT(slot_clearalldata()));
                    connect(this,SIGNAL(ClearAllData(QString)),LineEdit,SLOT(setText(QString)));//清除

                    connect(Ctl,SIGNAL(updateLineEdit(QString)),LineEdit,SLOT(setText(QString)));
                    connect(this,SIGNAL(LoadData(QVariant)),Ctl,SLOT(slot_onLoadInputData(QVariant)));//从ini load 数据时更新每个data ctrl
                }
                else//输出数据,不可编辑
                {
                    connect(Ctl,SIGNAL(testsetOutPutdata(QString)),LineEdit,SLOT(setText(QString)));//显示输出数据
                    connect(mProThread,SIGNAL(running(QVariant)),Ctl,SLOT(slot_updateOutputData(QVariant)));//每拍发出running信号,去更新输出数据的值
                    LineEdit->setEnabled(false);
                }
            }
            else
            {
                Ctl->updateInputUIFormIni();
            }

            //创建水平布局
            QHBoxLayout *horLayout = new QHBoxLayout;
            horLayout->setContentsMargins(0, 0, 0, 0);
            horLayout->setMargin(2);
            horLayout->setSpacing(2);

            horLayout->addWidget(Label,5);
            //horLayout->addStretch(1);
            horLayout->addWidget(LineEdit,1);
            horLayout->addWidget(LabelMeaning,1);

            widget->setLayout(horLayout);

            //将widget作为列表的item
            QListWidgetItem *ITEM = new QListWidgetItem();
            ITEM->setText(txt);

            QSize size = ITEM->sizeHint();
            ITEM->setSizeHint(QSize(size.width(), 40));
            widget->setSizeIncrement(size.width(), 40);

            if(pItem->getB_io())
            {
                ui->inputlistWidget->addItem(ITEM);
                ui->inputlistWidget->setItemWidget(ITEM, widget);//添加项目,每个item应该自己是一个类
            }
            else
            {
                ui->outputlistWidget->addItem(ITEM);
                ui->outputlistWidget->setItemWidget(ITEM, widget);//添加项目,每个item应该自己是一个类
            }

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
        if(pItem->getB_io())
        {
            inputTag.removeAll(pItem->getNo());
        }
        else
        {
            outputTag.removeAll(pItem->getNo());
        }
        auto childCount = item->childCount();
        //设置子项相同勾选状态
        for(int i = 0; i < childCount; ++i)
        {
            item->child(i)->setCheckState(0, Qt::Unchecked);
        }

        //if(cloumn < ui->inputlistWidget->count())
        {
            //删除listview的item
            deleteListWidgetItem(item->text(cloumn),pItem->getB_io());
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
    connect(countTimer,&QTimer::timeout,this,&MainWindow::doTimerService);
    //新语法
    QObject::connect(ui->inputtreeWidget, &QTreeWidget::itemChanged, this, &MainWindow::onItemChanged_In);
    //旧语法
    //connect(ui->inputtreeWidget, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(onItemChanged_In(QTreeWidgetItem *, int )));

    connect(ui->outputtreeWidget, &QTreeWidget::itemChanged, this, &MainWindow::onItemChanged_In);

    connect(this,SIGNAL(newInputdata2Proce()),mProThread,SLOT(getNewInputDataFromUI()));
    connect(mProThread,SIGNAL(updateCount(QString,bool)),this,SLOT(on_updatelabelcount(QString,bool)));

    connect(this,SIGNAL(LoadData(QVariant)),mProThread,SLOT(getNewInputDataFromIni(QVariant)));

}

//
void MainWindow::doTimerService()
{
    //QTime相减
#if 0
    end = QTime::currentTime();//获取当前时间
    int m_iTestTime = begin.msecsTo(end)/1000;
#else
    unsigned int count = mProThread->getTimeCount();
    int m_iTestTime = (count * period())/1000;
#endif
    ulong ulHour = m_iTestTime / 3600;
    ulong ulMinute = (m_iTestTime - ulHour * 3600) / 60;
    ulong ulSecond = (m_iTestTime - ulHour * 3600 - ulMinute * 60);

    QString strTime = QString("%1:%2:%3").arg(ulHour,2, 10, QChar('0')).arg(ulMinute,2, 10, QChar('0') ).arg(ulSecond,2, 10, QChar('0'));
    ui->lcdNumber_counting->display(strTime);
    //qDebug()<<count;

}

void MainWindow::loadxml()
{
    input_Model = new QStandardItemModel(this);
    unsigned int show_index_in = 0;
    unsigned int show_index_out = 0;

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
    in_head << tr("input data:");
    QStringList out_head;
    out_head << tr("output data:");

    //根节点:DataBase
    QDomNode root = doc.documentElement();
    QDomNode nodeICD = root.firstChild();

    ui->inputtreeWidget->setHeaderLabels(in_head);
    ui->outputtreeWidget->setHeaderLabels(out_head);

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
                    itemSYS->setNo(inputindex);
                    inputindex++;

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
                            //获取offset 字索引
                            QString stByteOffset = elemfield.attribute("stByteOffset");
                            //获取意义
                            QDomNodeList listValue = nodefield.childNodes();
                            //QMap <QString,QString>meanings;

                            auto ch = new TreeWidgetItemEx();
                            show_index_in++;

                            ch->setText(0,QString::number(show_index_in) + "." + FieldName);
                            ch->setBitend(uiBitEnd.toInt());
                            ch->setBitbegin(uiBitBegin.toInt());
                            ch->setOffset(stByteOffset.toInt());
                            ch->setDatatype(dataType);
                            ch->setCheckState(0,Qt::Unchecked);//默认没有check box
                            ch->setB_io(true);
                            ch->setNo(inputindex);

                            for(int j =0;j<listValue.size();j++)
                            {
                                QDomNode nodeValue = listValue.at(j);
                                QDomElement elemValue = nodeValue.toElement();
                                QString meaning = elemValue.attribute("strMean");
                                QString value = elemValue.attribute("strValue");
                                ch->setMeaning(value,meaning);
                            }

                            itemSYS->addChild(ch);
                            inputindex++;


                            if(stByteOffset.toInt() + 1 > inputword)
                            {
                                inputword = stByteOffset.toInt() + 1;
                                CDataControl::setDatalength(inputword);
                            }
                        }
                    }
                    //设置tree
                    ui->inputtreeWidget->addTopLevelItem(itemSYS);
                    ui->inputtreeWidget->expandAll();
                }
            }
            else if(elemICD.attribute("type") == "output")
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
                    itemSYS->setNo(outputindex);
                    outputindex++;

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

                            auto ch = new TreeWidgetItemEx();
                            outputindex++;
                            show_index_out++;
                            ch->setNo(outputindex);
                            ch->setText(0,QString::number(show_index_out) + "." + FieldName);
                            ch->setBitend(uiBitEnd.toInt());
                            ch->setBitbegin(uiBitBegin.toInt());
                            ch->setOffset(stByteOffset.toInt());
                            ch->setDatatype(dataType);
                            ch->setCheckState(0,Qt::Unchecked);//默认没有check box
                            ch->setB_io(false);
                            //获取意义
                            QDomNodeList listValue = nodefield.childNodes();
                            for(int j =0;j<listValue.size();j++)
                            {
                                QDomNode nodeValue = listValue.at(j);
                                QDomElement elemValue = nodeValue.toElement();
                                QString meaning = elemValue.attribute("strMean");
                                QString value = elemValue.attribute("strValue");
                                ch->setMeaning(value,meaning);
                            }
                            itemSYS->addChild(ch);
                        }
                    }
                    //设置tree
                    ui->outputtreeWidget->addTopLevelItem(itemSYS);
                    ui->outputtreeWidget->expandAll();
                }
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

void MainWindow::updateTreeView(bool in,QList<int> List)
{
    qDebug()<<"1"<<in;
    if (in)
    {
        qDebug()<<"2";
        QTreeWidgetItemIterator it(ui->inputtreeWidget);
        while (*it) {
            TreeWidgetItemEx *pItem = dynamic_cast<TreeWidgetItemEx*>(*it);
            if(List.contains(pItem->getNo()))
            {
                qDebug()<<"4"<<pItem->getNo();
                (*it)->setCheckState(0,Qt::Checked);
                qDebug() << (*it)->text(0);
            }

             ++it;
        }
    }
    else
    {
        QTreeWidgetItemIterator it(ui->outputtreeWidget);
        while (*it) {
            TreeWidgetItemEx *pItem = dynamic_cast<TreeWidgetItemEx*>(*it);
            if(List.contains(pItem->getNo()))
            {
                (*it)->setCheckState(0,Qt::Checked);
                qDebug() << (*it)->text(0);
            }

             ++it;
        }
    }

}

void MainWindow::initUI()
{
    ui->lcdNumber_counting->setFont(QFont("Times",12,QFont::Black));
    if(bUseCounting)
    {
        ui->checkBox->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox->setCheckState(Qt::Unchecked);
    }

    setCountView(true);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //true 勾选;false 非勾选
    bUseCounting = arg1 == 2?true:false;
    //qDebug() <<bUseCounting <<" "<< arg1;
    if(bUseCounting)
    {
        ui->pushButton_start_counting->setEnabled(false);
        ui->pushButton_stop_counting->setEnabled(true);
    }
    else
    {
        ui->pushButton_start_counting->setEnabled(true);
        ui->pushButton_stop_counting->setEnabled(true);
    }

    if(countTimer->isActive())
    {
        countTimer->stop();
    }
}

void MainWindow::on_pushButton_process_clicked()
{
    if(!mProThread->isRunning())
    {
        mProThread->start();
    }

    mProThread->setBRun(true);
    mProThread->setTimeCount(0);

    if(!mProThread->getBConstant())
    {
        mProThread->setConstantTarget(ConstantTarget);
        mProThread->setConstantCountStart(true);
    }
    else
    {
        mProThread->setConstantCountStart(false);
    }

    if(bUseCounting)//输入时计时
    {
        countTimer->start();
        mProThread->setTimeCount(0);
    }
    else
    {

    }

    //通知线程去更新数据
    emit newInputdata2Proce();
    ui->pushButton_process->setEnabled(false);
    ui->pushButton_stop_process->setEnabled(true);
    ui->checkBox_Constant->setEnabled(false);//开始运行后,不允许修改持续状态
}

//结束按钮
void MainWindow::on_pushButton_stop_process_clicked()
{
    if(bUseCounting)
    {
        if(countTimer->isActive())
        {
            countTimer->stop();

            //恢复开始计时按钮
            ui->pushButton_start_counting->setEnabled(true);
        }
    }
    mProThread->setBRun(false);
    if(!mProThread->getBConstant())
    {
        mProThread->setConstantCountStart(false);
    }
    ui->pushButton_process->setEnabled(true);
    ui->pushButton_stop_process->setEnabled(false);
    ui->checkBox_Constant->setEnabled(true);//结束运行后,恢复持续状态
}

void MainWindow::on_updatelabelcount(QString abc,bool b)
{
    ui->labelCount->setText(abc);
    if(b)//结束了
    {
        ui->pushButton_process->setEnabled(true);
        ui->pushButton_stop_process->setEnabled(true);
        ui->checkBox_Constant->setEnabled(true);//结束运行后,恢复持续状态
    }
}

void MainWindow::on_pushButton_start_counting_clicked()
{
    if(!bUseCounting)
    {
        countTimer->start();
        //begin = QTime::currentTime();//获取当前时间
        mProThread->setTimeCount(0);

        ui->pushButton_start_counting->setEnabled(false);
        ui->pushButton_stop_counting->setEnabled(true);
    }
    else
    {

    }

}

void MainWindow::on_pushButton_stop_counting_clicked()
{
    if(countTimer->isActive())
    {

        countTimer->stop();
        //end = QTime::currentTime();//获取当前时间

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

//清除所有输出数据
void MainWindow::on_pushButtonClearData_clicked()
{
    //有可能还没开始构造cDataManger
    //QMessageBox message(QMessageBox::NoIcon,  "attention",  "Do you want to clear all input data?", QMessageBox::Yes | QMessageBox::No, NULL);
    QMessageBox message(QMessageBox::NoIcon,  "注意",  "清零所有输入数据?", QMessageBox::Yes | QMessageBox::No, NULL);
    if(message.exec() == QMessageBox::Yes)
    {
        //QMessageBox::aboutQt(NULL,  "About Qt");
        //qDebug()<<"ok";
        emit ClearAllData();
        emit ClearAllData("0");
    }
    else
    {
        //qDebug()<<"no ok";
    }
}

void MainWindow::on_SaveTarg_clicked()
{
#if 0
    QTreeWidgetItemIterator it(ui->inputtreeWidget);
    while (*it) {
         //do something like
         qDebug() << (*it)->text(0);

        TreeWidgetItemEx *pItem = dynamic_cast<TreeWidgetItemEx*>(*it);
        if(inputTag.contains(pItem->getNo()))
        {
            (*it)->setCheckState(0,Qt::Checked);
        }

         ++it;
    }
#else
    qRegisterMetaTypeStreamOperators<QList<int> >("QList<int>");
    qRegisterMetaTypeStreamOperators<Input_vmc>("Input_vmc");

    //保存当前选项
    QString filter ="(*.ini)";
    QString aFileName = QFileDialog::getSaveFileName(this, tr("保存配置"), "./ini/in/", tr("(*.ini)"),&filter/*,QFileDialog::DontUseNativeDialog*/);//若不存在文件，则创建

    qDebug()<<"save list"<<aFileName<<inputTag;
    QSettings settings(aFileName, QSettings:: IniFormat);
    //保存输入数据的tag list
    settings.setValue("data", QVariant::fromValue(inputTag));
    //保存输入数据的真实值

    unsigned int *p = (unsigned int *)CDataControl::getIntputdata();
    for(int i =0;i <sizeof(Input_vmc)/sizeof (unsigned int);i++)
    {
        QString temp = "value" + QString::number(i);
        settings.setValue(temp, QVariant::fromValue(*p));
        p++;
    }

#endif
}

//load输入数据targ
void MainWindow::on_LoadTarg_clicked()
{
#if 0
    QDir directory;
    directory.setPath("/ini");  //设置文件路径

    QStringList filter;
    filter<<"*.ini";   //设置文件夹过滤，只取.ini文件

    QStringList allFiles=  directory.entryList(filter);   //列出所过满足过滤规则的文件名
#else
    QString  aFileName=     QFileDialog::getOpenFileName(nullptr,tr("打开配置"),"./ini/in/","ini files (*.ini)",nullptr,QFileDialog::DontUseNativeDialog);
    QSettings settings(aFileName, QSettings:: IniFormat);
    QList<int> TargList = settings.value("data").value<QList<int> >();

    unsigned int *ret = (unsigned int *)malloc(sizeof(Input_vmc));
    unsigned int *ret_index = ret;
    memset(ret,0x0,sizeof(Input_vmc));

    //取数据
    for(int i =0;i <sizeof(Input_vmc)/sizeof (unsigned int);i++)
    {
        QString temp = "value" + QString::number(i);
        unsigned int value = settings.value(temp).value<unsigned int>();
        memcpy(ret_index,&value,sizeof (value));
        //qDebug()<<value;
        ret_index++;
    }
    Input_vmc *inret = (Input_vmc *)ret;
    //将load的数据发给data ctrl,以及线程process
    QVariant data;
    data.setValue(*inret);
    emit LoadData(data);

    qDebug()<<"open list"<<TargList;
    if(!TargList.empty())
    {
        updateTreeView(true,TargList);
    }
#endif
}

void MainWindow::on_out_save_clicked()
{
    qRegisterMetaTypeStreamOperators<QList<int> >("QList<int>");

    //保存当前选项
    QString filter ="(*.ini)";
    QString aFileName = QFileDialog::getSaveFileName(this, tr("保存配置"), "./ini/out/", tr("(*.ini)"),&filter/*,QFileDialog::DontUseNativeDialog*/);//若不存在文件，则创建

    qDebug()<<"保存文件"<<aFileName<<outputTag;
    QSettings settings(aFileName, QSettings:: IniFormat);
    settings.setValue("data", QVariant::fromValue(outputTag));
}

void MainWindow::on_out_load_clicked()
{
    QString  aFileName=     QFileDialog::getOpenFileName(nullptr,tr("打开配置"),"./ini/out/","ini files (*.ini)",nullptr,QFileDialog::DontUseNativeDialog);
    QSettings settings(aFileName, QSettings:: IniFormat);
    QList<int> TargList = settings.value("data").value<QList<int> >();
    qDebug()<<"打开list"<<TargList;
    if(!TargList.empty())
    {
        updateTreeView(false,TargList);
    }
}

void MainWindow::on_radioButton_clicked()
{
    qDebug()<<"10ms";
    setPeriod(10.0);
}

void MainWindow::on_radioButton_12P5_clicked()
{
    qDebug()<<"12.5ms";
    setPeriod(12.5);
}

float MainWindow::period() const
{
    return m_period;
}

void MainWindow::setPeriod(float period)
{
    m_period = period;
}

void MainWindow::setCountView(bool vaild)
{
    if(vaild)
    {
        mProThread->setBConstant(true);

        ui->lineEditCount->setText("-");
        ui->lineEditCount->setEnabled(false);
//        ui->pushButtonCount->setEnabled(false);
//        ui->labelCount->setText("-");
//        ui->labelCount->setEnabled(false);
    }
    else
    {
        mProThread->setBConstant(false);

        ui->lineEditCount->setText("0");
        ui->lineEditCount->setEnabled(true);
//        ui->pushButtonCount->setEnabled(true);
//        ui->labelCount->setText("0");
//        ui->labelCount->setEnabled(true);
    }
}

CDataControl * MainWindow::findCtrl(int start, int end, int offset,int datatype,bool m_io, int length, QMap <int,QString> meaning,bool *isnew)
{
    for(int i=0; i<CtrlList.size(); ++i)
    {
        CDataControl * index = CtrlList.at(i);
        if(index->getBeginbit() == start && index->getEndbit() == end && index->getOffset() == offset)
        {
            *isnew = false;
            return index;
        }
    }
    //没找到,则创建一个
    CDataControl *Ctl = new CDataControl(start,end,offset,datatype,m_io,length,meaning);

    CtrlList.append(Ctl);
    *isnew = true;
    return Ctl;
}

void MainWindow::on_checkBox_Constant_stateChanged(int arg1)
{
    //如果此时程序在跑,需要先停止
    if(mProThread->getBRun())
    {
        //qDebug()<<ui->checkBox->isChecked();
        QMessageBox message(QMessageBox::NoIcon,  "","please stop frist!");
        //message.exec();
    }
    else
    {
        //true
        if(arg1 == 2)
        {
            setCountView(true);
        }
        else
        {
            setCountView(false);
        }
    }
}

void MainWindow::on_lineEditCount_textChanged(const QString &arg1)
{
    ConstantTarget = arg1.toUInt();
}

void MainWindow::on_pushButtonCount_clicked()
{
    mProThread->setConstantTarget(ConstantTarget);
    qDebug()<<"start"<<ConstantTarget;
}


