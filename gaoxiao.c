#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<string.h>

struct student {
    char name[20];
    int id;
    char college[20];
    int classNum;
    char gender;
    char password[20];
};
typedef struct student student;
student stu[100];

struct teacher{
    char name[20];
    int id;
    char gender;
    char college[20];
    char className1[20];
    char className2[20];
    char className3[20];
    float Allscore;
};
typedef struct teacher teacher;
teacher tea[100];

struct info
{
    int teacherId;
    char teacherName[20];
    char college[20];
    char className[20];
    int pjNum;
    float SumScore;
    float FinalScore;
};
typedef struct info in;
in info[100];

int teacherNum=0;
int studentNum=0;
int infoNum=0;

void newTeacherFile(){
    //循环输入老师信息
    printf("请输入老师信息\n");
    printf("教师编号输入0结束输入\n");
    int i=0;
    while (1)
    {
        printf("输入教师编号: \n");
        scanf("%d",&tea[i].id);
        if(tea[i].id==0){
            break;
        }
        printf("输入教师名称: \n");
        scanf("%s",tea[i].name);
        printf("输入教师性别(M/F): \n");
        scanf(" %c",&tea[i].gender);
        printf("输入教师所在学院: \n");
        scanf("%s",tea[i].college);
        printf("输入教师课程1: \n");
        scanf("%s",tea[i].className1);
        printf("输入教师课程2: \n");
        scanf("%s",tea[i].className2);
        printf("输入教师课程3: \n");
        scanf("%s",tea[i].className3);
        //初始化教师评教成绩
        tea[i].Allscore=0;
        printf("这是您添加的教师信息\n");
        //打印这次添加的教师信息放在一行
        printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
        i++;

    }
    
    //按照教师编码进行排序
    for(int j=0;j<i;j++){
        for(int k=j;k<i;k++){
            if(tea[j].id>tea[k].id){
                teacher temp;
                temp=tea[j];
                tea[j]=tea[k];
                tea[k]=temp;
            }
        }
    }

    //将新建的教师信息写入文件
    FILE *fp;
    fp=fopen("teacher.dat","wb");
    if(fp==NULL){
        printf("教师文件打开失败\n");
        return;
    }else{
        for(int j=0;j<i;j++){
            fwrite(&tea[j],sizeof(teacher),1,fp);
        }
        fclose(fp);
    }
    printf("教师信息写入成功\n");
    //更新教师数量
    teacherNum=i;

}

void addTeacher(){
    if(teacherNum==0){
        printf("没有老师信息\n");
        return;
    }
    //添加教师信息
    printf("请输入要添加的教师信息\n");
    printf("请输入教师名称\n");
    scanf("%s",tea[teacherNum].name);
    printf("请输入教师编号\n");
    
    //检测编号，如果重复，则再次输入直到不重复
    int found=0;
    while(1){
        found=0;
        scanf("%d",&tea[teacherNum].id);
        for(int k=0;k<teacherNum;k++){
            if(tea[k].id==tea[teacherNum].id){
                printf("输入的教师编号重复，请重新输入\n");
                found=1;
                break;
            }
        }
        if(found==0){
            break;
        }

    }   
    printf("请输入教师性别(M/F)\n");
    scanf(" %c",tea[teacherNum].gender);
    getchar();
    printf("请输入教师所在学院\n");
    scanf("%s",tea[teacherNum].college);
    printf("请输入教师课程1\n");
    scanf("%s",tea[teacherNum].className1);
    printf("请输入教师课程2\n");
    scanf("%s",tea[teacherNum].className2);
    printf("请输入教师课程3\n");
    scanf("%s",tea[teacherNum].className3);
    printf("这是您添加的教师信息\n");
    printf("%d %s %c %s %s %s %s \n",tea[teacherNum].id,tea[teacherNum].name,tea[teacherNum].gender,tea[teacherNum].college,tea[teacherNum].className1,tea[teacherNum].className2,tea[teacherNum].className3);

    //更新教师数量
    teacherNum++;
    //排序
    for(int j=0;j<teacherNum;j++){
        for(int k=j;k<teacherNum;k++){
            if(tea[j].id>tea[k].id){
                teacher temp;
                temp=tea[j];
                tea[j]=tea[k];
                tea[k]=temp;
            }
        }
    }
    //写入文件
    FILE *fp;
    fp=fopen("teacher.dat","ab");
    if(fp==NULL){
        printf("教师文件打开失败\n");
        return;
    }else{
        fwrite(&tea[teacherNum-1],sizeof(teacher),1,fp);
        fclose(fp);
    }
    

}

