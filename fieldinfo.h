#ifndef FIELDINFO_H
#define FIELDINFO_H

#include <complex.h>
#include <stddef.h>

typedef struct FieldInfo {
    size_t size;
    void* (*add)(const void*, const void*);
    void* (*mul)(const void*, const void*);
    void* (*scalar_mul)(const void*, double);
    void (*print)(const void*);
} FieldInfo;

const FieldInfo* GetIntFieldInfo();
const FieldInfo* GetDoubleFieldInfo();
const FieldInfo* GetComplexFieldInfo();

#endif // FIELDINFO_H

