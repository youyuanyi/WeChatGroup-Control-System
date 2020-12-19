#ifndef WIDGET_H
#define WIDGET_H
#define MAX 100
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QTextEdit>
#include"frontserve.h"
#include"login.h"
#include <Qvector>
#include <QFile>
#include <QDebug>
#include<QPainter>
#include<QPixmap>
#include<QPen>
#include<QPaintEvent>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include"data.h"
#include"manage.h"
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void ChangetoFront();//切换到前端界面
    void ChangetoLogin();//切换到登录界面
    void FrontToWin();//从前端界面跳回到主窗口
    void LoginToWin();//从登录界面跳回到主窗口
    void ReadFile();//读文件内容到结构体中
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QPushButton *front; //进入前台服务的按钮
    QPushButton *back;//进入后台管理的按钮
    QPushButton *out;//退出系统的按钮
    QLabel *title;//标题标签
    QLabel *mainwin;//主界面文字标签
    FrontServe front_Win;//前端界面
    login login_win;//登录界面子对象
    WeChatGroup *GroupList;//群列表
    int ListLen;
};



#endif // WIDGET_H
