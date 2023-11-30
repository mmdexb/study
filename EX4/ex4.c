#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>

struct people
{
    char name[20];
    int id;
    char gender;
    char phone[12];
    char qq[15];
    char poi[50];

};
typedef struct people people;
people peo[100];
int number ;
FILE *fp;

void updateNumber(){
    fp = fopen("people.dat","rb");
    if (fp == NULL)
    {
        printf("打开文件失败！");
    }
    //打开文件后检测是否为空文件
    fseek(fp,0,SEEK_END);
    number = ftell(fp)/sizeof(people);
    fclose(fp);
}




//新增联系人
void add (){
    people newadd;
    getchar();
    printf("请输入姓名: ");
    gets(newadd.name);
    printf("请输入性别(M/F): ");
    scanf("%c", &newadd.gender);
    getchar();
    printf("请输入手机号码(11位): ");
    gets(newadd.phone);
    printf("请输入QQ号: ");
    getchar();
    gets(newadd.qq);
    printf("请输入单位或班级: ");
    scanf("%s", newadd.poi);
    getchar();
    newadd.id=number;
    printf("你添加的是：\n");
    printf("%s\n",newadd.name);
    printf("%c\n",newadd.gender);
    printf("%s\n",newadd.phone);
    printf("%s\n",newadd.qq);
    printf("%s\n",newadd.poi);
    number++;
    fp = fopen("people.dat","ab");
    if (fp == NULL)
    {
        printf("打开文件失败！");
    }
    fwrite(&newadd,sizeof(people),1,fp);
    fclose(fp);
    printf("添加成功！\n");
    


}

void display(){
    people newdisplay;
    if (number==0)
    {
        printf("暂无联系人\n");
    }else{
        fp=fopen("people.dat","rb");
        if (fp == NULL)
        {
            printf("打开文件失败！");
        }

        printf("\n===== 联系人列表 =====\n");
        printf("%-5s% -15s% -5s% -20s% -20s% -20s\n", "序号", "姓名", "性别", "手机号码", "QQ号", "单位或班级");
        while (fread(&newdisplay,sizeof(people),1,fp)==1)
        {
            printf("%-5d %-15s %-5c %-20s %-20s %-20s\n",newdisplay.id,newdisplay.name,newdisplay.gender,newdisplay.phone,newdisplay.qq,newdisplay.poi);
        }

        fclose(fp);
        



    }
    


}  

void findbyName(char *name){
    people byname;
    int found=1;

    if (number==0)
    {
        printf("暂无联系人！");
    }else{
        fp=fopen("people.dat","rb");
        if (fp == NULL)
        {
            printf("打开文件失败！");
        }
        while(fread(&byname,sizeof(people),1,fp)==1){
            if (strcmp(byname.name,name)==0)
            {
                printf("找到名为%s的联系人\n",byname.name);
                printf("%-5d%-15s%-5c%-15s%-15s%-20s\n",byname.id,byname.name,byname.gender,byname.phone,byname.qq,byname.poi);
                found=0;

            }
            
        }
        if (found==1)
        {
            printf("没有找到名为%s的联系人",name);
        }
        
        

    }
    

}

void findbyPhone(char *phone){
    people byphone;
    int found=1;

    if (number==0)
    {
        printf("暂无联系人！");
    }else{
        fp=fopen("people.dat","rb");
        if (fp == NULL)
        {
            printf("打开文件失败！");
        }
        while(fread(&byphone,sizeof(people),1,fp)==1){
            if (strcmp(byphone.phone,phone)==0)
            {
                printf("找到电话号码为%s的联系人\n",byphone.phone);
                printf("%-5d%-15s%-5c%-15s%-15s%-20s\n",byphone.id,byphone.name,byphone.gender,byphone.phone,byphone.qq,byphone.poi);
                found=0;

            }
            
        }
        if (found==1)
        {
            printf("没有找到电话号码为%s的联系人",phone);
        }
        
        

    }

}


