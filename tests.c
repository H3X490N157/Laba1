#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fieldinfo.h"
#include "polynomial.h"

void create_polynomial_ui(Polynomial** p, const FieldInfo* fieldInfo) {
    int degree;
    printf("Введите степень многочлена: ");
    scanf("%d", &degree);
    
    *p = create_polynomial(degree, fieldInfo);
    
    for (int i = 0; i <= degree; i++) {
        printf("Введите коэффициент для x^%d: ", i);
        if (fieldInfo == GetIntFieldInfo()) {
            int value;
            scanf("%d", &value);
            (*p)->coefficients[i] = malloc(sizeof(int));
            memcpy((*p)->coefficients[i], &value, sizeof(int));
        } else if (fieldInfo == GetDoubleFieldInfo()) {
            double value;
            scanf("%lf", &value);
            (*p)->coefficients[i] = malloc(sizeof(double));
            memcpy((*p)->coefficients[i], &value, sizeof(double));
        } else if (fieldInfo == GetComplexFieldInfo()) {
            double real, imag;
            printf("Действительная часть: ");
            scanf("%lf", &real);
            printf("Мнимая часть: ");
            scanf("%lf", &imag);
            double complex value = real + imag * I;
            (*p)->coefficients[i] = malloc(sizeof(double complex));
            memcpy((*p)->coefficients[i], &value, sizeof(double complex));
        }
    }
}

void print_polynomial_ui(Polynomial* p) {
    if (p == NULL) {
        printf("Многочлен пуст.\n");
    } else {
        polynomial_print(p);
    }
}

int main() {
    Polynomial *p1 = NULL, *p2 = NULL, *result = NULL;
    int choice;
    int choice_two;
    const FieldInfo *fieldInfo = NULL;

    while (1) {
        printf("\nМеню операций с многочленами:\n");
        printf("1. Создать многочлен 1\n");
        printf("2. Создать многочлен 2\n");
        printf("3. Сложить многочлены\n");
        printf("4. Умножить многочлены\n");
        printf("5. Умножить многочлен на скаляр\n");
        printf("6. Показать многочлен 1\n");
        printf("7. Показать многочлен 2\n");
        printf("8. Показать результат\n");
        printf("9. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Выберите тип для многочлена 1:\n");
                printf("1. Целые числа\n2. Вещественные числа\n3. Комплексные числа\n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1: fieldInfo = GetIntFieldInfo(); break;
                    case 2: fieldInfo = GetDoubleFieldInfo(); break;
                    case 3: fieldInfo = GetComplexFieldInfo(); break;
                    default: printf("Некорректный выбор.\n"); continue;
                }
                create_polynomial_ui(&p1, fieldInfo);
                break;
            case 2:
                printf("Выберите тип для многочлена 2:\n");
                printf("1. Целые числа\n2. Вещественные числа\n3. Комплексные числа\n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1: fieldInfo = GetIntFieldInfo(); break;
                    case 2: fieldInfo = GetDoubleFieldInfo(); break;
                    case 3: fieldInfo = GetComplexFieldInfo(); break;
                    default: printf("Некорректный выбор.\n"); continue;
                }
                create_polynomial_ui(&p2, fieldInfo);
                break;
            case 3:
                if (p1 == NULL || p2 == NULL) {
                    printf("Оба многочлена должны быть созданы.\n");
                } 
                else {
                    if (p1->fieldInfo != p2->fieldInfo) {
                        printf("Многочлены должны быть одного типа.\n");
                    }
                    else {
                        result = polynomial_add(p1, p2);
                        printf("Многочлены сложены.\n");
                    }
                }
                break;
            case 4:
                if (p1 == NULL || p2 == NULL) {
                    printf("Оба многочлена должны быть созданы.\n");
                } 
                else {
                    if (p1->fieldInfo != p2->fieldInfo) {
                        printf("Многочлены должны быть одного типа.\n");
                    }
                    else {
                        result = polynomial_mul(p1, p2);
                        printf("Многочлены умножены.\n");
                    }
                }
                break;
            case 5:
                printf("Выберите многочлен для умножения: 1 или 2. По умолчанию выбирается 1 (при выборе иных вариантов):\n");
                scanf("%d", &choice_two);
                Polynomial* poly_to_multiply;
                if (choice_two == 2) {
                    if (p2 == NULL) {
                        printf("Многочлен 2 должен быть создан.\n");
                        continue;
                    }
                    poly_to_multiply = p2;
                } else {
                    if (p1 == NULL) {
                        printf("Многочлен 1 должен быть создан.\n");
                        continue;
                    }
                    poly_to_multiply = p1;
                }
                double scalar;
                printf("Введите значение скаляра: ");
                scanf("%lf", &scalar);
                result = polynomial_scalar_mul(poly_to_multiply, scalar);
                printf("Выбранный многочлен умножен на скаляр.\n");
                break;
            case 6:
                printf("Многочлен 1: ");
                print_polynomial_ui(p1);
                break;
            case 7:
                printf("Многочлен 2: ");
                print_polynomial_ui(p2);
                break;
            case 8:
                printf("Результат: ");
                print_polynomial_ui(result);
                break;
            case 9:
                printf("Выход\n");
                destroy_polynomial(p1);
                destroy_polynomial(p2);
                destroy_polynomial(result);
                return 0;
            default:
                printf("Некорректный выбор.\n");
                break;
        }
    }
}

