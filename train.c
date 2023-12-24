#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<Windows.h>
struct node
{
    char name[12];//乘客姓名
    char IDcara[20];//乘客身份证号码
    int TicketNum;//订票数
    float FareSum;//总票价
    struct node* next;//指针成员
};
typedef struct node node;
struct Dtime
{
    short year;
    short month;
    short day;
    short hour;
    short minute;
};
typedef struct Dtime dtime;
struct train
{
    char terminal[20];//终点站
    char sequence[20];//车次
    struct Dtime StartTime;//发车时间
    float fare;//票价
    int SpareTicketNum;//余票数
    struct node * head;//指针成员,指向该线路第一个订票乘客
};
typedef struct train train;

train Trains[5];

void CreatFile(){
    FILE *fp=fopen("train.dat","rb");
    if (fp==NULL)
    {
        fp=fopen("train.dat","wb");
        char terminal1[20] = "BeiJing";
        strcpy(Trains[0].terminal, terminal1);
        char sequence1[20] = "G201";
        strcpy(Trains[0].sequence, sequence1);
        Trains[0].StartTime.year = 2023;
        Trains[0].StartTime.month = 12;
        Trains[0].StartTime.day = 23;
        Trains[0].StartTime.hour = 14;
        Trains[0].StartTime.minute = 5;
        Trains[0].fare = 100.0;
        Trains[0].SpareTicketNum = 300;
        Trains[0].head = NULL;


        fwrite(&Trains[0], sizeof(train), 1, fp);

        // 火车2信息
        char terminal2[20] = "ShangHai";
        strcpy(Trains[1].terminal, terminal2);
        char sequence2[20] = "D102";
        strcpy(Trains[1].sequence, sequence2);
        Trains[1].StartTime.year = 2023;
        Trains[1].StartTime.month = 11;
        Trains[1].StartTime.day = 15;
        Trains[1].StartTime.hour = 10;
        Trains[1].StartTime.minute = 30;
        Trains[1].fare = 150.0;
        Trains[1].SpareTicketNum = 300;
        Trains[1].head = NULL;

        fwrite(&Trains[1], sizeof(train), 1, fp);

        // 火车3信息
        char terminal3[20] = "GuangZhou";
        strcpy(Trains[2].terminal, terminal3);
        char sequence3[20] = "K888";
        strcpy(Trains[2].sequence, sequence3);
        Trains[2].StartTime.year = 2023;
        Trains[2].StartTime.month = 10;
        Trains[2].StartTime.day = 5;
        Trains[2].StartTime.hour = 8;
        Trains[2].StartTime.minute = 45;
        Trains[2].fare = 200.0;
        Trains[2].SpareTicketNum = 300;
        Trains[2].head = NULL;

        fwrite(&Trains[2], sizeof(train), 1, fp);

        // 火车4信息
        char terminal4[20] = "ChengDu";
        strcpy(Trains[3].terminal, terminal4);
        char sequence4[20] = "T123";
        strcpy(Trains[3].sequence, sequence4);
        Trains[3].StartTime.year = 2023;
        Trains[3].StartTime.month = 9;
        Trains[3].StartTime.day = 12;
        Trains[3].StartTime.hour = 16;
        Trains[3].StartTime.minute = 20;
        Trains[3].fare = 250.0;
        Trains[3].SpareTicketNum = 300;
        Trains[3].head = NULL;


        fwrite(&Trains[3], sizeof(train), 1, fp);

        // 火车5信息
        char terminal5[20] = "HangZhou";
        strcpy(Trains[4].terminal, terminal5);
        char sequence5[20] = "G102";
        strcpy(Trains[4].sequence, sequence5);
        Trains[4].StartTime.year = 2023;
        Trains[4].StartTime.month = 8;
        Trains[4].StartTime.day = 18;
        Trains[4].StartTime.hour = 12;
        Trains[4].StartTime.minute = 45;
        Trains[4].fare = 300.0;
        Trains[4].SpareTicketNum = 300;
        Trains[4].head = NULL;

        fwrite(&Trains[4], sizeof(train), 1, fp);

        fclose(fp);
        printf("文件创建成功！\n");
        printf("火车数据已写入!\n");

 
    }
    if (fp!=NULL)
    {
        fclose(fp);
    }
    

}


