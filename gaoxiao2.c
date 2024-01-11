#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>
typedef struct jiaoshi{
    int bianhao;
    char xingming[50];
    char xingbie;
    char xueyuan[50];
    char kecheng[5][30];
    double chengji;
    long long int xuehao;
    struct jiaoshi*next;
}jiaoshi;
typedef struct xuesheng{
    long long int xuehao;
    char mima[50];
    struct xuesheng*next;
}xuesheng;
void create(){
    FILE *file = fopen("D:\\pingjiaojiaoshi.txt", "r");//打开文件，没有这个文件file就是空的
    FILE *file2 = fopen("D:\\xueshengxinxi.txt", "r");
    if (file == NULL|| file2==NULL) {
        file = fopen("D:\\pingjiaojiaoshi.txt", "w");
        file2 = fopen("D:\\xueshengxinxi.txt", "w");
        if (file != NULL&&file2!=NULL) {
            printf("file create success\n");
        } else {
            printf("file create failed\n");
        }
    }
    if (file != NULL&&file2!=NULL) {
        fclose(file);
        fclose(file2);
    }
}
// 读取函数修改
void duqujiaoshi(jiaoshi** head) {
    FILE* fp = fopen("D:\\pingjiaojiaoshi.txt", "r");
    if (fp == NULL) {
        perror("无法打开文件");
        return;
    }
    *head=NULL;
    jiaoshi* current = *head;
    while (1) {
        jiaoshi* newop = (jiaoshi*)malloc(sizeof(jiaoshi));
        int itemsRead = fscanf(fp, "%d %49s %c %49s %29s %29s %29s %29s %29s %lf %lld",
                            &newop->bianhao, newop->xingming, &newop->xingbie,
                            newop->xueyuan, newop->kecheng[0],
                            newop->kecheng[1], newop->kecheng[2],
                            newop->kecheng[3], newop->kecheng[4],
                            &newop->chengji, &newop->xuehao);

        if (itemsRead == 11) {
            newop->next = NULL;
            if (*head == NULL) {
                *head = newop;
                current = newop;
            } else {
                current->next = newop;
                current = newop;
            }
        } else if (itemsRead == EOF) {
            free(newop);
            break;
        } else {
            free(newop);
            printf("文件格式错误或读取文件出错\n");
            break;
        }
    }
    fclose(fp);
}

void savefilejiaoshi(jiaoshi* head) {
    FILE* fp = fopen("D:\\pingjiaojiaoshi.txt", "w");
    if (fp == NULL) {
        perror("无法打开文件");
        return;
    }

    jiaoshi* newop = head;
    while (newop != NULL) {
        fprintf(fp, "%d %s %c %s %s %s %s %s %s %.2lf %lld",
                newop->bianhao, newop->xingming, newop->xingbie,
                newop->xueyuan, newop->kecheng[0], newop->kecheng[1],
                newop->kecheng[2], newop->kecheng[3], newop->kecheng[4],
                newop->chengji, newop->xuehao);
        fprintf(fp, "\n");
        newop = newop->next;
    }
    fclose(fp);
}