void DelTeacher(){
    if(teacherNum==0){
        printf("没有老师信息\n");
        return;
    }
    char name[20];
    printf("请输入要删除的教师姓名\n");
    scanf("%s",name);
    for(int i=0;i<teacherNum;i++){
        if(strcmp(tea[i].name,name)==0){
            //打印信息，并确认是否删除
            printf("您要删除的教师信息如下\n");
            printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
            printf("是否删除(Y/N)\n");
            char ch;
            scanf(" %c",&ch);
            if(ch=='Y'){
                //删除
                teacher temp;
                temp=tea[i];
                for(int j=i;j<teacherNum-1;j++){
                    tea[j]=tea[j+1];
                }
                teacherNum--;
                tea[teacherNum]=temp;
                printf("删除成功!\n");
                break;
            }else{
                printf("取消删除\n");
                break;
            }
        }
    }
    //更新数据到文件
    FILE* fp;
    fp=fopen("teacher.dat","wb");
    if(fp==NULL){
        printf("教师文件打开失败\n");
        return;
        
    }else{
        for(int i=0;i<teacherNum;i++){
            fwrite(&tea[i],sizeof(teacher),1,fp);
        }
        fclose(fp);
    }

}

void modifyTeacher(){
    char name[20];
    printf("请输入要修改的教师姓名\n");
    scanf("%s",name);
    int found=0;
    for(int i=0;i<teacherNum;i++){
        if(strcmp(tea[i].name,name)==0){
            //打印信息，并确认是否修改
            printf("您要修改的教师信息如下\n");
            printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
            char choice;
            //选择修改的地方
            printf("1.修改性别\n");
            printf("2.修改所在学院\n");
            printf("3.修改课程1名称\n");
            printf("4.修改课程2名称\n");
            printf("5.修改课程3名称\n");
            printf("请输入修改的选项\n");
            getchar();
            scanf("%c",&choice);
            switch(choice){
                case '1':
                    printf("请输入修改后的性别\n");
                    getchar();
                    scanf("%c",&tea[i].gender);
                    break;
                case '2':
                    printf("请输入修改后的所在学院\n");
                    scanf("%s",tea[i].college);
                    break;
                case '3':
                    printf("请输入修改后的课程1名称\n");
                    scanf("%s",tea[i].className1);
                    break;
                case '4':
                    printf("请输入修改后的课程2名称\n");
                    scanf("%s",tea[i].className2);
                    break;
                case '5':
                    printf("请输入修改后的课程3名称\n");
                    scanf("%s",tea[i].className3);
                    break;
                default:
                    printf("输入错误\n");
                    break;
            }
            printf("修改后的教师信息如下\n");
            printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
            found=1;
            break;
        }
    }
    if(found==0){
        printf("没有找到此老师!\n");
    }

    //写入文件
    FILE *fp;
    fp=fopen("teacher.dat","ab");
    if(fp==NULL){
        printf("教师文件打开失败\n");
        return;
    }else{
        fwrite(&tea[teacherNum-1],sizeof(teacher),1,fp);
        fclose(fp);
    }
}


