#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int* generatedNumbers, int count) {
    int excludedNumbers[] = {2, 5, 7, 9, 15, 17, 23, 24, 25, 28, 30, 31, 32};
    int num;
    
    srand(time(NULL)); // 初始化随机数生成器
    
    do {
        num = rand() % 35 + 2; // 生成2到36之间的随机数
        int excluded = 0;
        
        for (int i = 0; i < sizeof(excludedNumbers) / sizeof(excludedNumbers[0]); i++) {
            if (num == excludedNumbers[i]) {
                excluded = 1;
                break;
            }
        }
        
        if (!excluded) {
            int unique = 1;
            
            for (int i = 0; i < count; i++) {
                if (num == generatedNumbers[i]) {
                    unique = 0;
                    break;
                }
            }
            
            if (unique) {
                return num; // 返回生成的不在排除列表中且与已生成的数不重复的随机数
            }
        }
        
    } while (1);
}

int main() {
    int randomNumbers[8]; // 存储生成的随机数
    int count = 0; // 记录已生成的随机数数量
    
    while (count < 8) {
        int randomNumber = generateRandomNumber(randomNumbers, count);
        randomNumbers[count] = randomNumber;
        count++;
    }
    
    printf("the numbers are:");
    for (int i = 0; i < 8; i++) {
        printf("%d ", randomNumbers[i]);
    }
    printf("\n");
    
    system("pause");
    return 0;
}