void duquxuesheng(xuesheng** head) {
    FILE* fp = fopen("D:\\xueshengxinxi.txt", "r");
    if (fp == NULL) {
        perror("Unable to open the file");
        return;
    }
    *head=NULL;
    xuesheng* current = NULL;
    char line[256]; // 假设每行不超过 256 个字符
    while (fgets(line, sizeof(line), fp) != NULL) {
        xuesheng* newop = (xuesheng*)malloc(sizeof(xuesheng));
        if (newop == NULL) {
            printf("Memory allocation failed.\n");
            break;
        }
        int result = sscanf(line, "%lld %49s", &newop->xuehao, newop->mima); // 使用 %49s 防止缓冲区溢出
        if (result == 2) {
            newop->next = NULL;
            if (*head == NULL) {
                *head = newop;
                current = newop;
            } else {
                newop->next = newop;
                current = newop;
            }
        } else {
            free(newop);
            printf("Incorrect file format.\n");
            break;
        }
    }
    fclose(fp);
}
void jiaoshicharu(jiaoshi** head) {
    jiaoshi* newjiao = (jiaoshi*)malloc(sizeof(jiaoshi));
    if (newjiao == NULL) {
        printf("内存分配失败。\n");
        return;
    }
    while (getchar() != '\n'); // 清理输入缓冲区
    printf("请输入姓名：\n");
    fgets(newjiao->xingming, sizeof(newjiao->xingming), stdin);
    newjiao->xingming[strcspn(newjiao->xingming, "\n")] = 0;

    printf("请输入性别('w'或'm')：\n");
    scanf(" %c", &newjiao->xingbie);
    while (getchar() != '\n'); // 清理输入缓冲区

    printf("请输入学院：\n");
    fgets(newjiao->xueyuan, sizeof(newjiao->xueyuan), stdin);
    newjiao->xueyuan[strcspn(newjiao->xueyuan, "\n")] = 0;

    printf("请输入课程，共五门：\n");
    for (int i = 0; i < 5; i++) {
        scanf("%29s", newjiao->kecheng[i]);
    }

    newjiao->chengji = 0.00;

    if (*head == NULL) {
        newjiao->bianhao = 1;
        newjiao->xuehao = 0;
        newjiao->next = NULL;
        *head = newjiao;
    } else {
        jiaoshi* current = *head;
        int max_bianhao = current->bianhao;

        while (current != NULL) {
            if (current->bianhao > max_bianhao) {
                max_bianhao = current->bianhao;
            }
            current = current->next;
        }

        newjiao->xuehao = 0;
        newjiao->bianhao = max_bianhao + 1;
        newjiao->next = *head;
        *head = newjiao;
    }
    savefilejiaoshi(*head);
}

void jiaoshixiugai(jiaoshi** head) {
    if (*head == NULL) {
        printf("链表为空\n");
        return;
    }

    char kecheng[5][50];
    char xingming[50];
    char xingbie;
    char xueyuan[50];

    printf("请输入老师姓名\n");
    getchar();
    scanf("%s", xingming);
    jiaoshi* current = *head;
    while (current ->next!= NULL && strcmp(current->xingming, xingming) != 0) {
        current = current->next;
    }
    if (current == NULL) {
        printf("未找到该教师\n");
        return;
    }

    printf("请给出您的选择\n");
    printf("1.修改性别\n");
    printf("2.修改学院\n");
    printf("3.修改课程(将所有的课程重新输入，共五次)\n");

    int n;
    scanf("%d", &n);
    switch (n) {
        case 1: {
            getchar();
            printf("请输入性别('w'or'm'):");
            xingbie = getchar();
            current->xingbie = xingbie;
            printf("成功\n");
            break;
        }
        case 2: {
            printf("请输入学院\n");
            scanf("%s", xueyuan);
            strcpy(current->xueyuan, xueyuan);
            printf("成功\n");
            break;
        }
        case 3: {
            printf("请重新输入五门课程\n");
            getchar();
            for (int i = 0; i < 5; i++) {
                scanf("%s", kecheng[i]);
            }
            for (int k = 0; k < 5; k++) {
                strcpy(current->kecheng[k], kecheng[k]);
            }
            printf("成功\n");
            break;
        }
        default: {
            printf("错误的选择,现在为您退出\n");
            break;
        }
    }
    savefilejiaoshi(*head);
}
void jiaoshishanchu(jiaoshi** head) {
    if (*head == NULL) {
        printf("链表为空\n");
        return;
    }

    jiaoshi* current = *head;
    jiaoshi* prev = NULL;
    
    // 获取用户输入的教师姓名
    char xingming[50];
    printf("给出您想删除的教师姓名\n");
    getchar();
    scanf("%s",xingming);

    // 在链表中查找要删除的教师
    while (current ->next!= NULL && strcmp(current->xingming, xingming) != 0) {
        prev=current;
        current = current->next;
    }
    if (current == NULL) {
        printf("未找到该教师\n");
        return;
    }
    if (current == NULL) {
        printf("未找到该教师\n");
        return;
    }
    // 确认是否删除该教师
    printf("您是否想删除这位教师 ('y' or 'n')? ");
    char con;
    getchar();
    con = getchar();

    if (con == 'y') {
        if (prev == NULL) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("删除成功\n");
        // 更新编号
        int new_bianhao = 1;  // 从1开始编号
        current = *head;
        while (current != NULL) {
            current->bianhao = new_bianhao++;
            current = current->next;
        }
        savefilejiaoshi(*head);  // 更新完编号后再保存到文件
    } else {
        printf("放弃删除教师\n");
    }
}

