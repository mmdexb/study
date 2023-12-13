#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<Windows.h>

struct people
{
    char name[20];
    int id;
    char gender;
    char phone[12];
    char qq[15];
    char poi[50];

    struct people *next;

};
typedef struct people people;
int number;
FILE *fp;

void FreeList(people *head) {
    people *cur = head;
    while (cur != NULL) {
        people *next = cur->next;
        free(cur);
        cur = next;
    }
}

void createFile() {
    FILE *file = fopen("peo.dat", "r");
    if (file == NULL) {
        file = fopen("peo.dat", "w");
        if (file != NULL) {
            printf("success\n");
        } else {
            printf("Failed\n");
        }
    }
    if (file != NULL) {
        fclose(file);
    }
}

people *ReadFile() {
    FILE *fp = fopen("peo.dat", "rb");
    if (fp == NULL) {
        printf("Failed to open file!\n");
        return NULL;  
    }

    people *head = NULL, *temp = NULL;
    while (1) {
        people *newp = (people *)malloc(sizeof(people));
        if (fread(newp, sizeof(people), 1, fp) != 1) {
            free(newp);  // 如果读取失败，释放分配的内存并退出循环
            break;
        }
        newp->next = NULL;

        if (head == NULL) {
            head = newp;  // 如果链表为空，新节点成为头节点
        } else {
            temp->next = newp;  // 否则，添加到链表末尾
        }
        temp = newp;  // 更新 temp 指向新的末尾节点
    }

    fclose(fp);
    return head;
}



void WriteFile(people *head) {
    FILE *fp = fopen("peo.dat", "wb");
    if (fp == NULL) {
        printf("Failed to open file for writing!\n");
        return;
    }

    people *temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(people), 1, fp);
        temp = temp->next;
    }

    fclose(fp);
}

int newID(){
    people *head = ReadFile();
    if (head==NULL)
    {
        FreeList(head);
        return 0;
    }else{

        int id=0;
        people *temp=head;
        while (temp->next!=NULL)
        {
            temp=temp->next;   
        }
        id=temp->id;
        FreeList(head);
        return id+1;

    }

}

void Add(){
    people *head = ReadFile(); 

    people *add=(people *)malloc(sizeof(people));
    add->next=NULL;
    getchar();
    printf("输入姓名: ");
    gets(add->name);
    printf("输入性别(M/F): ");
    scanf("%c", &add->gender);
    getchar();
    printf("输入电话号码: ");
    gets(add->phone);
    printf("输入QQ号码: ");
    gets(add->qq);
    printf("输入单位或班级: ");
    gets(add->poi); 
    add->id=newID();

    add->next=head;
    head=add;

    WriteFile(head);
    FreeList(head);
    printf("Success!\n");
    

}

void display(){
    people *head = ReadFile();

    if (head == NULL) {
        printf("联系人列表为空！\n");
        return;
    }
    people* temp=head;

    printf("%-5s%-15s%-5s%-20s%-20s%-20s\n", "序号", "\t姓名", "\t性别", "\t手机号码", "\tQQ号", "\t单位或班级");
    while (temp!=NULL)
    {
        printf("%-5d %-15s %-5c %-20s %-20s %-20s\n",temp->id,temp->name,temp->gender,temp->phone,temp->qq,temp->poi);
        temp=temp->next;
    }
    FreeList(head);

}

void findbyName(char *name){
    people *head = ReadFile();
    people* temp=head;
    int found=0;

    while (temp!=NULL)
    {
        if (strcmp(temp->name,name)==0)
        {
            printf("找到名为%s的联系人\n",temp->name);
            printf("%-5s%-15s%-5s%-20s%-20s%-20s\n", "序号", "\t姓名", "\t性别", "\t手机号码", "\tQQ号", "\t单位或班级");
            printf("%-5d %-15s %-5c %-20s %-20s %-20s\n",temp->id,temp->name,temp->gender,temp->phone,temp->qq,temp->poi);
            found=1;

        }
        temp=temp->next;
        
    }

    if (found==0)
    {
        printf("找不到名为%s的联系人\n",name);
    }
    FreeList(head);
}

