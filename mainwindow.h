#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QStringList>
#include <QDebug>
#include <QStandardItemModel>
#include <qtimer.h>
#include <QTime>
#include "QLabel"
#include "QLineEdit"
#include "QHBoxLayout"
#include <QtXml/QDomDocument>
#include "QFile"
#include "TreeWidgetItemEx.h"
#include "cdatacontrol.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initTreeWiget();
    void connectWidget();

    void delteInputListView(QString text);
    void delteOutputListView(QString text);
    //删除指定的item
    void deleteListWidgetItem(QString text);
    //void deleteListWidgetItem(int row);

    void doTimerService();

    void loadxml();

private slots:
    void onItemChanged_In(QTreeWidgetItem *item, int cloumn);
    void onItemChanged_Out(QTreeWidgetItem *item, int cloumn);


    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_process_clicked();

    void on_pushButton_start_counting_clicked();

    void on_pushButton_stop_counting_clicked();

    void on_pushButton_clear_counting_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *input_Model;//输入listview的model
    QStandardItemModel *output_Model;//输出listview的model
    bool bUseCounting;
    QTimer *countTimer;// 定义定时器对象
    QTime begin;
    QTime end;
    //QList <CDataControl*> listCtl;
    //QList <QLineEdit> EditCtl;
};
#endif // MAINWINDOW_H
