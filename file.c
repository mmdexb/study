#include<stdlib.h>
#include<stdio.h>

typedef struct student
{
    int id;
    char name[20];
    int s;
}STU;

STU stu[3];

int main(){
    FILE *fp;
    int i;
    if((fp=fopen("student.dat","wb"))==NULL){
        printf("error");
        exit(1);
    }
    for (int i = 0; i < 3; i++)
    {
        scanf("%d%s%d",&stu[i].id,stu[i].name,&stu[i].s);
    }
    fwrite(stu,sizeof(STU),3,fp);
    fclose(fp);
    system("pause");
    return 0;
    
    

    
    
    
    
}