void findbyPhone(char *phone){
    people *head = ReadFile();
    people* temp=head;
    int found=0;

    while (temp!=NULL)
    {
        if (strcmp(temp->phone,phone)==0)
        {
            printf("找到名为%s的联系人\n",temp->phone);
            printf("%-5s%-15s%-5s%-20s%-20s%-20s\n", "序号", "\t姓名", "\t性别", "\t手机号码", "\tQQ号", "\t单位或班级");
            printf("%-5d %-15s %-5c %-20s %-20s %-20s\n",temp->id,temp->name,temp->gender,temp->phone,temp->qq,temp->poi);
            found=1;

        }
        temp=temp->next;
        
    }

    if (found==0)
    {
        printf("找不到电话号码为%s的联系人\n",phone);
    }
    FreeList(head);
}

void displaySorted(){
    FILE *k;
    k = fopen("sorted_people.dat", "rb");

    if (k != NULL) {
        printf("排序后的联系人信息：\n");

        people dcurrent; // 创建一个结构体变量而不是指针
        printf("%-5s%-15s%-5s%-20s%-20s%-20s\n", "序号", "\t姓名", "\t性别", "\t手机号码", "\tQQ号", "\t单位或班级");
        while (fread(&dcurrent, sizeof(people), 1, k)) { // 注意这里 &dcurrent
            printf("%-5d %-15s %-5c %-20s %-20s %-20s\n",dcurrent.id,dcurrent.name,dcurrent.gender,dcurrent.phone,dcurrent.qq,dcurrent.poi);
        }

        fclose(k); 
    } 
}

void SortbyName() {
    people *head = ReadFile();
    if (head == NULL || head->next == NULL) {
        return;  
    }

    
    people *sortedHead = NULL;
    people *current, *next;

    for (current = head; current != NULL; current = current->next) {
        people *newNode = (people *)malloc(sizeof(people));

        // 复制
        strcpy(newNode->name, current->name);
        newNode->id = current->id;
        newNode->gender = current->gender;
        strcpy(newNode->phone, current->phone);
        strcpy(newNode->qq, current->qq);
        strcpy(newNode->poi, current->poi);
        newNode->next = NULL;


        if (sortedHead == NULL || strcmp(newNode->name, sortedHead->name) <= 0) {
            newNode->next = sortedHead;
            sortedHead = newNode;
        } else {
            people *prev = NULL;
            next = sortedHead;

            while (next != NULL && strcmp(newNode->name, next->name) > 0) {
                prev = next;
                next = next->next;
            }

            newNode->next = next;
            prev->next = newNode;
        }
    }

    FILE *sortedFile = fopen("sorted_people.dat", "wb");

    current = sortedHead;
    while (current != NULL) {
        fwrite(current, sizeof(people), 1, sortedFile);
        current = current->next;
    }

    fclose(sortedFile);


    current = sortedHead;
    while (current != NULL) {
        people *temp = current;
        current = current->next;
        free(temp);
    }

    displaySorted();   
    FreeList(head);
}



    



void DeleteByName(const char *targetName) {
    people *head = ReadFile();
    if (head == NULL) {
        printf("链表为空，无法删除。\n");
        return;
    }
    int found=1;
    people *current = head;
    people *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, targetName) == 0) {
            found=0;
            printf("确认删除姓名为 %s 的联系人吗？(y/n): \n", targetName);
            printf("%-5s%-15s%-5s%-20s%-20s%-20s\n", "序号", "\t姓名", "\t性别", "\t手机号码", "\tQQ号", "\t单位或班级");
            printf("%-5d %-15s %-5c %-20s %-20s %-20s\n",current->id,current->name,current->gender,current->phone,current->qq,current->poi);
            char confirmation;
            scanf(" %c", &confirmation);
            if (confirmation == 'y' || confirmation == 'Y') {
                if (prev == NULL) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }

                free(current);
                printf("已删除姓名为 %s 的联系人。\n", targetName);
            } else {
                printf("取消删除。\n");
            }

            break;
        }

        prev = current;
        current = current->next;
    }
    WriteFile(head);
    FreeList(head); 
    if (found==1)
    {
        printf("没有找到对应联系人\n");
    }
    
}


int main(){
    createFile();
    SetConsoleOutputCP(65001);
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
                Add();
                break;
            case 2:
                display();
                break;
            case 3:
                printf("1.按姓名查找\n");
                printf("2.按电话号码查找\n");
                scanf("%d",&choice2);
                
                switch(choice2){
                    case 1:
                        getchar();
                        printf("请输入要查找的姓名：");
                        gets(findname);
                        findbyName(findname);
                        break;
                    case 2:
                        getchar();
                        printf("请输入要查找的电话号码：");
                        gets(findphone);
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
                DeleteByName(delname);
                break;
            case 5:
                SortbyName();
                //displaySorted();
                
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

