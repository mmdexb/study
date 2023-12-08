#include <stdlib.h>
#include<stdio.h>

int main(){
    FILE* fp=NULL;
    fp=fopen("file1.txt","r");
    char ch;
    int n=0;
    printf("this is file1.txt:\n");
    while ((ch=fgetc(fp))!=EOF)
    {
        
        printf("%c",ch);
        n++;
    }
    printf("\n");
    rewind(fp);
    char str[50];
    fgets(str,n+1,fp);
    printf("enter new file1.txt\n%s",str);


    fclose(fp);

    fp=fopen("file1.txt","w");
    char newstr[50];
    n=0;
    while(gets(newstr)!=NULL){
        fputs(newstr,fp);
        fputc('\n',fp);
    }
    fclose(fp);
    printf("this is new new file1.txt:\n");
    fp=fopen("file1.txt","r");
    while ((ch=fgetc(fp))!=EOF)
    {
        printf("%c",ch);
    }

    fclose(fp);

    FILE *fp1=NULL;
    FILE *fp2=NULL;

    fp1=fopen("file1.txt","r");
    fp2=fopen("file.txt","w");

    printf("copying......\n");
    while ((ch=fgetc(fp1))!=EOF)
    {
        fputc(ch,fp2);
    }

    fclose(fp1);
    fclose(fp2);

    fp1=fopen("file.txt","r");
    fgets(newstr,50,fp1);

    printf("this is new file.txt\n");
    printf("%s",newstr);


    


    
    system("pause");
    




}