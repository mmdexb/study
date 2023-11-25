#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

struct student
{
    char name[20];
    int id;
    int class_num;
    float score[3];
};

struct student students[100];
int number=0;

int sortArrMin(float *arr) {
    int min = 0;
    for (int i = 0; i < number; i++) {
        min = i;
        for(int j = i + 1; j < number; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        
        float temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    return min;
}

int sortArrMax(float *arr) {
    int max = 0;
    for (int i = 0; i < number; i++) {
        max = i;
        for(int j = i + 1; j < number; j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        
        float temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
    }
    return max;
}


void bubble_sort(int arr[], int len) {
        int i, j, temp;
        for (i = 0; i < len - 1; i++)
                for (j = 0; j < len - 1 - i; j++)
                        if (arr[j] < arr[j + 1]) {
                                temp = arr[j];
                                arr[j] = arr[j + 1];
                                arr[j + 1] = temp;
                        }
}

//添加学生函数
void add(){
    if(number<100){
        printf("请输入学生姓名：\n");
        scanf("%s",students[number].name);
        printf("请输入学生学号：\n");
        scanf("%d",&students[number].id);
        printf("请输入学生班级：\n");
        scanf("%d",&students[number].class_num);
        printf("请输入学生三门成绩：\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f",&students[number].score[i]);
        }
        number++;
    }else{
        printf("已到达人数上限");
    }
   
        
}

//打印全部学生
void display(){
    if (number==0)
    {
        printf("目前还没有任何学生");
    }else{
        printf("学生信息如下：\n");
        printf("--------------------------------------------------\n");
        printf("| 学号 |   姓名   | 班级 |  课程1  |  课程2  |  课程3  |\n");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < number; i++)
        {
            struct student *display= &students[i];
            printf("| %4d | %-8s | %4d | %.2f | %.2f | %.2f |\n",
               display->id, display->name, display->class_num,
               display->score[0], display->score[1], display->score[2]);
        }
        printf("--------------------------------------------------\n");
    }
    
}
void findByid(int id){
    if (number==0)
    {
        printf("目前还没有任何学生");
    }else{
        for (int i = 0; i < number; i++)
        {
            if (id==students[i].id)
            {
                printf("找到学生信息：\n");
                printf("姓名：%s\n", students[i].name);
                printf("学号：%d\n", students[i].id);
                printf("班级：%d\n", students[i].class_num);
                printf("课程成绩：%.2f %.2f %.2f\n",
                    students[i].score[0], students[i].score[1], students[i].score[2]); 
            }else{
            
             printf("没有找到此学生\n");
            }
             
        }
        

    }
    
}

void findByname(char *name){
    int found=0;
    if (number==0)
    {
        printf("目前还没有任何学生");
    }else{
        for (int i = 0; i < number; i++)
        {
            if (strcmp(name,students[i].name)==0)
            {
                printf("找到学生信息：\n");
                printf("姓名：%s\n", students[i].name);
                printf("学号：%d\n", students[i].id);
                printf("班级：%d\n", students[i].class_num);
                printf("课程成绩：%.2f %.2f %.2f\n",
                    students[i].score[0], students[i].score[1], students[i].score[2]); 
                found=1;
                
                
            }
            
        }
        if (found==0)
        {
            printf("没有找到此学生\n");
        }
        
    }
    
}

void findLsscore(int class_num){
    if (number==0)
    {
       printf("目前还没有任何学生"); 
    }else{
        float *score =(float *)malloc(sizeof(float)*number);
        for (int i = 0; i < number; i++)
        {
            score[i]=students[i].score[class_num];
        }
        int min=sortArrMin(score);

        printf("找到科目%d的成绩最低的学生信息：\n",class_num);
        printf("姓名：%s\n", students[min].name);
        printf("学号：%d\n", students[min].id);
        printf("班级：%d\n", students[min].class_num);
        free(score);

    }
    

}

void findHIscore(int class_num){
    if (number==0)
    {
       printf("目前还没有任何学生"); 
    }else{
        float *score =(float *)malloc(sizeof(float)*number);
        for (int i = 0; i < number; i++)
        {
            score[i]=students[i].score[class_num];
        }
        int min=sortArrMax(score);

        printf("找到科目%d的成绩最高的学生信息：\n",class_num);
        printf("姓名：%s\n", students[min].name);
        printf("学号：%d\n", students[min].id);
        printf("班级：%d\n", students[min].class_num);
        free(score);

    }
    

}

void findByAve(int n){
    if (number==0)
    {
       printf("目前还没有任何学生");  
    }else{
        float *Avescore =(float *)malloc(sizeof(float)*number);
        for (int i = 0; i < number; i++)
        {
            Avescore[i]=(students[i].score[0]+students[i].score[1]+students[i].score[2])/3.0 ;
        }
        if (n=1)//1是找最高，2是找最低
        {
            int max=sortArrMax(Avescore);
            printf("找到平均的成绩最高的学生信息：\n");
            printf("姓名：%s\n", students[max].name);
            printf("学号：%d\n", students[max].id);
            printf("班级：%d\n", students[max].class_num);
                       
        }
        if (n=2)//1是找最高，2是找最低
        {
            int max=sortArrMin(Avescore);
            printf("找到平均的成绩最低的学生信息：\n");
            printf("姓名：%s\n", students[max].name);
            printf("学号：%d\n", students[max].id);
            printf("班级：%d\n", students[max].class_num);
                       
        }
        free(Avescore);

    }
    
}

void delByid(int id){
    if (number == 0) {
        printf("暂无学生信息。\n");
        return;
    }


    int found = 0;
    int index = 0;
    
    for (int i = 0; i < number; i++) {
        if (students[i].id == id) {
            printf("找到以下学生信息，是否确认删除？\n");
            printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "姓名", "学号", "班级", "课程1", "课程2", "课程3");
            printf("%-10s %-10d %-10d %-10.2f %-10.2f %-10.2f\n", students[i].name, students[i].id,
                   students[i].class_num, students[i].score[0], students[i].score[1], students[i].score[2]);
            found = 1;
            index = i;
            break;
        }
    }

    if (!found) {
        printf("未找到学号为%d的学生。\n", id);
        return;
    }

    char confirmation;
    printf("确认删除该学生信息？(y/n): ");
    scanf(" %c", &confirmation);

    if (confirmation == 'y' || confirmation == 'Y') {
        // 删除学生信息
        for (int i = index; i < number - 1; i++) {
            students[i] = students[i + 1];
        }
        number--;

        printf("学生信息删除成功！\n");
    } else {
        printf("学生信息未被删除。\n");
    }
}    

    
void delByName(char *name){
    int found=0;
    int index=0;
    if (number == 0)
    {
        printf("暂无学生信息。\n");
    }else{
        for (int i = 0; i < number; i++)
        {
            if (strcmp(name,students[i].name)==0)
            {
                
                printf("找到以下学生信息，是否确认删除？\n");
                printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "姓名", "学号", "班级", "课程1", "课程2", "课程3");
                printf("%-10s %-10d %-10d %-10.2f %-10.2f %-10.2f\n", students[i].name, students[i].id,
                    students[i].class_num, students[i].score[0], students[i].score[1], students[i].score[2]);
                found = 1;
                index = i;
                break;
                
            }
        }   
    }
    if (!found) {
        printf("未找到姓名为%s的学生。\n", name);
        return;
    }

    char confirmation;
    printf("确认删除该学生信息？(y/n): ");
    scanf(" %c", &confirmation);

    if (confirmation == 'y' || confirmation == 'Y') {
        // 删除学生信息
        for (int i = index; i < number - 1; i++) {
            students[i] = students[i + 1];
        }
        number--;

        printf("学生信息删除成功！\n");
    } else {
        printf("学生信息未被删除。\n");
    }    

}


