#include<stdlib.h>
#include<stdio.h>

int main(){
    FILE *fp;
    char str[100];
    if((fp=fopen("file.txt","r"))==NULL){
        printf("error\n");
        exit(1);
    }
    while (fgets(str,81,fp)!=NULL)
    {
        printf("%s",str);
    }
    fclose(fp);
    system("pause");
    

    return 0;
    

    
    
    
    
}