void newStudentFile(){
    //循环新建学生信息，学号为0时退出
    int i=0;
    while(1){
        printf("新建学生信息开始,学号输入0结束\n");
        printf("请输入学号: \n");
        scanf("%d",&stu[i].id);
        if(stu[i].id==0){
            break;
        }
        printf("请输入学生姓名: \n");
        scanf("%s",stu[i].name);
        printf("请输入学生性别(M/F): \n");
        scanf(" %c",&stu[i].gender);
        printf("请输入学生所在学院: \n");
        scanf("%s",stu[i].college);
        printf("请输入学生班级号: \n");
        scanf("%d",&stu[i].classNum);
        printf("请输入学生密码:\n");
        scanf("%s",stu[i].password);
        printf("这是您新建的学生信息\n");
        printf("%d %s %c %s %d %s \n",stu[i].id,stu[i].name,stu[i].gender,stu[i].college,stu[i].classNum,stu[i].password);
    
        i++;

    }

    studentNum=i;
    //写入文件
    FILE *fp;
    fp=fopen("student.dat","w");
    if(fp==NULL){
        printf("学生文件打开失败\n");
        return;
    }else{
        fwrite(&stu[studentNum-1],sizeof(student),1,fp);
        fclose(fp);
    }
    


}

void CreatFile(){
    FILE *fp;

    //检测是否有文件
    if(fopen("student.dat","r")!=NULL){
        printf("学生文件已存在\n");
        
    }else{
        fp=fopen("student.dat","wb");
        if(fp==NULL){
            printf("学生文件创建失败\n");
            
        }else{
            printf("学生文件创建成功\n");
            newStudentFile();
            fclose(fp);
        }
    }

    if (fopen("teacher.dat","r")!=NULL)
    {
        printf("老师文件已存在\n");
        
    }else{
        fp=fopen("teacher.dat","wb");
        if(fp==NULL){
            printf("老师文件创建失败\n");
            
        }else{
            printf("老师文件创建成功\n");
            newTeacherFile();
            fclose(fp);
        }
    }
    
    if (fopen("info.dat","r")!=NULL)
    {
        printf("信息文件已存在\n");
        
    }else{
        fp=fopen("info.dat","wb");
        if(fp==NULL){
            printf("信息文件创建失败\n");
            
        }else{
            printf("信息文件创建成功\n");
            fclose(fp);
        }
    }



}
void  Judge(){
    //首先按姓名查询教师
    //两种模式，精确查找和模糊查找
    printf("1.精确查找\n2.模糊查找");
    int choice;
    scanf("%d",&choice);
    
    if (choice == 1)
    {
        //精确查找
        printf("请输入教师的名称:\n");
        char name[20];
        scanf("%s",name);
        int found=0;
        int found2=0;
        for(int i=0;i<teacherNum;i++){
            if(strcmp(tea[i].name,name)==0){
                found2=1;
                printf("您输入的教师信息如下\n");
                printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
                
                
                //第一个科目
                //循环info数组，查找是否已经存在学生对此老师的此科目的评价
                for(int j=0;j<infoNum;j++){
                    if(info[i].teacherId == tea[i].id && strcmp(info[i].className, tea[i].className1) == 0){
                        printf("请输入对%s科目的分数 \n",tea[i].className1);
                        float score=0;
                        scanf("%f",&score);
                        info[j].SumScore += score;
                        info[j].pjNum++;
                        info[j].FinalScore = info[j].SumScore / info[j].pjNum;
                        found=1;
                        break;
                    }
                }
                //没有找到，则创建新的记录
                if (found==0)
                {
                    info[infoNum].teacherId = tea[i].id;
                    strcpy(info[infoNum].className, tea[i].className1);
                    strcpy(info[infoNum].teacherName, tea[i].name);
                    strcpy(info[infoNum].college, tea[i].college);
                    info[infoNum].pjNum = 1;
                    printf("请输入对%s科目的分数 \n",tea[i].className1);
                    float score=0;
                    scanf("%f",&score);
                    info[infoNum].SumScore = score;
                    info[infoNum].FinalScore = info[infoNum].SumScore / info[infoNum].pjNum;
                    infoNum++;
                }



                //第二个科目
                //循环info数组，查找是否已经存在学生对此老师的此科目的评价
                found=0;
                for(int j=0;j<infoNum;j++){
                    if(info[i].teacherId == tea[i].id && strcmp(info[i].className, tea[i].className2) == 0){
                        printf("请输入对%s科目的分数 \n",tea[i].className2);
                        float score=0;
                        scanf("%f",&score);
                        info[j].SumScore += score;
                        info[j].pjNum++;
                        info[j].FinalScore = info[j].SumScore / info[j].pjNum;
                        found=1;
                        break;
                    }
                }
                //没有找到，则创建新的记录
                if (found==0)
                {
                    info[infoNum].teacherId = tea[i].id;
                    strcpy(info[infoNum].className, tea[i].className2);
                    strcpy(info[infoNum].teacherName, tea[i].name);
                    strcpy(info[infoNum].college, tea[i].college);
                    info[infoNum].pjNum = 1;
                    printf("请输入对%s科目的分数 \n",tea[i].className2);
                    float score=0;
                    scanf("%f",&score);
                    info[infoNum].SumScore = score;
                    info[infoNum].FinalScore = info[infoNum].SumScore / info[infoNum].pjNum;
                    infoNum++;
                }
                

                found=0;
                //第三个科目
                //循环info数组，查找是否已经存在学生对此老师的此科目的评价
                for(int j=0;j<infoNum;j++){
                    if(info[i].teacherId == tea[i].id && strcmp(info[i].className, tea[i].className3) == 0){
                        printf("请输入对%s科目的分数 \n",tea[i].className3);
                        float score=0;
                        scanf("%f",&score);
                        info[j].SumScore += score;
                        info[j].pjNum++;
                        info[j].FinalScore = info[j].SumScore / info[j].pjNum;
                        found=1;
                        break;
                    }
                }
                //没有找到，则创建新的记录
                if (found==0)
                {
                    info[infoNum].teacherId = tea[i].id;
                    strcpy(info[infoNum].className, tea[i].className3);
                    strcpy(info[infoNum].teacherName, tea[i].name);
                    strcpy(info[infoNum].college, tea[i].college);
                    info[infoNum].pjNum = 1;
                    printf("请输入对%s科目的分数 \n",tea[i].className3);
                    float score=0;
                    scanf("%f",&score);
                    info[infoNum].SumScore = score;
                    info[infoNum].FinalScore = info[infoNum].SumScore / info[infoNum].pjNum;
                    infoNum++;
                }

                //循环info数组，找出此老师的三个科目的FinallScore取平均值给teacher的allscore
                float allscore=0;
                for(int k=0 ;k<infoNum;k++){
                    if(strcmp(info[k].teacherName,tea[i].name)==0){
                        allscore+=info[k].FinalScore;
                    }

                }
                tea[i].Allscore=allscore/3.0;
                break;

            }
        }
        if (found2==0)
        {
            printf("没有找到该老师\n");
        }
        

        
    }
    else if (choice == 2)//模糊查询
    {
        printf("进行模糊查询\n");
        printf("请输入教师的部分名字\n");
        char name[20];
        scanf("%s",name);
        for(int i=0;i<teacherNum;i++){
            if(strstr(tea[i].name,name)!=NULL){
                printf("您输入的教师信息如下\n");
                //输出教师信息
                printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
            }
        }
        printf("请输入你要评教的老师的完整姓名：\n");
        char name2[20];
        scanf("%s",name2);
        int found=0;
        for(int i=0;i<teacherNum;i++){
            if(strcmp(tea[i].name,name2)==0){
                printf("您输入的教师信息如下\n");
                //输出教师信息
                printf("%d %s %c %s %s %s %s \n",tea[i].id,tea[i].name,tea[i].gender,tea[i].college,tea[i].className1,tea[i].className2,tea[i].className3);
                                

                //第一个科目
                //循环info数组，查找是否已经存在学生对此老师的此科目的评价
                for(int j=0;j<infoNum;j++){
                    if(info[i].teacherId == tea[i].id && strcmp(info[i].className, tea[i].className1) == 0){
                        printf("请输入对%s科目的分数 \n",tea[i].className1);
                        float score=0;
                        scanf("%f",&score);
                        info[j].SumScore += score;
                        info[j].pjNum++;
                        info[j].FinalScore = info[j].SumScore / info[j].pjNum;
                        found=1;
                        break;
                    }
                }
                //没有找到，则创建新的记录
                if (found==0)
                {
                    info[infoNum].teacherId = tea[i].id;
                    strcpy(info[infoNum].className, tea[i].className1);
                    strcpy(info[infoNum].teacherName, tea[i].name);
                    strcpy(info[infoNum].college, tea[i].college);
                    info[infoNum].pjNum = 1;
                    printf("请输入对%s科目的分数 \n",tea[i].className1);
                    float score=0;
                    scanf("%f",&score);
                    info[infoNum].SumScore = score;
                    info[infoNum].FinalScore = info[infoNum].SumScore / info[infoNum].pjNum;
                    infoNum++;
                }



                //第二个科目
                //循环info数组，查找是否已经存在学生对此老师的此科目的评价
                found=0;
                for(int j=0;j<infoNum;j++){
                    if(info[i].teacherId == tea[i].id && strcmp(info[i].className, tea[i].className2) == 0){
                        printf("请输入对%s科目的分数 \n",tea[i].className2);
                        float score=0;
                        scanf("%f",&score);
                        info[j].SumScore += score;
                        info[j].pjNum++;
                        info[j].FinalScore = info[j].SumScore / info[j].pjNum;
                        found=1;
                        break;
                    }
                }
                //没有找到，则创建新的记录
                if (found==0)
                {
                    info[infoNum].teacherId = tea[i].id;
                    strcpy(info[infoNum].className, tea[i].className2);
                    strcpy(info[infoNum].teacherName, tea[i].name);
                    strcpy(info[infoNum].college, tea[i].college);
                    info[infoNum].pjNum = 1;
                    printf("请输入对%s科目的分数 \n",tea[i].className2);
                    float score=0;
                    scanf("%f",&score);
                    info[infoNum].SumScore = score;
                    info[infoNum].FinalScore = info[infoNum].SumScore / info[infoNum].pjNum;
                    infoNum++;
                }
                


                //第三个科目
                //循环info数组，查找是否已经存在学生对此老师的此科目的评价
                found=0;
                for(int j=0;j<infoNum;j++){
                    if(info[i].teacherId == tea[i].id && strcmp(info[i].className, tea[i].className3) == 0){
                        printf("请输入对%s科目的分数 \n",tea[i].className3);
                        float score=0;
                        scanf("%f",&score);
                        info[j].SumScore += score;
                        info[j].pjNum++;
                        info[j].FinalScore = info[j].SumScore / info[j].pjNum;
                        found=1;
                        break;
                    }
                }
                //没有找到，则创建新的记录
                if (found==0)
                {
                    info[infoNum].teacherId = tea[i].id;
                    strcpy(info[infoNum].className, tea[i].className3);
                    strcpy(info[infoNum].teacherName, tea[i].name);
                    strcpy(info[infoNum].college, tea[i].college);
                    info[infoNum].pjNum = 1;
                    printf("请输入对%s科目的分数 \n",tea[i].className3);
                    float score=0;
                    scanf("%f",&score);
                    info[infoNum].SumScore = score;
                    info[infoNum].FinalScore = info[infoNum].SumScore / info[infoNum].pjNum;
                    infoNum++;
                }
                //循环info数组，找出此老师的三个科目的FinallScore取平均值给teacher的allscore
                float allscore=0;
                for(int k=0 ;k<infoNum;k++){
                    if(strcmp(info[k].teacherName,tea[i].name)==0){
                        allscore+=info[k].FinalScore;
                    }

                }
                tea[i].Allscore=allscore/3.0;



                break;
            }
        }
        if(found==0){
            printf("没有此老师\n");
        }

    }
    
    //更新info数组到文件
    FILE *fp;
    fp=fopen("info.dat","wb");
    fwrite(info,sizeof(info[0]),infoNum,fp);
    fclose(fp);
    //更新teacher数组到文件
    fp=fopen("teacher.dat","wb");
    fwrite(tea,sizeof(tea[0]),teacherNum,fp);
    fclose(fp);

    return ;

}

