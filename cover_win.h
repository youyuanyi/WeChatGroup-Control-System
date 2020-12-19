#ifndef COVER_WIN_H
#define COVER_WIN_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QTextEdit>
#include<QLineEdit>
#include<QFile>
#include<fstream>
#include<sstream>
#include<QPainter>
#include<QPen>
#include<QPixmap>
#include<QPaintEvent>
#include<string>
#include"data.h"
#include<map>
#include<vector>
#include<string>
#define MAXN 1500
class Cover_Win : public QWidget
{
    Q_OBJECT
public:
    explicit Cover_Win(QWidget *parent = nullptr);
    void Merge();
    void Cover();
    int find(int x);
    void paintEvent(QPaintEvent *event);
    void search();
    int GetNum(string s);

signals:
    void CoverToFront();
public slots:
    void SendSlot();
    void Show();
private:
    QPushButton *out_btn;
    QLabel *title;//主标题
    QLabel *front_title;//前端服务标题
    QLabel *fun_title;//功能标签
    QPushButton *cover_btn;//点击进行覆盖
    QTextEdit *edit;//显示标签
    WeChatGroup *GroupList;//群列表
    QLineEdit *search_btn;//搜索用户名
    QPushButton *btn;
    QLineEdit *ans;
};

#endif // COVER_WIN_H
