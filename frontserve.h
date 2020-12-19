#ifndef FRONTSERVE_H
#define FRONTSERVE_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QTextLine>
#include<QLineEdit>
#include<QPainter>
#include<QPixmap>
#include<QPen>
#include<QPaintEvent>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<QDebug>
#include<minmax.h>
#include "search_class_win.h"
#include "search_user_win.h"
#include"search_dis_win.h"
#include "sortwin.h"
#include "cover_win.h"
#include"data.h"
class FrontServe : public QWidget
{
    Q_OBJECT
public:
    explicit FrontServe(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:
    void MySignal();

public slots:
    void SendSlot();//发送从前端跳转到主界面的信号
    void FrontToSort();//前端界面跳转到排序界面
    void FrontToClass();//前端界面跳转到按类别查询界面
    void FrontToUser();//从前端界面跳转到查询用户界面
    void FrontToDis();//从前端界面跳转到求距离界面
    void FrontToCover();//从前端界面跳转到求群覆盖界面
    void Deal_Class();//处理按类型查询界面发送的信号
    void Deal_Sort();//处理排序界面发送的信号
    void Deal_User();//处理用户查询界面发送的信号
    void Deal_Dis();//处理从距离界面发送的信号
    void Deal_Cover();//处理从群覆盖界面发送的信号
private:
    QPushButton *sort; //按微信群排序按钮
    QPushButton *search_class;//按类别查询按钮
    QPushButton *search_user;//查询群中是否有某用户按钮
    QPushButton *search_dis;//查询两用户间最短距离的按钮
    QPushButton *cover;//群覆盖的按钮
    QPushButton *out;//返回上级按钮
    QLabel *title;//主标题
    QLabel *front_title;//前端服务标题
    //把5个子窗口都作为前端窗口的对象
    SortWin Sort_Sub;
    Search_Class_Win Class_Sub;
    Search_User_Win User_Sub;
    Search_Dis_Win Dis_Sub;
    Cover_Win Cover_Sub;

};

#endif // FRONTSERVE_H