int login(){
    //输入学号和密码，循环学生数组，找出此学号的密码是否正确，如果正确返回1，错误返回2
    int id;
    char password[20];
    printf("请输入学号：");
    scanf("%d",&id);
    printf("请输入密码：");
    scanf("%s",password);
    int found=0;
    for(int i=0;i<studentNum;i++){
        if(id==stu[i].id && strcmp(password,stu[i].password)==0){
            found=1;
            return 1;
        }
    }
    if (found==0)
    {
        return 2;
    }

}
void read2Arr(){
//从文件中读取学生和教师数组到内存
    FILE *fp;
    fp=fopen("student.dat","rb");
    fread(stu,sizeof(stu[0]),studentNum,fp);
    fclose(fp);
    fp=fopen("teacher.dat","rb");
    fread(tea,sizeof(tea[0]),teacherNum,fp);
    fclose(fp);
    fp=fopen("info.dat","rb");
    fread(info,sizeof(info[0]),infoNum,fp);
    fclose(fp);

}
void upadteNum(){

    //更新学生和教师数组的长度
    FILE *fp;
    fp = fopen("teacher.dat","rb");
    if (fp == NULL)
    {
        printf("更新教师打开文件失败！\n");
    }
    //计算条数
    fseek(fp,0,SEEK_END);
    teacherNum = ftell(fp)/sizeof(tea[0]);
    fclose(fp);
    fp = fopen("student.dat","rb");
    if (fp == NULL)
    {
        printf("更新学生打开文件失败！\n");
    }
    //计算条数
    fseek(fp,0,SEEK_END);
    studentNum = ftell(fp)/sizeof(stu[0]);
    fclose(fp);
    fp = fopen("info.dat","rb");
    if (fp == NULL)
    {
        printf("更新info打开文件失败！\n");
    }
    //计算条数
    fseek(fp,0,SEEK_END);
    infoNum = ftell(fp)/sizeof(info[0]);
    fclose(fp);
}

