#include <stdio.h>
#include <stdlib.h>

struct Node {  // объявляем структуру
    int power;
    int coef;
    struct Node* next;
};

struct Node* createNode(int power, int coef) {  // функция создания нового узла списка
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->power = power;
    newNode->coef = coef;
    newNode->next = NULL;
    return newNode;
}

typedef enum { false, true } bool; // объявляем новый тип "bool" для более удобной реализации функции


bool is_int(char* str) {
    int i = 0;

    if (str[i] == '-')  // проверяем, что первый символ может быть знаком минуса
        i++;

    for (; str[i] != '\0'; i++) {  // проверяем, что остальные символы являются цифрами
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}