void oddbyName(){
    people* arr=(people*)malloc(number*sizeof(people));
    fp=fopen("people.dat","rb");
    if (fp=NULL)
    {
        printf("文件打开失败\n");
    }
    if (number==0)
    {
        printf("暂无联系人\n");
    }else{
        int i=0;
        while ((fread(&arr[i],sizeof(people),1,fp))==1)
        {
            i++;
            if (i==number)
            {
                break;
            }
            
        }
        //按名称排序
        for ( i = 0; i < number; i++)
        {
            for (int j = 0; j < number-i-1; j++)
            {
                if(arr[j].name[0]>arr[j+1].name[0]){
                    people temp =arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }else if (arr[j].name[0]==arr[j+1].name[0])
                {
                    if(arr[j].name[1]>arr[j+1].name[1]){
                        people temp =arr[j];
                        arr[j]=arr[j+1];
                        arr[j+1]=temp;                    
                    }
                }                                                    
                
            }
            
        }

        fclose(fp);

        fp=fopen("people_odd.dat","wb");
        fwrite(arr,sizeof(people),number,fp);

        for (i = 0; i < number; i++)
        {
        printf("\n===== 按名字排序 =====\n");
        printf("%-5s%-15s%-5s%-15s%-15s%-20s\n", "序号", "姓名", "性别", "手机号码", "QQ号", "单位或班级");
        printf("%-5d%-15s%-5c%-15s%-15s%-20s\n",arr[i].id,arr[i].name,arr[i].gender,arr[i].phone,arr[i].qq,arr[i].poi);           
        }

        fclose(fp);
        

    }
    
    


}
void delbyName(char *delname){  
    people* delarr=(people*)malloc(number*sizeof(people));
    fp=fopen("people.dat","rb");
    if (fp==NULL)
    {
        printf("文件打开失败\n");
    }
    if (number==0)
    {
        printf("暂无联系人\n");
    }else{
        int i=0;
        int found=0;
        int index;
        char choice2;
        fread(delarr,sizeof(people),number,fp);
        
        //在数组中循环找到需要删除的名字
        for (i = 0; i < number; i++)
        {
            if (strcmp(delarr[i].name,delname)==0)
            {
                printf("找到名为%s的联系人，将删除\n",delarr[i].name);
                printf("%-5d%-15s%-5c%-15s%-15s%-20s\n",delarr[i].id,delarr[i].name,delarr[i].gender,delarr[i].phone,delarr[i].qq,delarr[i].poi);
                printf("确定删除？(y/n)");

                found=1;
                index=i;
                
            }
            
        }
        if (found==0) {
            printf("未找到名字为%s的联系人。\n", delname);
            return;
        }

        char confirmation;
        printf("确认删除该联系人信息？(y/n): ");
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') {
            // 删除联系人信息
            for (int i = index; i < number - 1; i++) {
                delarr[i] = delarr[i + 1];
            }
            number--;

            printf("删除成功！\n");
        } else {
            printf("未被删除。\n");
        }
        
    }
    fclose(fp);
    //覆写数组
    fp=fopen("people.dat","wb");
    fwrite(delarr,sizeof(people),number,fp);
    fclose(fp);
    free(delarr);

}

int main(){
    SetConsoleOutputCP(65001);
    updateNumber();
    printf("**********************************\n");
    printf("*网安233 陈薏帆 202301050854*\n");
    printf("**********************************\n");
    while(1){
    printf("欢迎使用联系人系统\n");
    printf("1.添加联系人\n");
    printf("2.显示联系人\n");
    printf("3.查找联系人\n");
    printf("4.删除联系人\n");
    printf("5.按姓名排序\n");
    printf("0.退出系统\n");
    int choice;
    int choice2;
    char findname[20];
    char findphone[11];
    char delname[20];
    
    printf("请输入你的选择：");
        
    scanf("%d",&choice);
        
    switch(choice){
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                printf("1.按姓名查找\n");
                printf("2.按电话号码查找\n");
                scanf("%d",&choice2);
                getchar();
                switch(choice2){
                    case 1:
                        printf("请输入要查找的姓名：");
                        gets(findname);
                        getchar();
                        findbyName(findname);
                        break;
                    case 2:
                        printf("请输入要查找的电话号码：");
                        gets(findphone);
                        getchar();
                        findbyPhone(findphone);
                        break;
                    default:
                        printf("输入错误，请重新输入\n");
                        break;
                }
                
                break;
            case 4:
                
                printf("请输入要删除的联系人姓名: \n");
                getchar();
                gets(delname);
                delbyName(delname);
                break;
            case 5:
                oddbyName();
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("输入错误，请重新输入\n");
                break;
        }
    }
}








