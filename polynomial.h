#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "fieldinfo.h"

typedef struct {
    void** coefficients;
    int degree;
    const FieldInfo* fieldInfo;
} Polynomial;

Polynomial* create_polynomial(int degree, const FieldInfo* fieldInfo);
void destroy_polynomial(Polynomial* p);
Polynomial* polynomial_add(const Polynomial* p1, const Polynomial* p2);
Polynomial* polynomial_mul(const Polynomial* p1, const Polynomial* p2);
Polynomial* polynomial_scalar_mul(const Polynomial* p, double scalar);
void polynomial_print(const Polynomial* p);

#endif // POLYNOMIAL_H

