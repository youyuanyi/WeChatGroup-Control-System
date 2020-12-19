#ifndef SEARCH_USER_WIN_H
#define SEARCH_USER_WIN_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<fstream>
#include<sstream>
#include<QTextEdit>
#include<QLineEdit>
#include<QPainter>
#include<QPen>
#include<QPixmap>
#include<QPaintEvent>
#include"data.h"
#include"hash.h"
#include"group.h"
#include<QMessageBox>
#define MAXN 1500
class Search_User_Win : public QWidget
{
    Q_OBJECT
public:
    explicit Search_User_Win(QWidget *parent = nullptr);
    void Get_idx();
    void Creat_Hash();
    void Hash_Search();
    void paintEvent(QPaintEvent *event);

signals:
    void UserToFront();
public slots:
    void SendSlot();
private:
    QPushButton *out_btn;
    QLabel *title;//主标题
    QLabel *front_title;//前端服务标题
    QLabel *fun_title;//功能标签
    QLineEdit *user_edit;//输入用户
    QLineEdit *group_edit;//输入群
    QPushButton *search;
    WeChatGroup *GroupList;//群列表
    int ListLen;
    int user_idx;//用户下标
    LinkList Hash[1500];//先把用户链表数组开大点
    //群覆盖
    int p[MAXN];//存放每个用户的群主
    int p_size[MAXN];//存放覆盖后每个群的人数

    //利用map把用户的下标和名称一一映射
    map<string, int>  userTonum;//以名称为key，下标为value
    string numTouser[MAXN];//通过下标找到用户
    int map_idx;
};

#endif // SEARCH_USER_WIN_H
