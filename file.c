#include<stdlib.h>
#include<stdio.h>

int main(){
    FILE *fp;
    char str[100];
    if((fp=fopen("file.txt","w"))==NULL){
        printf("error\n");
        exit(1);
    }
    while (gets(str)!=NULL)
    {
        fputs(str,fp);
        fputc('\n',fp);
    }
    fclose(fp);
    
    return 0;
    

    
    
    
    
}