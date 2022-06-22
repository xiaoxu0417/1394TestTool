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
#include "def.h"
#include <windows.h>
#include "processthread.h"
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QFileDialog>

//#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectWidget();

    void delteInputListView(QString text);

    //删除
    void deleteListWidgetItem(QString text, bool io);
    //void deleteListWidgetItem(int row);

    void doTimerService();

    void loadxml();

    void updateTreeView(bool in,QList<int> List);

    void initUI();

    float period() const;
    void setPeriod(float period);

    void setCountView(bool vaild);

signals:
    void ClearAllData();
    void ClearAllData(QString);
    void newInputdata2Proce();
    //void running();

private slots:
    void onItemChanged_In(QTreeWidgetItem *item, int cloumn);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_process_clicked();

    void on_pushButton_start_counting_clicked();

    void on_pushButton_stop_counting_clicked();

    void on_pushButton_clear_counting_clicked();

    void on_pushButtonClearData_clicked();

    void on_SaveTarg_clicked();

    void on_LoadTarg_clicked();

    void on_out_save_clicked();

    void on_out_load_clicked();

    void on_radioButton_clicked();

    void on_radioButton_12P5_clicked();

    void on_checkBox_Constant_stateChanged(int arg1);

    void on_lineEditCount_textChanged(const QString &arg1);

    void on_pushButtonCount_clicked();

    void on_pushButton_stop_process_clicked();

    void on_updatelabelcount(QString,bool);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *input_Model;//输入
    QStandardItemModel *output_Model;//输出
    bool bUseCounting;
    QTimer *countTimer;//计时器
    //QTime begin;
    //QTime end;
    int inputword;

    ProcessThread *mProThread;

    unsigned int inputindex = 0;
    unsigned int outputindex = 0;

    QList <int>inputTag;
    QList <int>outputTag;

    float m_period;
    unsigned int ConstantTarget;
};
#endif // MAINWINDOW_H