void FindbyName(){
    //根据教师查询教师的评教得分
    char name[20];
    printf("请输入教师姓名：");
    scanf("%s",name);
    int found=0;
    for(int i=0;i<teacherNum;i++){
        if(strcmp(name,tea[i].name)==0){
            printf("教师姓名：%s\n",tea[i].name);
            printf("教师编号：%d\n",tea[i].id);
            printf("教师得分: %.2f\n",tea[i].Allscore);
            found=1;
            break;
        }
    }
    if (found==0)
    {
        printf("没有找到此老师\n");
    }

}

void findBycollege(){
    //输入学院名称，对该学院的老师的评教成绩从高到低进行排序，保存到新数组里
    printf("请输入学院名称\n");
    char college[20];
    scanf("%s",college);
    //从tea数组中统计某学院的教师数量
    int count=0;
    for(int i=0;i<teacherNum;i++){
        if(strcmp(college,tea[i].college)==0){
            count++;
        }
    }
    //malloc申请内存
    teacher *newtea=(teacher*)malloc(sizeof(teacher)*count);
    //将该学院的教师信息复制到新数组里
    for(int i=0,j=0;i<teacherNum;i++){
        if(strcmp(college,tea[i].college)==0){
            newtea[j]=tea[i];
            j++;
        }
    }
    //对新数组进行排序
    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            if(newtea[i].Allscore<newtea[j].Allscore){
                teacher temp=newtea[i];
                newtea[i]=newtea[j];
                newtea[j]=temp;
            }
        }
    }
    for(int i=0;i<count;i++){
        printf("教师姓名：%s\n",newtea[i].name);
        printf("教师编号：%d\n",newtea[i].id);
        printf("教师得分: %.2f\n",newtea[i].Allscore);
    }
    //保存到文件中
    FILE *fp;
    fp=fopen("Sortedteacher.dat","wb");
    fwrite(newtea,sizeof(newtea[0]),count,fp);
    fclose(fp);
    free(newtea);
    printf("已保存到文件中\n");
    return;
}

