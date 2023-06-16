#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"


void insert_node(struct Node** poly, int power, int coef) {  // функция вставки слагаемого в список
    struct Node* new_node = createNode(power, coef);

    if (*poly == NULL) {
        *poly = new_node;
    }
    else {
        struct Node* temp = *poly;
        struct Node* prev = NULL;

        while (temp != NULL && temp->power > power) {  // проверяем, есть ли элементы с такой же степенью
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL && temp->power == power) {
            temp->coef += coef;  // сложение коэффициентов, если степень уже существует
            free(new_node);
        }
        else {
            if (prev == NULL) {  // вставка нового элемента в нужную позицию
                new_node->next = *poly;
                *poly = new_node;
            }
            else {
                new_node->next = prev->next;
                prev->next = new_node;
            }
        }
    }
}


void display_list(struct Node* poly) {  // функция вывода многочлена
    struct Node* temp = poly;

    while (temp != NULL) {
        if (temp->coef != 0) {
            if (temp != poly && temp->coef > 0) {
                printf("+");
            }
            if (temp->power == 0) {
                printf("%d", temp->coef);
            }
            else if (temp->power == 1) {
                if (temp->coef == 1) {
                    printf("x");
                }
                else if (temp->coef == -1) {
                    printf("-x");
                }
                else {
                    printf("%dx", temp->coef);
                }
            }
            else {
                if (temp->coef == 1) {
                    printf("x^%d", temp->power);
                }
                else if (temp->coef == -1) {
                    printf("-x^%d", temp->power);
                }
                else {
                    printf("%dx^%d", temp->coef, temp->power);
                }
            }
        }
        temp = temp->next;
    }
    printf("\n");
}

bool read_polynomial(struct Node** poly) {  //функция считывания многочлена
    int power, coef;
    char ch;
    char coef_[20], power_[20];

    printf("Введите коэффициенты и степени слагаемых:\n");

    do {
        scanf("%s %s", coef_, power_);

        if (!is_int(coef_) || !is_int(power_)) {
            return false;
        }

        coef = atoi(coef_);
        power = atoi(power_);

        insert_node(poly, power, coef);
        scanf("%c", &ch);
    }
    while (power != 0 || coef != 0);
    return true;
}

void remove_even_terms(struct Node** poly) {  // функция удаления слагаемых с четной степенью
    struct Node* curr = *poly;
    struct Node* prev = NULL;

    while (curr != NULL) {
        if (curr->power % 2 == 0 && curr->power != 0) {
            if (prev == NULL) {
                *poly = curr->next;
            }
            else {
                prev->next = curr->next;
            }

            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

int main() {
    struct Node* polynom = NULL;

    if (read_polynomial(&polynom) == true){

        printf("Исходный многочлен: ");
        display_list(polynom);

        remove_even_terms(&polynom);

        printf(ANSI_COLOR_GREEN"Обработанный многочлен: ");
        display_list(polynom);
    }
    else{
        printf(ANSI_COLOR_RED "ERROR: Введен некорректный символ.");
    }

    return 0;
}

