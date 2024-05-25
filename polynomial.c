#include "polynomial.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Polynomial* create_polynomial(int degree, const FieldInfo* fieldInfo) {
    Polynomial* p = malloc(sizeof(Polynomial));
    p->degree = degree;
    p->fieldInfo = fieldInfo;
    p->coefficients = calloc(degree + 1, sizeof(void*));
    return p;
}

void destroy_polynomial(Polynomial* p) {
    for (int i = 0; i <= p->degree; i++) {
        free(p->coefficients[i]);
    }
    free(p->coefficients);
    free(p);
}

Polynomial* polynomial_add(const Polynomial* p1, const Polynomial* p2) {
    if (p1->fieldInfo != p2->fieldInfo) return NULL; // Ensure same type
    int max_degree = p1->degree > p2->degree ? p1->degree : p2->degree;
    Polynomial* result = create_polynomial(max_degree, p1->fieldInfo);

    for (int i = 0; i <= max_degree; i++) {
        if (i <= p1->degree && i <= p2->degree) {
            result->coefficients[i] = p1->fieldInfo->add(p1->coefficients[i], p2->coefficients[i]);
        } else if (i <= p1->degree) {
            result->coefficients[i] = malloc(p1->fieldInfo->size);
            memcpy(result->coefficients[i], p1->coefficients[i], p1->fieldInfo->size);
        } else {
            result->coefficients[i] = malloc(p2->fieldInfo->size);
            memcpy(result->coefficients[i], p2->coefficients[i], p2->fieldInfo->size);
        }
    }
    return result;
}

Polynomial* polynomial_mul(const Polynomial* p1, const Polynomial* p2) {
    if (p1->fieldInfo != p2->fieldInfo) return NULL; // Ensure same type
    int result_degree = p1->degree + p2->degree;
    Polynomial* result = create_polynomial(result_degree, p1->fieldInfo);

    for (int i = 0; i <= result_degree; i++) {
        result->coefficients[i] = calloc(1, p1->fieldInfo->size);
    }

    for (int i = 0; i <= p1->degree; i++) {
        for (int j = 0; j <= p2->degree; j++) {
            void* product = p1->fieldInfo->mul(p1->coefficients[i], p2->coefficients[j]);
            void* sum = p1->fieldInfo->add(result->coefficients[i + j], product);
            free(result->coefficients[i + j]);
            result->coefficients[i + j] = sum;
            free(product);
        }
    }
    return result;
}

Polynomial* polynomial_scalar_mul(const Polynomial* p, double scalar) {
    Polynomial* result = create_polynomial(p->degree, p->fieldInfo);

    for (int i = 0; i <= p->degree; i++) {
        result->coefficients[i] = p->fieldInfo->scalar_mul(p->coefficients[i], scalar);
    }
    return result;
}

void polynomial_print(const Polynomial* p) {
    for (int i = p->degree; i >= 0; i--) {
        p->fieldInfo->print(p->coefficients[i]);
        if (i > 0) printf("x^%d + ", i);
    }
    printf("\n");
}