void sortByphase(){
    //按照分数段统计人数
    //90~100分段
    int count=0;
    for(int i=0;i<teacherNum;i++){
        if(tea[i].Allscore>=90 && tea[i].Allscore<=100){
            count++;
        }
    }
    printf("90~100分段人数：%d\n",count);
    count=0;
    for(int i=0;i<teacherNum;i++){
        if(tea[i].Allscore>=80 && tea[i].Allscore<90){
            count++;
        }
    }
    printf("80~89分段人数：%d\n",count);
    count=0;
    for(int i=0;i<teacherNum;i++){
        if(tea[i].Allscore>=70 && tea[i].Allscore<80){
            count++;
        }
    }
    printf("70~79分段人数：%d\n",count);
    count=0;
    for(int i=0;i<teacherNum;i++){
        if(tea[i].Allscore>=0 && tea[i].Allscore<69){
            count++;
        }
    }
    printf("0~69分段人数：%d\n",count);

    

}

void sortBycollege(){
    //输入课程名称
    printf("请输入课程名称\n");
    char course[20];
    scanf("%s",course);
    //输出该课程的教师的所有评教得分
    //查找classname1
    for(int i=0;i<teacherNum;i++){
        if(strcmp(course,tea[i].className1)==0 || strcmp(course,tea[i].className2)==0 || strcmp(course,tea[i].className3)==0){
            printf("教师姓名：%s\n",tea[i].name);
            printf("教师编号：%d\n",tea[i].id);
            printf("教师得分：%.2f\n",tea[i].Allscore);
            
        }
    }

}

