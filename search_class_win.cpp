#include "search_class_win.h"

Search_Class_Win::Search_Class_Win(QWidget *parent) : QWidget(parent)
{
    this->resize(1400,1100);
    this->setWindowTitle("按类型查询");
    GroupList=new WeChatGroup[500];
    out_btn=new QPushButton(this);
    out_btn->setText("回退");
    out_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    out_btn->setGeometry(50,150,150,30);
    out_btn->show();
    connect(out_btn,&QPushButton::clicked,this,&Search_Class_Win::SendSlot);

    class_btn=new QPushButton(this);
    class_btn->setText("分类");
    class_btn->setGeometry(50,210,150,30);
    class_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    class_btn->show();
    connect(class_btn,&QPushButton::clicked,this,&Search_Class_Win::Search_Class);

    key_word=new QLineEdit(this);
    key_word->setText("在此输入关键字");
    key_word->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
    key_word->setGeometry(50,270,150,30);
    key_word->show();

    title=new QLabel(this);
    title->setText("  微信群管理系统");
    title->setGeometry(this->width()/2-100,30,350,30);
    title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    title->show();

    front_title=new QLabel(this);
    front_title->setText("   前端服务系统");
    front_title->setGeometry(this->width()/2-100,70,350,30);
    front_title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    front_title->show();

    fun_title=new QLabel(this);
    fun_title->setText("   按类别查询");
    fun_title->setGeometry(this->width()/2-100,110,350,30);
    fun_title->setStyleSheet("QLabel{font-size:28px;color:white;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
    fun_title->show();

    edit=new QTextEdit(this);
    edit->setGeometry(230,150,800,600);
    edit->show();
}
void Search_Class_Win::ReadFile()
{
    ifstream fin;
        fin.open("../weChatData.txt");
        if (!fin.is_open())
            printf("文件打开失败");
        else
        {
            ListLen = 0;
            int i = 0;
            for (i = 0; !fin.eof(); i++)
            {
                string s;
                getline(fin, s);//读一行
                stringstream ss(s);//把字符串转换为流
                string temp;
                ss >> temp;
                GroupList[i].Group_Name = temp;
                ss >> temp;
                int num = atoi(temp.c_str());
                GroupList[i].Person_Num = num;
                for (int j = 0; j<num; j++)
                {
                    ss >> temp;
                    GroupList[i].Person.push_back(temp);//存用户
                }
                ss >> temp;
                GroupList[i].times += temp;
                GroupList[i].year = atoi(temp.c_str());//存年

                ss >> temp;
                GroupList[i].times += ' ' + temp;
                GroupList[i].month = atoi(temp.c_str());//存月

                ss >> temp;
                GroupList[i].times += ' ' + temp;
                GroupList[i].date = atoi(temp.c_str());//读日

            }
            fin.close();
            ListLen = i;
        }
}
int Search_Class_Win::KMP(string S, string T)
{
    //S是主串，T是模式串
        int *next = new int[T.length() + 1];
        //把主串和模式串存入下标从1开始的数组，方便KMP
        char SS[30];
        for (int i = 1; i<=S.length(); i++)
            SS[i] = S[i - 1];
        char TT[30];
        for (int i = 1; i<=T.length(); i++)
            TT[i] = T[i - 1];
        //求next数组的一些初始化
        int i = 1;
        next[1] = 0;
        int j = 0;
        //求TT的next数组
        while (i<T.length()) {
            if (j == 0 || TT[i] == TT[j])
            {
                ++i; ++j; next[i] = j;
            }
            else
                j = next[j];
        }
        //进行KMP匹配
        i = 1, j = 1;
        while (i<=S.length() && j<=T.length())
        {
            if (j == 0 || SS[i]==TT[j]) { i++; j++; }
            else j = next[j];
        }
        delete[]next;
        if (j >=T.length())return 1; //匹配成功
        else return -1;
}
void Search_Class_Win::Classify()
{
    //拿模式串和主串进行比较，找到匹配起点，得到类别，然后输出所有属于该类别的微信群的名称以及群人数和创建时间
        string t[] = { "养生","健康","长寿","养老","工作","项目组","工作室","部门" ,"公司","单位","娱乐","电影","音乐","八卦","购物","拼单","团购","凑团","同学","小学","中学","大学","宿舍","家","爸","妈","学习","英语","数学","专业课" };
        for (int i = 0; i < ListLen; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (KMP(GroupList[i].Group_Name, t[j]) == 1)
                {
                    if (j < 4)
                    {
                        GroupList[i].type = "养生";
                    }
                    else if (j >= 4 && j < 10)
                        GroupList[i].type = "工作";
                    else if (j >= 10 && j < 14)
                        GroupList[i].type = "娱乐";
                    else if (j >= 14 && j < 18)
                        GroupList[i].type = "购物";
                    else if (j >= 18 && j < 23)
                        GroupList[i].type = "同学";
                    else if (j >= 23 && j < 26)
                        GroupList[i].type = "家人";
                    else if (j >= 26 && j < 30)
                        GroupList[i].type = "学习";
                }
            }
        }





        for (int i = 0; i < ListLen; i++)
        {
            if (GroupList[i].Group_Name == "八卦那些事")
                GroupList[i].type = "娱乐";
        }





}
void Search_Class_Win::Search_Class()
{
        edit->clear();
        flag=0;
        ReadFile();
        Classify();
        string key;
        QString type;
        key=key_word->text().toStdString();//获取文本框内容设置为string类型
        if (key == "养生" || key == "健康" || key == "长寿" || key == "养老")
             {type = "养生"; flag=1;}
        else if (key == "工作" || key == "项目组" || key == "工作室" || key == "部门" || key == "公司" || key == "单位")
             {type = "工作";flag=1;}
        else if (key == "娱乐" || key == "电影" || key == "音乐" || key == "八卦")
             {type = "娱乐";flag=1;}
        else if (key == "购物" || key == "拼单" || key == "团购" || key == "凑团")
             {type = "购物";flag=1;}
        else if (key == "同学" || key == "小学" || key == "中学" || key == "大学"||key=="宿舍")
             {type = "同学";flag=1;}
        else if (key =="家" || key == "爸" || key == "妈")
             {type = "家人";flag=1;}
        else if (key == "学习" || key == "英语" || key == "数学" || key == "专业课")
             {type = "学习";flag=1;}
        if(flag==1)//输入正确的关键词或类关键词
        {
        for (int i = 0; i < ListLen; i++)
        {//把key和每个群进行比较
            if (QString::fromStdString(GroupList[i].type)==type)
            {

               QString s;
               s=QString::fromStdString(GroupList[i].Group_Name)+' ';
               s=s+QString::fromStdString(to_string(GroupList[i].Person_Num))+' ';
               s=s+QString::fromStdString(to_string(GroupList[i].year))+' ';
               s=s+QString::fromStdString(to_string(GroupList[i].month))+' ';
               s=s+QString::fromStdString(to_string(GroupList[i].date));
               edit->append(s);

           }
        }
        }
        else
            QMessageBox::information(this,"无该群","请输入有效的关键词信息!");


}
void Search_Class_Win::SendSlot()
{
    emit ClassToFront();
}
void Search_Class_Win::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":image/dis.jpg"));
}
