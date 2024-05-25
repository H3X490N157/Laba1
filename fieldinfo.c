#include "fieldinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>

// Integer operations
void* int_add(const void* a, const void* b) {
    int* result = malloc(sizeof(int));
    *result = *(const int*)a + *(const int*)b;
    return result;
}

void* int_mul(const void* a, const void* b) {
    int* result = malloc(sizeof(int));
    *result = *(const int*)a * *(const int*)b;
    return result;
}

void* int_scalar_mul(const void* a, double scalar) {
    int* result = malloc(sizeof(int));
    *result = *(const int*)a * (int)scalar;
    return result;
}

void int_print(const void* a) {
    printf("%d", *(const int*)a);
}

const FieldInfo* GetIntFieldInfo() {
    static FieldInfo intFieldInfo = {
        sizeof(int),
        int_add,
        int_mul,
        int_scalar_mul,
        int_print
    };
    return &intFieldInfo;
}

// Double operations
void* double_add(const void* a, const void* b) {
    double* result = malloc(sizeof(double));
    *result = *(const double*)a + *(const double*)b;
    return result;
}

void* double_mul(const void* a, const void* b) {
    double* result = malloc(sizeof(double));
    *result = *(const double*)a * *(const double*)b;
    return result;
}

void* double_scalar_mul(const void* a, double scalar) {
    double* result = malloc(sizeof(double));
    *result = *(const double*)a * scalar;
    return result;
}

void double_print(const void* a) {
    printf("%lf", *(const double*)a);
}

const FieldInfo* GetDoubleFieldInfo() {
    static FieldInfo doubleFieldInfo = {
        sizeof(double),
        double_add,
        double_mul,
        double_scalar_mul,
        double_print
    };
    return &doubleFieldInfo;
}

// Complex operations
void* complex_add(const void* a, const void* b) {
    double complex* result = malloc(sizeof(double complex));
    *result = *(const double complex*)a + *(const double complex*)b;
    return result;
}

void* complex_mul(const void* a, const void* b) {
    double complex* result = malloc(sizeof(double complex));
    *result = *(const double complex*)a * *(const double complex*)b;
    return result;
}

void* complex_scalar_mul(const void* a, double scalar) {
    double complex* result = malloc(sizeof(double complex));
    *result = *(const double complex*)a * scalar;
    return result;
}

void complex_print(const void* a) {
    printf("(%lf + %lfi)", creal(*(const double complex*)a), cimag(*(const double complex*)a));
}

const FieldInfo* GetComplexFieldInfo() {
    static FieldInfo complexFieldInfo = {
        sizeof(double complex),
        complex_add,
        complex_mul,
        complex_scalar_mul,
        complex_print
    };
    return &complexFieldInfo;
}