int main(){

    //预处理
    SetConsoleOutputCP(65001);
    CreatFile();
    upadteNum();
    read2Arr();

    printf("欢迎使用评教系统!\n");
    while(1){
        printf("1.添加教师信息\n");
        printf("2.删除教师信息\n");
        printf("3.修改教师信息\n");
        printf("************************\n");
        printf("4.开始评教\n");
        printf("************************\n");
        printf("5.根据教师姓名查询教师信息\n");
        printf("6.根据学院查询教师信息\n");
        printf("7.根据课程查询教师信息\n");
        printf("8.按分数段统计人数\n");

        printf("0.退出\n"); 

        int choice;
        int is_login;
        scanf("%d",&choice);
        switch(choice){
            case 1:
            addTeacher();
            break;
            case 2:
            DelTeacher();
            break;
            case 3:
            modifyTeacher();
            break;
            case 4:
            while (1)
            {
                is_login=login();
                if (is_login==1)
                {
                    break;
                }
                
                if (is_login==2)
                {
                    printf("学号或密码错误，请重新输入！\n");
                }
            }
            if (is_login==1)
            {
                    printf("登陆成功!\n");
                    printf("开始评教\n");
                    Judge();
                    printf("评价完成！\n");
                    break;
            }
            case 5:
            FindbyName();
            break;
            case 6:
            findBycollege();
            break;
            case 7:
            sortBycollege();
            break;
            case 8:
            sortByphase();
            break;
            case 0:
            exit(0);
            break;
            default:
            printf("输入错误，请重新输入！\n");
            
        }




    }
    system("pause");



}