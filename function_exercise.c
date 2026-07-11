/*
 * 函数练习 — 2026-07-11
 * print_hello / Max / swap_case / sum_array / 冒泡排序
 */

#include <stdio.h>

// ========== 1. 基础函数调用 ==========
void print_hello() {
    printf("hello world\n");
}

// ========== 2. 带参数，有返回值 ==========
int Max(int a, int b) {
    return (b > a) ? b : a;
}

// ========== 3. 指针操作字符串 ==========
int swap_case(char *str) {
    int count = 0;
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z')
            *str -= 32;
        else if (*str >= 'A' && *str <= 'Z') {
            *str += 32;
            count++;
        }
        str++;
    }
    return count;
}

// ========== 4. 指针传出参数 ==========
void swap_case_v2(char *str, int *sum_p) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z')
            *str -= 32;
        else if (*str >= 'A' && *str <= 'Z') {
            *str += 32;
            (*sum_p)++;
        }
        str++;
    }
}

// ========== 5. 数组传参 ==========
int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

// ========== 6. 冒泡排序（降序） ==========
void swap_if_less(int *a, int *b) {
    if (*a < *b) {
        int t = *a;
        *a = *b;
        *b = t;
    }
}

void sort_desc(int *array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            swap_if_less(array + i, array + j);
        }
    }
}

// ========== 主函数测试 ==========
int main() {
    printf("===== 1. print_hello =====\n");
    print_hello();

    printf("\n===== 2. Max =====\n");
    printf("Max(3, 5) = %d\n", Max(3, 5));

    printf("\n===== 3. swap_case =====\n");
    char str1[] = "Hello World";
    int changed = swap_case(str1);
    printf("changed: %d, result: %s\n", changed, str1);

    printf("\n===== 4. swap_case_v2 (指针传出) =====\n");
    char str2[] = "HeLLo WOrLD";
    int sum = 0;
    swap_case_v2(str2, &sum);
    printf("changed: %d, result: %s\n", sum, str2);

    printf("\n===== 5. sum_array =====\n");
    int arr[] = {1, 3, 2, 4, 2, 5, 2};
    int size = sizeof(arr) / sizeof(int);
    printf("sum = %d\n", sum_array(arr, size));

    printf("\n===== 6. sort_desc (降序) =====\n");
    int array[] = {1, 4, 2, 5, 6, 7, 4};
    size = sizeof(array) / sizeof(int);
    sort_desc(array, size);
    for (int k = 0; k < size; k++)
        printf("%d\t", *(array + k));
    printf("\n");

    return 0;
}