void insert() {
    if (number == 0) {
        printf("暂无任何学生学号，无法插入。\n");
    } else {
        int *ids = (int *)malloc(sizeof(int) * number);
        for (int i = 0; i < number; i++) {
            ids[i] = students[i].id;
        }

        bubble_sort(ids, number);

        int newid = ids[0] + 1;
        if (number == 100) {
            printf("学生已满，请删除部分再试");
        } else {
            number++;
            printf("请输入学生姓名：\n");
            scanf("%s", students[number - 1].name);
            students[number - 1].id = newid;
            printf("请输入学生班级：\n");
            scanf("%d", &students[number - 1].class_num);
            for (int i = 0; i < 3; i++) {
                printf("请输入学生%d课程成绩：\n", i + 1);
                scanf("%f", &students[number - 1].score[i]);
            }

            printf("插入成功！\n");
            printf("您插入的学生信息为\n");
            printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "姓名", "学号", "班级", "课程1", "课程2", "课程3");
            printf("%-10s %-10d %-10d %-10.2f %-10.2f %-10.2f\n", students[number - 1].name, students[number - 1].id,
                   students[number - 1].class_num, students[number - 1].score[0], students[number - 1].score[1], students[number - 1].score[2]);
            free(ids);
        }
    }
}

void allAve(){
    if (number == 0) {
        printf("暂无学生信息。\n");
    }else{
        float *ave=(float *)malloc(sizeof(float)*number);
        for (int i = 0; i < number; i++)
        {
            ave[i]=students[i].score[0]+students[i].score[1]+students[i].score[2];
        }
        for (int i = 0; i < number; i++)
        {
            printf("%-10s %-10d %-10d %-10.2f\n",students[i].name,students[i].id,students[i].class_num,ave[i]/3.0);
        }
        free(ave);
    
    }
    
        
}

void allsum() {

    if (number == 0) {
        printf("暂无学生信息。\n");
    } else {
        int *sum = (int *)malloc(sizeof(int) * number);
        for (int i = 0; i < number; i++) {
            sum[i] = students[i].score[0] + students[i].score[1] + students[i].score[2];
        }
        for (int i = 0; i < number; i++) {
            printf("%-10s %-10d %-10d %-10d\n", students[i].name, students[i].id, students[i].class_num, sum[i]);
        }
        free(sum);
    }
}


