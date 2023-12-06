#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randInt() {
    
    return (rand() % 100) + 1;
}

int randInt2() {
    return (rand() % 4) + 1;
}

int add(int num1, int num2) {
    return num1 + num2;
}

int sub(int num1, int num2) {
    return num1 - num2;
}

int mul(int num1, int num2) {
    return num1 * num2;
}

int divd(int num1, int num2) {
    return num1 / num2;
}

double Time(time_t start) {
    return difftime(time(NULL), start);
}

void check(int result_user, int result) {
    if (result_user == result) {
        printf("very good\n");
    } else {
        printf("wrong! 再试一次");
        scanf("%d", &result_user);
        if (result_user == result) {
            printf("very good\n");
        } else {
            printf("wrong! 答案是：");
            printf("%d", result);
        }
    }
}

int main() {
    system("chcp 65001");
    printf("****************************************\n");
    printf("*Created by 陈薏帆 网安233 202301050854*\n");
    printf("****************************************\n");
    

    int col;
    double right = 0;
    int count = 5;
    int result;
    int result_user;
    int temp1;
    int temp2;
    double right_rate;

    while (1) {
        printf("请输入你的运算\n");
        printf("1加法运算\n2减法运算\n3乘法运算\n4除法运算\n5混合运算\n0退出\n*******************\n");
        scanf("%d", &col);

        switch (col) {
            case 1:
                for (int i = 0; i < count; i++) {
                    temp1 = randInt();
                    temp2 = randInt();
                    result = add(temp1, temp2);
                    printf("请在100s内计算 %d + %d =\n", temp1, temp2);
                    time_t start = time(NULL);
                    double elapsed;
                    scanf("%d", &result_user);
                    elapsed = Time(start);
                    if (elapsed > 100.0) {
                        printf("超时，此题判错\n");
                    } else {
                        check(result_user, result);
                        if (result_user == result) {
                            right++;
                        }
                    }
                }
                break;

            case 2:
                for (int i = 0; i < count; i++) {
                    srand((unsigned int)time(NULL));
                    temp1 = randInt();
                    temp2 = randInt();
                    result = sub(temp1, temp2);
                    printf("请在100s内计算 %d - %d =\n", temp1, temp2);
                    time_t start = time(NULL);
                    double elapsed;
                    scanf("%d", &result_user);
                    elapsed = Time(start);
                    if (elapsed > 100.0) {
                        printf("超时，此题判错\n");
                    } else {
                        check(result_user, result);
                        if (result_user == result) {
                            right++;
                        }
                    }
                }
                break;

            case 3:
                for (int i = 0; i < count; i++) {
                    temp1 = randInt();
                    temp2 = randInt();
                    result = mul(temp1, temp2);
                    printf("请在100s内计算 %d * %d =\n", temp1, temp2);
                    time_t start = time(NULL);
                    double elapsed;
                    scanf("%d", &result_user);
                    elapsed = Time(start);
                    if (elapsed > 100.0) {
                        printf("超时，此题判错\n");
                    } else {
                        check(result_user, result);
                        if (result_user == result) {
                            right++;
                        }
                    }
                }
                break;

            case 4:
                for (int i = 0; i < count; i++) {
                    temp1 = randInt();
                    temp2 = randInt();
                    while (temp2 == 0) {
                        temp2 = randInt();
                    }
                    result = divd(temp1, temp2);
                    printf("请在100s内计算 仅回答整数部分 %d / %d =\n", temp1, temp2);
                    time_t start = time(NULL);
                    double elapsed;
                    scanf("%d", &result_user);
                    elapsed = Time(start);
                    if (elapsed > 100.0) {
                        printf("超时，此题判错\n");
                    } else {
                        check(result_user, result);
                        if (result_user == result) {
                            right++;
                        }
                    }
                }
                break;

            case 5:
                for (int i = 0; i < count; i++) {
                    temp1 = randInt();
                    temp2 = randInt();
                    int operation = randInt2();
                    switch (operation) {
                        case 1:
                            result = add(temp1, temp2);
                            printf("请在100s内计算 %d + %d =\n", temp1, temp2);
                            break;
                        case 2:
                            result = sub(temp1, temp2);
                            printf("请在100s内计算 %d - %d =\n", temp1, temp2);
                            break;
                        case 3:
                            result = mul(temp1, temp2);
                            printf("请在100s内计算 %d * %d =\n", temp1, temp2);
                            break;
                        case 4:
                            while (temp2 == 0) {
                                temp2 = randInt();
                            }
                            result = divd(temp1, temp2);
                            printf("请在100s内计算 仅回答整数部分 %d / %d =\n", temp1, temp2);
                            break;
                    }
                    time_t start = time(NULL);
                    double elapsed;
                    scanf("%d", &result_user);
                    elapsed = Time(start);
                    if (elapsed > 100.0) {
                        printf("超时，此题判错\n");
                    } else {
                        check(result_user, result);
                        if (result_user == result) {
                            right++;
                        }
                    }
                }
                break;

            case 0:
                return 0;
            default:
                printf("无效的输入，请重新选择\n");
                break;
        }

        right_rate = right * 20.0;
        printf("你的正确率是：%.2f%%\n", right_rate);
        system("pause");
    }
}
