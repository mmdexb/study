#include<stdlib.h>
#include<stdio.h>

int main() {
    FILE* fp;
    char str1[10], str2[10], str3[10];
    int year;

    fp = fopen("file1.txt", "w+");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return 1;
    }

    fputs("we are in 2014", fp);
    rewind(fp);
    fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
    printf("%s %s %s %d\n", str1, str2, str3, year);

    fseek(fp, 2, SEEK_SET);
    fputs("new content", fp);
    rewind(fp);

    fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
    printf("%s %s %s %d\n", str1, str2, str3, year);

    fclose(fp);

    system("pause");
    return 0;
}