void ReadFile2Arr(){
    FILE* file = fopen("train.dat", "rb");

    if (file != NULL)
    {
        fread(Trains, sizeof(train), 5, file);

        // 读取链表信息
        for (int i = 0; i < 5; ++i)
        {
            node* current = Trains[i].head;
            node* prev = NULL;

            while (current != NULL)
            {
                node* newnode = (node*)malloc(sizeof(node));
                newnode->next=NULL;
                fread(newnode, sizeof(node), 1, file);
                if (prev == NULL)
                {
                    Trains[i].head = newnode;
                    current=newnode;
                }
                else
                {
                    current=newnode;
                    prev->next = newnode;
                }

                prev = newnode;
                if (current->next == NULL)
                {
                    break;
                }
                
                current = current->next;
            }
        }

        fclose(file);
    }
}

void UpdateTrainsArr(){
   FILE* file = fopen("train.dat", "wb");

    if (file != NULL) 
    {
        // 写入结构体数组
        fwrite(Trains, sizeof(train), 5, file);

        // 写入链表信息
        for (int i = 0; i < 5; ++i)
        {
            node* current = Trains[i].head;
            if (current==NULL)
            {
                fwrite(current, sizeof(node), 1, file);
            }else{
                while (current!= NULL)
                {
                    fwrite(current, sizeof(node), 1, file);
                    current = current->next;
                }
                
            }
        }

        fclose(file);
    }


}

void FindTrains(){
    ReadFile2Arr();
    char terminal[20];
    char sequence[20];
    int found=0;
    int i;
    printf("请输入终点站：");
    scanf("%s",terminal);
    printf("请输入车次：");
    scanf("%s",sequence);
    for (i = 0; i < 5; i++)
    {
        if (strcmp(Trains[i].terminal, terminal) == 0 && strcmp(Trains[i].sequence, sequence) == 0){
            printf("该车次在%s站发车，发车时间为%d年%d月%d日%d时%d分，票价为%.2f元，余票数为%d张\n",Trains[i].terminal,Trains[i].StartTime.year,Trains[i].StartTime.month,Trains[i].StartTime.day,Trains[i].StartTime.hour,Trains[i].StartTime.minute,Trains[i].fare,Trains[i].SpareTicketNum);
            found=1;

        }
    }
    if (found==0){
        printf("该车次不存在！\n");
    }
}

void orderTicket(){
    ReadFile2Arr();
    char sequence[20];
    int OdderNum;
    int i;
    int found=0;
    printf("请输入车次：");
    scanf("%s",sequence);
    for (i = 0; i < 5; i++)
    {
        if (strcmp(Trains[i].sequence, sequence) == 0){
            found=1;
            printf("请输入订票人数：");
            scanf("%d",&OdderNum);
            if (OdderNum>Trains[i].SpareTicketNum){
                printf("余票不足！\n");
                return ;
            }else{
                char name[20];
                char IDcara[20];
                int TicketNum=OdderNum;
                float FareSum;
                
                printf("请输入订票人姓名: ");
                scanf("%s",name);
                printf("请输入订票人身份证号: ");
                scanf("%s",IDcara);
                FareSum=TicketNum*Trains[i].fare;
                printf("您订购了%d张票，单张票价为%.2f元，总票价为%.2f元，余票数为%d张\n",TicketNum,Trains[i].fare,FareSum,Trains[i].SpareTicketNum-TicketNum);

                //前端完成，进行链表添加
                node *newnode=(node *)malloc(sizeof(node));
                strcpy(newnode->name,name);
                strcpy(newnode->IDcara,IDcara);
                newnode->FareSum=FareSum;
                newnode->TicketNum=TicketNum;
                newnode->next=NULL;

                if(Trains[i].head==NULL){
                    Trains[i].head=newnode;
                    Trains[i].SpareTicketNum-=TicketNum;
                }else{
                    node *temp=Trains[i].head;
                    while(temp->next!=NULL){
                        temp=temp->next;
                    }
                    temp->next=newnode;
                    Trains[i].SpareTicketNum-=TicketNum;

                }
                //添加完成，更新文件
                UpdateTrainsArr();
                printf("订单已成功提交！\n");
            }
        }
    }
    if (found==0)
    {
        printf("该车次不存在！\n");
    }
    


}

