#ifndef SEARCH_DIS_WIN_H
#define SEARCH_DIS_WIN_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QTextLine>
#include<QTextEdit>
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
#include<QPainter>
#include<QPen>
#include<QPixmap>
#include<QPaintEvent>
#include<minmax.h>
#include"data.h"
#include"manage.h"
#define MAXINT 32767.0
class Search_Dis_Win : public QWidget
{
    Q_OBJECT
public:
    explicit Search_Dis_Win(QWidget *parent = nullptr);
    void Get_Dis();//求得最短距离
    int Get_Num(string);
    void paintEvent(QPaintEvent *event);

signals:
    void DisToFront();

public slots:
    void SendSlotS();

private:
    Manage *M;//要动态分配，不然会爆
    //WeChatGroup *GroupList;
    int ListLen;
    QPushButton *out_btn;//回退按钮
    QPushButton *search;//搜索
    QLabel *title;//主标题
    QLabel *front_title;//前端服务标题
    QLabel *fun_title;//功能标签
    QLineEdit *user_st;
    QLineEdit *user_ed;
    QTextEdit *edit;
};

#endif // SEARCH_DIS_WIN_H
