#include <stdio.h>
#include <memory.h>
#include <stdlib.h>


// // 查找数组中出现次数超过一半的数字
// int find_exceed_half_count(const int* arr, int len) {
//     int tmp[100000] = {0};
//     int max_count = 0, result = 0;

//     for (int i = 0; i < len; i++) {
//         tmp[arr[i]]++;
//         if (tmp[arr[i]] > max_count) {
//             max_count = tmp[arr[i]];
//             result = arr[i];
//         }
//     }

//     return (max_count > len / 2) ? result : 0;
// }


// int main() {
//     int in[] = {1, 2, 2};

//     int res = find_exceed_half_count(in, 3);

//     printf("%d \n", res);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValidIpAddress(const char *ipAddress) {
    int num, dots = 0;
    int i, j, len = strlen(ipAddress);
    int partLen = 0, partCount = 0;
    char part[4] = {0};

    // 检查IP地址是否为空
    if (len == 0) {
        return 0;
    }

    // 检查IP地址的每个字符
    for (i = 0; i < len; i++) {
        char c = ipAddress[i];

        // 检查字符是否为数字
        if (c >= '0' && c <= '9') {
            if (partLen == 3) {
                return 0;  // IP地址部分长度超过3位
            }
            part[partLen++] = c;
        }
        // 检查字符是否为点号
        else if (c == '.') {
            if (partLen == 0) {
                return 0;  // 点号前没有数字
            }
            num = atoi(part);
            if (num < 0 || num > 255) {
                return 0;  // IP地址部分超出合法范围
            }
            partLen = 0;
            partCount++;
        }
        // 其他非法字符
        else {
            return 0;
        }
    }

    // 检查IP地址是否有四个部分
    if (partCount != 3) {
        return 0;
    }

    return 1;
}

unsigned int ipToInt(const char *ipAddress) {
    unsigned int ip = 0;
    int i, j, len = strlen(ipAddress);
    int partLen = 0, partCount = 0;
    char part[4] = {0};

    // 将IP地址转换为整数
    for (i = 0; i < len; i++) {
        char c = ipAddress[i];

        // 检查字符是否为数字
        if (c >= '0' && c <= '9') {
            if (partLen == 3) {
                return 0;  // IP地址部分长度超过3位
            }
            part[partLen++] = c;
        }
        // 检查字符是否为点号
        else if (c == '.') {
            if (partLen == 0) {
                return 0;  // 点号前没有数字
            }
            int num = atoi(part);
            ip = (ip << 8) + num;
            partLen = 0;
            partCount++;
        }
        // 其他非法字符
        else {
            return 0;
        }
    }

    // 检查IP地址是否有四个部分
    if (partCount != 3) {
        return 0;
    }

    int num = atoi(part);
    ip = (ip << 8) + num;

    return ip;
}

int main() {
    char ipAddress[16];
    printf("请输入IP地址: ");
    fgets(ipAddress, sizeof(ipAddress), stdin);

    // 去除输入中的换行符
    int len = strlen(ipAddress);
    if (ipAddress[len - 1] == '\n') {
        ipAddress[len - 1] = '\0';
    }

    // 检查IP地址的有效性
    if (!isValidIpAddress(ipAddress)) {
        printf("非法的IP地址\n");
        return 0;
    }

    // 转换IP地址为整数并输出结果
    unsigned int ip = ipToInt(ipAddress);
    printf("转换后的整数表示: %u\n", ip);

    return 0;
}