void aveByclass_num(int class_num) {
    int found=0;
    if (number==0)
    {
        printf("暂无学生信息。\n");
    }else{
        for (int i = 0; i < number; i++)
        {
            if (students[i].class_num==class_num)
            {
                printf("%-10s %-10d %-10d %-10.2f\n",students[i].name,students[i].id,students[i].class_num,students[i].score[0]+students[i].score[1]+students[i].score[2]/3.0);
            }
        }
        if (!found) {
            printf("未找到班级为%d的学生。\n", class_num);
            
        }
 
    }
    
    
}

void displayBySumscore() {
    if (number == 0) {
        printf("暂无学生信息。\n");
    }else{
        int *sum=(int *)malloc(sizeof(int)*number);
        for (int i = 0; i < number; i++)
        {
            sum[i]=students[i].score[0]+students[i].score[1]+students[i].score[2];
        }
        int *sumIdx=(int *)malloc(sizeof(int)*number);
        for (int i = 0; i < number; i++)
        {
            sumIdx[i]=i;
        }
        int temp=0;
        //假定一个索引数列和总分数序列，在对分数数列排序的时候同时对索引数列进行排序
        for (int i = 0; i < number; i++)
        {
          
            for (int j = 0; j < number-1-i; j++ )
            {
                if (sum[j]>sum[j+1])
                {
                    temp=sum[j];
                    sum[j]=sum[j+1];
                    sum[j+1]=temp;
                    temp=sumIdx[j];
                    sumIdx[j]=sumIdx[j+1];
                    sumIdx[j+1]=temp;
                }
                
                
            }
              
        }

        printf("按总分排序的学生信息为\n");
        for (int i = 0; i < number; i++)
        {
            printf("%-10s %-10d %-10d %-10d\n",students[sumIdx[i]].name,students[sumIdx[i]].id,students[sumIdx[i]].class_num,sum[i]);
        }
        free(sum);
        free(sumIdx);
    }    
}

int main() {
    SetConsoleOutputCP(65001);
    printf("****************************************\n");
    printf("Made By 陈薏帆 网安233 202301050854\n");
    printf("****************************************\n");

    printf("欢迎使用学生信息管理系统\n");
    while (1) {
        printf("请选择操作：\n");
        printf("1.添加学生信息\n");
        printf("2.显示学生信息\n");
        printf("3.查找学生信息\n");
        printf("4.插入学生信息\n");
        printf("5.删除学生信息\n");
        printf("6.成绩计算\n");
        printf("7.按总分降序输出\n");
        printf("0.退出\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                printf("请选择查询的方式\n");
                printf("1.按姓名查询\n");
                printf("2.按学号查询\n");
                printf("3.查询某门课的最高成绩的学生\n");
                printf("4.查询某门课的最低成绩的学生\n");
                printf("5.查询某门课的平均成绩最高或最低的学生\n");
                int choice2;
                scanf("%d", &choice2);
                switch (choice2) {
                    case 1:
                        char name[20];
                        printf("请输入学生姓名：\n");
                        scanf("%s", name);
                        findByname(name);
                        break;
                    case 2:
                        int id;
                        printf("请输入学生学号：\n");
                        scanf("%d", &id);
                        findByid(id);
                        break;
                    case 3:
                        int class_num;
                        printf("请输入课程序号：\n");
                        scanf("%d",&class_num);
                        findHIscore(class_num);
                        break;
                    case 4:
                        int class_num2;
                        printf("请输入课程序号：\n");
                        scanf("%d", &class_num2);
                        findLsscore(class_num2);
                        break;
                    case 5:
                        int class_num3;
                        printf("查询最高的学生或最低的学生：\n");
                        printf("1.查询最高的学生\n");
                        printf("2.查询最低的学生\n");
                        scanf("%d", &class_num3);
                        findByAve(class_num3);
                        break;
                    default:
                        printf("输入错误，请重新输入。\n");
                        break;
                }
                break;
            case 4:
                insert();
                break;
            case 5:
                printf("请选择删除的方式\n");
                printf("1.按姓名删除\n");
                printf("2.按学号删除\n");
                int choice3;
                scanf("%d", &choice3);
                switch (choice3) {
                    case 1:
                        char name2[20];
                        printf("请输入学生姓名：\n");
                        scanf("%s", name2);
                        delByName(name2);
                        break;
                    case 2:
                        int id2=0;
                        printf("请输入学生学号：\n");
                        scanf("%d", &id2);
                        delByid(id2);
                        break;
                    }          
                break;
            case 6:
                printf("请选择计算的方式\n");
                printf("1.计算平均成绩\n");
                printf("2.计算总分\n");
                printf("3.班级最高分\n");
                int choice4;
                scanf("%d", &choice4);
                switch (choice4) {
                    case 1:
                        allAve();
                        break;
                    case 2:
                        allsum();
                        break;
                    case 3:
                        int class_num2;
                        printf("请输入班级：\n");
                        scanf("%d", &class_num2);
                        aveByclass_num(class_num2);
                        break;
                    default:
                        printf("输入错误，请重新输入。\n");
                        break;
                }
                break;
            case 7:
                displayBySumscore();
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("输入错误，请重新输入。\n");
                break;
        }
    }
}