void delTicket(){
    ReadFile2Arr();
    char sequence[20];
    int i;
    char IDcara[20];
    int delnumber;
    int found=0;
    int found2=0;
    printf("请输入身份证号：");
    scanf("%s",IDcara);
    printf("请输入车次： ");
    scanf("%s",sequence);

    for ( i = 0; i < 5; i++)
    {
        if (strcmp(Trains[i].sequence, sequence) == 0)
        {
            found2=1;
            printf("找到车次%s\n",sequence);
            if (Trains[i].head==NULL){
                printf("该车次没有订单！\n");
                return ;
            }else{
                printf("该车次有订单！\n");
                printf("开始查找身份证号为%s的乘客\n",IDcara);
                node *temp=Trains[i].head;
                node *prev=NULL;
                while(temp!=NULL){
                    if (strcmp(temp->IDcara,IDcara)==0){
                        found=1;
                        printf("找到身份证号为%s的乘客，您订购了%d张票\n",IDcara,temp->TicketNum);
                        printf("请输入退票的数量： ");
                        scanf("%d",&delnumber);

                        while (delnumber<=0||delnumber>temp->TicketNum)
                        {
                            if (delnumber>temp->TicketNum)
                            {
                                printf("退票数量大于订票数量！请重试！\n");
                            }else{
                                printf("退票数量小于0！请重试！\n");
                            }

                            scanf("%d",&delnumber);
                            
                        }

                        //如果退票数量等于订票数量，直接删除节点
                        if (delnumber==temp->TicketNum)
                        {
                            prev->next=temp->next;
                            printf("退票成功！由于您的退票数量等于订票数量，您的订单已被删除！\n");
                            return ;
                            //处理票的数量
                            Trains[i].SpareTicketNum+=temp->TicketNum;
                            free(temp);
                            UpdateTrainsArr();
                        }
                        //如果退票数量小于订票数量
                        else{
                            temp->TicketNum-=delnumber;
                            printf("退票成功！您剩余%d张票\n",temp->TicketNum);
                            //处理票的数量
                            Trains[i].SpareTicketNum=Trains[i].SpareTicketNum+delnumber;
                            temp->FareSum=temp->FareSum-delnumber*Trains[i].fare;
                            UpdateTrainsArr();
                            return ;
                        }
                    }

                    temp=temp->next;
                    prev=temp;
                }
                if (found==0)
                {
                    printf("未能找到身份证号为%s的乘客\n",IDcara);
                    return;
                }
                
            }

        }
        
    }
    if (found2==0)
    {
        printf("未能找到车次%s\n",sequence);
        return;
    }
    

}

void FindBysequence(){
    ReadFile2Arr();
    char sequence[20];
    int i;
    printf("请输入车次：");
    scanf("%s",sequence);
    for (i = 0; i < 5; i++)
    {
        if (strcmp(Trains[i].sequence, sequence) == 0){
            printf("以下是列车信息\n");
            printf("终点站: %s\n",Trains[i].terminal);
            printf("列车号：%s\n",Trains[i].sequence);
            printf("发车时间：%hd年%hd月%hd日%hd时%hd分\n",Trains[i].StartTime.year,Trains[i].StartTime.month,Trains[i].StartTime.day,Trains[i].StartTime.hour,Trains[i].StartTime.minute);
            printf("票价: %.2f\n",Trains[i].fare);
            printf("余票数: %d\n",Trains[i].SpareTicketNum);
            printf("--------------------------------------------------------\n");
            printf("以下是乘客信息\n");
            node *temp=Trains[i].head;
            while(temp!=NULL){
                printf("订票人姓名：%s\n",temp->name);
                printf("订票人身份证号：%s\n",temp->IDcara);
                printf("订票人订购的票数：%d\n",temp->TicketNum);
                printf("订票人支付的票价：%.2f\n",temp->FareSum);
                printf("--------------------------------------------------------\n");
                temp=temp->next;
            }
            return;
        }
    }
    printf("未能找到该车次！\n");
}

void FindBysequence2tickets(){
    ReadFile2Arr();
    char sequence[20];
    int i;
    int found=0;
    printf("请输入车次：");
    scanf("%s",sequence);
    for (i = 0; i < 5; i++)
    {
        if (strcmp(Trains[i].sequence, sequence) == 0){
            printf("以下是%s列车票务信息\n",sequence);
            printf("余票数: %d\n",Trains[i].SpareTicketNum);
            printf("订票数: %d\n",300-Trains[i].SpareTicketNum);
            return;
            found=1;
        }
        
    }
    if (found==0)
    {
        printf("未能找到该车次！\n");
    }
            
}

void FindByTerminal(){
    ReadFile2Arr();
    char terminal[20];
    int i;
    int found=0;

    printf("请输入终点站: ");
    scanf("%s",terminal);

    for ( i = 0; i < 5; i++)
    {
        if (strcmp(Trains[i].terminal, terminal) == 0)
        {
            printf("以下是列车信息\n");
            printf("终点站: %s\n",Trains[i].terminal);
            printf("列车号：%s\n",Trains[i].sequence);
            printf("发车时间：%hd年%hd月%hd日%hd时%hd分\n",Trains[i].StartTime.year,Trains[i].StartTime.month,Trains[i].StartTime.day,Trains[i].StartTime.hour,Trains[i].StartTime.minute);
            printf("票价: %.2f\n",Trains[i].fare);
            printf("余票数: %d\n",Trains[i].SpareTicketNum);
            printf("--------------------------------------------------------\n");
            found=1;
        }
        
    }
    if (found==0)
    {
        printf("未能找到终点站为%s的列车\n",terminal);
    }

}