void xueshengcharu(xuesheng** headxue) {
    FILE* fp = fopen("D:\\xueshengxinxi.txt", "a"); // 使用 "a" 模式以追加方式打开文件
    if (fp == NULL) {
        perror("Unable to open the file");
        return;
    }
    xuesheng* newxue = (xuesheng*)malloc(sizeof(xuesheng));
    if (newxue == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return;
    }
    printf("请输入学生学号:\n");
    scanf("%lld", &newxue->xuehao);
    while (getchar() != '\n'); // 清除输入缓冲区中的换行符
    printf("请输入学生密码:\n");
    fgets(newxue->mima, sizeof(newxue->mima), stdin);
    newxue->mima[strcspn(newxue->mima, "\n")] = '\0'; // 移除末尾的换行符
    newxue->next = *headxue; // 插入到链表头部
    *headxue = newxue;
    fprintf(fp, "%lld %s\n", newxue->xuehao, newxue->mima); // 写入文件
    fclose(fp);
    printf("学生信息插入成功\n");
}
void xueshengpingjiao(xuesheng** headxue, jiaoshi** head) {
    long long int xuehao;
    char xingming[50];
    char mima[50];
    xuesheng* temp = *headxue;
    jiaoshi* current = *head;

    printf("请输入您的学号:\n");
    scanf("%lld", &xuehao);
    while (getchar() != '\n'); // 清除输入缓冲区中的换行符
    // 查找学生
    while (temp != NULL && xuehao != temp->xuehao) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("未找到该学生\n");
        return;
    }
    printf("请输入密码:\n");
    fgets(mima, sizeof(mima), stdin);
    mima[strcspn(mima, "\n")] = '\0'; // 移除末尾的换行符
    // 验证密码
    if (strcmp(temp->mima, mima) != 0) {
        printf("密码错误\n");
        return;
    }
    printf("密码正确，现在开始评教，请输入您想评教的老师姓名:\n");
    fgets(xingming, sizeof(xingming), stdin);
    xingming[strcspn(xingming, "\n")] = '\0'; // 移除末尾的换行符
    // 查找教师
    while (current->next!= NULL && strcmp(current->xingming, xingming) != 0) {
        current = current->next;
    }
    if (current == NULL) {
        printf("未找到这位老师，现在为您退出\n");
        return;
    }
    printf("成功找到这位老师，现在开始评教(共五门):\n");
    current->xuehao=temp->xuehao;
    int xuefen;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        printf("请对%s科目进行评教(输入1-100的分数): ", current->kecheng[i]);
        scanf("%d", &xuefen);
        sum += xuefen;
    }
    current->chengji = sum / 5; // 计算平均成绩
    printf("评教成功，为您退出\n");
    // 更新文件
    FILE* fp = fopen("D:\\pingjiaojiaoshi.txt", "w");
    if (fp == NULL) {
        perror("Unable to open the file");
        return;
    }
    jiaoshi* write_current = *head;
    while (write_current != NULL) {
        fprintf(fp, "%d %s %c %s %s %s %s %s %s %lf %lld\n",
                write_current->bianhao, write_current->xingming, write_current->xingbie,
                write_current->xueyuan, write_current->kecheng[0], write_current->kecheng[1],
                write_current->kecheng[2], write_current->kecheng[3], write_current->kecheng[4],
                write_current->chengji, write_current->xuehao);
        write_current = write_current->next;
    }
    fclose(fp);
}
void chaxunlaoshi(jiaoshi**head){ 
    duqujiaoshi(head);
    int found=0;
    jiaoshi*current=*head;
    printf("请输入您想查询老师的姓名\n");
    char xingming[50];
    getchar(); 
    scanf("%s",xingming);
    while(current!=NULL){
        if(strcmp(current->xingming,xingming)==0){
        found=1;
        break;
        }
        current=current->next;
    }
    if(found==0){
        printf("未找到该教师，为您退出\n");
        return;
    }else{
    printf("教师编号为%lld:\n",current->bianhao);
    printf("教师姓名为%s\n",current->xingming);
    printf("教师性别为%c\n",current->xingbie);
    printf("教师学院为%s\n",current->xueyuan);
    for(int i=0;i<5;i++) {
        printf("课程第%d项为%s\n",i+1,current->kecheng[i]);
    }
    printf("平均成绩为:%.2f(注意，未进行评测的成绩为0)\n",current->chengji);
    printf("输入完毕\n");
    }
}
void tongjichengji(jiaoshi**head){
    int fen[5]={0};
    jiaoshi*current=*head;
    while(current!=NULL){
        if(current->chengji<60){
            fen[0]+=1;
        }else if(current->chengji<70&&current->chengji>=60){
            fen[1]+=1;
        }else if(current->chengji <80&&current->chengji>=70){
            fen[2]+=1;
        }else if(current->chengji<90&&current->chengji>=80){
            fen[3]=1;
        }else if(current->chengji>=90){
            fen[4]+=1;
        }
        current=current->next;
    }
        printf("处于60分以下的老师有%d名\n",fen[0]);
        printf("处于60-70的老师有%d名\n",fen[1]);
        printf("处于70-80的老师有%d名\n",fen[2]);
        printf("处于80-90的老师有%d名\n",fen[3]);
        printf("处于90分以上的老师有%d名\n",fen[4]);
        printf("输出成功，为您退出\n");
}
void chaxunjiaoshi(jiaoshi**head){
	duqujiaoshi(head);
    char xingming[50];
    getchar(); 
    printf("请输入您想查询老师的姓名\n");
    scanf("%s",xingming);
    jiaoshi*current=*head;
    int found=0;
    while(current!=NULL){
        if(strcmp(current->xingming,xingming)==0){
        found=1;
        break;
        }
        current=current->next;
    }
    if(found==0){
        printf("未找到该教师，为您退出\n");
        return;
    }else{
    printf("教师编号为%lld:\n",current->bianhao);
    printf("教师姓名为%s\n",current->xingming);
    printf("教师性别为%c\n",current->xingbie);
    printf("教师学院为%s\n",current->xueyuan);
    }
}
void anxueyuan(jiaoshi** head) {
    int n = 0;
    jiaoshi* temp = *head;
    jiaoshi* prev = NULL;
    jiaoshi* current = *head;
    // 计算链表节点数量
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }
    // 使用冒泡排序对教师按成绩进行排序
    for (int i = 0; i < n - 1; i++) {
        prev = NULL;
        current = *head;
        for (int k = 0; k < n - 1 - i; k++) {
            // 比较当前节点和下一节点的成绩，并交换节点数据
            if (current->chengji < current->next->chengji) {
                 char temp_xingming[50];
                strcpy(temp_xingming, current->xingming);
                strcpy(current->xingming, current->next->xingming);
                strcpy(current->next->xingming, temp_xingming);
                char temp_xingbie = current->xingbie;
                current->xingbie = current->next->xingbie;
                current->next->xingbie = temp_xingbie;
                char temp_xueyuan[50];
                strcpy(temp_xueyuan, current->xueyuan);
                strcpy(current->xueyuan, current->next->xueyuan);
                strcpy(current->next->xueyuan, temp_xueyuan);
                for (int m = 0; m < 5; m++) {
                    char temp_kecheng[30];
                    strcpy(temp_kecheng, current->kecheng[m]);
                    strcpy(current->kecheng[m], current->next->kecheng[m]);
                    strcpy(current->next->kecheng[m], temp_kecheng);
                }
                double temp_chengji = current->chengji;
                current->chengji = current->next->chengji;
                current->next->chengji = temp_chengji;
                long long int temp_xuehao = current->xuehao;
                current->xuehao = current->next->xuehao;
                current->next->xuehao = temp_xuehao;
            }
            prev = current;
            current = current->next;
        }
    }
    char xueyuan[50];
    printf("请输入您想排序的学院名称：\n");
    getchar(); 
    fgets(xueyuan, sizeof(xueyuan), stdin);
    xueyuan[strcspn(xueyuan, "\n")] = '\0'; // 移除末尾的换行符
    current = *head;
    // 遍历链表输出指定学院的老师信息
    while (current != NULL) {
        if (strcmp(current->xueyuan, xueyuan) == 0) {
            printf("教师编号为%lld:\n", current->bianhao);
            printf("教师姓名为%s\n", current->xingming);
            printf("教师性别为%c\n", current->xingbie);
            printf("教师学院为%s\n", current->xueyuan);
            printf("平均成绩为:%d (未进行评测的成绩为0)\n", current->chengji);
        }
        current = current->next;
    }
    if(current == NULL){
    	printf("完毕\n");
	}
    savefilejiaoshi(*head); // 更新教师文件
}
void mmm(jiaoshi* head) {
    if (head == NULL) {
        printf("链表为空\n");
        return;
    }

    jiaoshi* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->bianhao);
        temp = temp->next;
    }
    printf("输完了\n");
}
int main(){
    SetConsoleOutputCP(65001);
    jiaoshi* head = NULL;
    xuesheng* headxue = NULL;
    int choice;
    create();
    do {

    	duqujiaoshi(&head);
        duquxuesheng(&headxue);
        printf("请输入您的选择\n");
        printf("1.插入教师信息\n");
        printf("2.修改老师信息\n");
        printf("3.删除老师信息\n");
        printf("4.插入学生信息\n");
        printf("5.学生评教\n");
        printf("6.查询老师得分\n");
        printf("7.统计评教成绩\n");
        printf("8.查询课程教师\n");
        printf("9.按学院排序\n");
        printf("10.退出\n");
        if (scanf("%d", &choice) != 1) {
            printf("请输入有效数字。\n");
            while (getchar() != '\n');
            continue;
        }
        switch(choice){
            case 1:{
                jiaoshicharu(&head);
                break;
            }
            case 2:{
                jiaoshixiugai(&head);
                break;
            }
            case 3:{
                jiaoshishanchu(&head);
                break;
            }
            case 4:{
                xueshengcharu(&headxue);
                break;
            }
            case 5:{
                xueshengpingjiao(&headxue, &head);
                break;
            }
            case 6:{
                chaxunlaoshi(&head);
                break;
            }
            case 7:{
                tongjichengji(&head);
                break;
            }
            case 8:{
                chaxunjiaoshi(&head);
                break;
            }
            case 9:{
                anxueyuan(&head);
                break;
            }
            case 10:{
                printf("程序结束。\n");
                return 0;
            }
            case 11:{
                mmm(head);
                printf("111"); 
                break; 
            }
            default:{
                printf("无效输入，请重新选择。\n");
            }
        }
    } while (1);
}
