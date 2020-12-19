        #include "search_dis_win.h"

    Search_Dis_Win::Search_Dis_Win(QWidget *parent) : QWidget(parent)
    {
        this->resize(1400,1100);
        this->setWindowTitle("查询最短路");

        search=new QPushButton(this);
        search->setText("搜索");
        search->setGeometry(30,450,180,50);
        search->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
        search->show();
        connect(search,&QPushButton::clicked,this,&Search_Dis_Win::Get_Dis);

        out_btn=new QPushButton(this);
        out_btn->setText("回退");
        out_btn->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
        out_btn->setGeometry(30,150,180,50);
        out_btn->show();
        connect(out_btn,&QPushButton::clicked,this,&Search_Dis_Win::SendSlotS);

        user_st=new QLineEdit(this);
        user_st->setGeometry(30,250,180,50);
        user_st->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
        user_st->show();

        user_ed=new QLineEdit(this);
        user_ed->setGeometry(30,350,180,50);
        user_ed->setStyleSheet("QPushButton{background-color:#FFF5EE;}");
        user_ed->show();

        edit=new QTextEdit(this);
        edit->setGeometry(430,150,600,400);
        edit->show();

        title=new QLabel(this);
        title->setText("  微信群管理系统");
        title->setGeometry(this->width()/2-100,30,350,30);
        title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
        title->show();

        front_title=new QLabel(this);
        front_title->setText("   前端服务系统");
        front_title->setGeometry(this->width()/2-100,70,350,30);
        front_title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
        front_title->show();

        fun_title=new QLabel(this);
        fun_title->setText("查询两个用户最短距离");
        fun_title->setGeometry(this->width()/2-100,110,350,30);
        fun_title->setStyleSheet("QLabel{font-size:28px;color:black;border-radius:5px;font-weight:bold;font-family:Georgia, serif;}");
        fun_title->show();

        user_st->clear();
        user_ed->clear();
        edit->clear();
        M=new Manage;
        qDebug()<<"预加载中...";
        M->ReadFile();
        M->Get_idx();
        M->Creat_Hash();
        //因为建图算法和Floyd跑得慢，所以在打开窗口时就预加载，把建图和Floyd都先执行
        int i,j;//M->user_idx=971
        for ( i = 0; i < M->user_idx; i++)
            for ( j = 0; j < M->user_idx; j++)
                     M->G[i][j].val= MAXINT;//初始化为非连通图

        for (i = 0; i < M->user_idx; i++)
            {//从第1个用户开始，和后面所有的人比较有无在同一个群中，直到i=user_idx
                for (j = i + 1; j <M->user_idx; j++)
                {
                    LinkList p1 = M->Hash[i]->next;//遍历用户i的哈希表
                    vector<string> Main_Node;
                    vector<string> Main_Copy;
                    while (p1)
                    {
                        Main_Copy.push_back(p1->node_value);
                        Main_Node.push_back(p1->node_value);//先把i的所在的群都存入
                        p1 = p1->next;
                    }
                    LinkList p2 = M->Hash[j]->next;
                    vector<string> Sub_Node;
                    vector<string> Sub_Copy;
                    while (p2)//存j的所在群
                    {
                        Sub_Copy.push_back(p2->node_value);
                        Sub_Node.push_back(p2->node_value);
                        p2 = p2->next;
                    }
                    vector<string> Belong_Group;//i,j的共同群的群名
                    for(int t=0;t<Sub_Node.size();t++)
                        for (int k = 0; k < Main_Node.size(); k++)
                        {
                            if (Sub_Node[t] == Main_Node[k])//处于同一个群
                                Belong_Group.push_back(Sub_Node[t]);
                        }
                    if (Belong_Group.size() == 0)
                        continue;//j与i无共同群,找j+1与i比较
                    //from::把两个用户所处的相同群从群列表中删除
                     vector<string>::iterator it;
                    for (int t = 0; t < Belong_Group.size(); t++)
                    {
                        for (it = Sub_Node.begin(); it != Sub_Node.end();)
                        {
                            if (Belong_Group[t] == *it)
                                it = Sub_Node.erase(it);
                            else
                                it++;
                        }
                    }
                    for (int k = 0; k < Belong_Group.size(); k++)
                    {
                        for (it = Main_Node.begin(); it != Main_Node.end();)
                        {
                            if (Belong_Group[k] == *it)
                                it = Main_Node.erase(it);
                            else
                                it++;
                        }
                    }
                    //删除end
                    if (Main_Node.size() == 0 && Sub_Node.size() == 0)
                    {//如果删掉相同群后两个用户没有所处群了，说明他们在同一个群中，情况1
                        M->G[i][j].val = 1.0;
                        M->G[j][i].val = 1.0;
                    }
                    //情况2，i，j属于不同的群
//                    else if (Main_Node.size() == 0 && Sub_Node.size() != 0)
//                    {
//                        int maxn = 0;
//                        for (int t = 0; t< Sub_Node.size(); t++)
//                            maxn = max(maxn, Get_Num(Sub_Node[t]));//找群人数最多
//                        M->G[i][j].val = 100.0 / maxn;
//                        M->G[j][i].val = 100.0 / maxn;
//                    }
//                    else if (Main_Node.size() != 0 && Sub_Node.size() == 0)
//                    {
//                        int maxn = 0;
//                        for (int t = 0; t < Main_Node.size(); t++)
//                            maxn = max(maxn, Get_Num(Main_Node[t]));
//                        M->G[i][j].val = 100.0 / maxn;
//                        M->G[j][i].val = 100.0 / maxn;
//                    }
                     else if (Main_Node.size() == 1 && Sub_Node.size() == 1)
                    {
                            int p_num1=Get_Num(Main_Node[0]);
                            int p_num2=Get_Num(Sub_Node[0]);
                            M->G[i][j].val=M->G[j][i].val=100.0/(p_num1+p_num2);
                    }
                    else//i，j完全属于多个不同的群，情况3
                    {
                        int max1 = 0;
                        int max2 = 0;
                        for (int t = 0; t < Main_Copy.size(); t++)
                            max1 = max(max1, Get_Num(Main_Copy[t]));
                        for (int k = 0; k < Sub_Copy.size(); k++)
                            max2 = max(max2, Get_Num(Sub_Copy[k]));
                        M->G[i][j].val = 100.0 / (max1 + max2);
                        M->G[j][i].val = 100.0 / (max1 + max2);
                    }
                }
            }
             M->Floyd();//预加载

    }
    int  Search_Dis_Win::Get_Num(string T)
    {
        for(int i=0;i<M->ListLen;i++)
        {
            if(M->GroupList[i].Group_Name==T)
                return M->GroupList[i].Person_Num;

        }
    }
    void Search_Dis_Win::Get_Dis()
    {
        edit->clear();
        string user1,user2;
        user1=user_st->text().toStdString();
        user2=user_ed->text().toStdString();
        int start_idx =  M->userTonum[user1];
        int end_idx=  M->userTonum[user2];
        int idx =  M->Path[start_idx][end_idx];
        QString s;
        string ss[100];
        int cnts=0;
        LinkList tp1=M->Hash[start_idx]->next;
        int flag=0;
        while(tp1&&!flag)
        {
            LinkList tp2=M->Hash[M->Path[start_idx][end_idx]]->next;
            while(tp2&&!flag)
            {
                if(tp1->node_value==tp2->node_value)
                {
                    ss[cnts++]=tp1->node_value;
                    flag=1;//找到第一个的群
                }
                tp2=tp2->next;
            }
           tp1=tp1->next;
        }
        while(idx!=end_idx)
        {
           LinkList p1=M->Hash[idx]->next;
           while(p1)
           {
             int t=M->Path[idx][end_idx];//idx后面的一个人
             LinkList p2=M->Hash[t]->next;
             while(p2)
            {
               if(p1->node_value==p2->node_value)
               {
                    ss[cnts++]=p2->node_value;//记录群名
               }
               p2=p2->next;
           }
             p1=p1->next;
           }
           idx=M->Path[idx][end_idx];
        }
        idx =  M->Path[start_idx][end_idx];
        if(M->D[start_idx][end_idx]==MAXINT)
            s=s+"无法认识";
        else
        {
        s=s+"距离"+QString::fromStdString(to_string(  M->D[start_idx][end_idx]))+ " ";
        s=s+QString::fromStdString(user1);
        int i=0;
        qDebug()<<"cnts:"<<cnts;
        while (idx != end_idx)
         {
             s=s+"("+QString::fromStdString(ss[i++])+")";
              s=s+ "->" +QString::fromStdString(  M->numTouser[idx ]);

              idx  =  M->Path[idx][end_idx];
         }
          s=s+"("+QString::fromStdString(ss[cnts-1])+")";
        s=s+"->"+QString::fromStdString(user2);
        }
    //    for(int i=0;i<cnts;i++)
    //        s=s+QString::fromStdString(ss[i])+"、";
        edit->setText(s);
    }
    void Search_Dis_Win::SendSlotS()
    {
        emit DisToFront();
    }
    void Search_Dis_Win::paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.drawPixmap(0,0,width(),height(),QPixmap(":image/corn.jpg"));
    }