void FindByTime(){
    ReadFile2Arr();
    short year,month,day;
    int i;
    int found=0;
    printf("请输入发车时间：\n");
    printf("年：");
    scanf("%hd",&year);
    printf("月：");
    scanf("%hd",&month);
    printf("日：");
    scanf("%hd",&day);

    for ( i = 0; i < 5; i++)
    {
        if(Trains[i].StartTime.year==year&&Trains[i].StartTime.month==month&&Trains[i].StartTime.day==day){
            printf("以下是在%hd年%hd月%hd日发车的列车信息\n",year,month,day);
            printf("终点站: %s\n",Trains[i].terminal);
            printf("列车号：%s\n",Trains[i].sequence);
            printf("发车时间：%hd年%hd月%hd日%hd时%hd分\n",Trains[i].StartTime.year,Trains[i].StartTime.month,Trains[i].StartTime.day,Trains[i].StartTime.hour,Trains[i].StartTime.minute);
            printf("票价: %.2f\n",Trains[i].fare);
            printf("余票数: %d\n",Trains[i].SpareTicketNum);
            printf("--------------------------------------------------------\n");
            found=1;
        }
    }
    if (found==0)
    {
        printf("未能找到发车时间为%hd年%hd月%hd日的列车\n",year,month,day);
    }
    
    
}

void FindEmpty(){
    ReadFile2Arr();
    int found=0;
    for (int i = 0; i < 5; i++)
    {
        if (Trains[i].SpareTicketNum==0)
        {
            printf("以下是无票列车信息\n");
            printf("终点站: %s\n",Trains[i].terminal);
            printf("列车号：%s\n",Trains[i].sequence);
            printf("发车时间：%hd年%hd月%hd日%hd时%hd分\n",Trains[i].StartTime.year,Trains[i].StartTime.month,Trains[i].StartTime.day,Trains[i].StartTime.hour,Trains[i].StartTime.minute);
            printf("票价: %.2f\n",Trains[i].fare);
            printf("--------------------------------------------------------\n");
            found=1;
        }
    }

    if (found==0)
    {
        printf("未能找到无票列车\n");
    }
    
}
void showAllTrains(){
    ReadFile2Arr();
    for (int i = 0; i < 5; i++)
    {
        printf("以下是%s列车信息\n",Trains[i].sequence);
        printf("终点站: %s\n",Trains[i].terminal);
        printf("列车号：%s\n",Trains[i].sequence);
        printf("发车时间：%hd年%hd月%hd日%hd时%hd分\n",Trains[i].StartTime.year,Trains[i].StartTime.month,Trains[i].StartTime.day,Trains[i].StartTime.hour,Trains[i].StartTime.minute);
        printf("票价: %.2f\n",Trains[i].fare);
        printf("余票数: %d\n",Trains[i].SpareTicketNum);
        printf("--------------------------------------------------------\n");
        
    }
}

int main(){
    SetConsoleOutputCP(65001);
    CreatFile();
    printf("**********************************\n");
    printf("*网安233 陈薏帆 202301050854*\n");
    printf("**********************************\n");
    while (1)
    {
        printf("欢迎使用火车定票管理系统\n");
        printf("0.展示全部线路\n");
        printf("1.火车线路查询\n");
        printf("2.订票\n");
        printf("3.退票\n");
        printf("4.列车查询\n");
        printf("5.退出\n");
        printf("请输入你的选择：");
        int choice;
        int choice2;
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            FindTrains();
            break;
        case 2:
            orderTicket();
            break;
        case 3:
            delTicket();
            break;
        case 4:
            printf("请输入查询内容：\n");
            printf("1.按车次查询全部订票信息\n");
            printf("2.按车次查询订票数和余票数\n");
            printf("3.按终点站查询火车信息\n");
            printf("4.按发车时间查询火车信息\n");
            printf("5.查询无票列车\n");
            scanf("%d",&choice2);
            switch (choice2)
            {
            case 1:
                FindBysequence();
                break;
            case 2:
                FindBysequence2tickets();
                break;
            case 3:
                FindByTerminal();
                break;
            case 4:
                FindByTime();
                break;
            case 5:
                FindEmpty();
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
            }
            break;
        case 5:
            exit(0);
            break;
        case 0:
            showAllTrains();
            break;
        default:
            printf("输入错误，请重新输入！\n");
            break;
        }

    }
    return 0;
}
    

           






    


