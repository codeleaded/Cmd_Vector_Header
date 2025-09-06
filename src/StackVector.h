#pragma once
#define StartSize 5
#define ExpandSize 5
#define NULL_PTR (void*)NULL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vector
{
    s32 size;
    size_t ELEMENT_SIZE;
    u32 Memory_SIZE;
    void* Memory;
} Vector;

Vector NewVector(size_t ELEMENT_SIZE) {
    Vector v;
    v.size = 0;
    v.ELEMENT_SIZE = ELEMENT_SIZE;
    v.Memory_SIZE = StartSize;
    v.Memory = (void*)calloc(v.Memory_SIZE, v.ELEMENT_SIZE);
    printf("init -> Vector.\n");
    printf("Size -> Vector: %i.\n", (int)v.Memory_SIZE);
    return v;
}

void* GetOfVector(Vector* v, int Index) {
    if (Index >= 0 && Index < v->size) {
        return &(((char*)v->Memory)[Index * v->ELEMENT_SIZE]);
    }
    else {
        printf("Can't Get At Index: %i\n", Index);
    }
    return NULL;
}

void SetOfVector(Vector* v, char* Item, int Index) {
    if (Index >= 0 && Index < v->size) {
        void* Dst = &(((char*)v->Memory)[Index * v->ELEMENT_SIZE]);
        memcpy(Dst, Item, v->ELEMENT_SIZE);
    }
    else {
        printf("Can't Set At Index: %i\n", Index);
    }
}

void ExpandVector(Vector* v) {
    if (v->size >= v->Memory_SIZE) {
        printf("Expand Vector.\n");
        s32 NewSize = v->Memory_SIZE + ExpandSize;
        char* NewMemory = (char*)calloc(NewSize, v->ELEMENT_SIZE);
        memcpy(NewMemory, v->Memory, v->size * v->ELEMENT_SIZE);
        if (v->Memory) free(v->Memory);
        v->Memory = NULL;
        v->Memory = NewMemory;
        v->Memory_SIZE = NewSize;
    }
    else {
        printf("Don't Expand Vector: \n");
    }
}

void CompressVector(Vector* v) {
    if (v->size <= (v->Memory_SIZE - ExpandSize)) {
        u32 NewSize = v->Memory_SIZE - ExpandSize;
        char* NewMemory = (char*)calloc(NewSize, v->ELEMENT_SIZE);
        memcpy(NewMemory, v->Memory, NewSize * v->ELEMENT_SIZE);
        if (v->Memory) free(v->Memory);
        v->Memory = NULL;
        v->Memory = NewMemory;
        v->Memory_SIZE = NewSize;
        printf("Resized Vector: \n");
    }
    else {
        printf("Don't Expand Vector: \n");
    }
}

void PushOfVector(Vector* v, char* Item) {
    printf("size: %i.\n", (int)v->size);
    printf("Size: %i.\n", (int)v->Memory_SIZE);
    ExpandVector(v);
    if (v->size < v->Memory_SIZE) {
        printf("Add Item.\n");
        SetOfVector(v, Item, v->size++);
    }
    else {
        printf("Still Not Able to Add.\n");
    }
}

void AddOfVector(Vector* v, char* Item, int Index) {
    printf("size: %i.\n", (int)v->size);
    printf("Size: %i.\n", (int)v->Memory_SIZE);
    ExpandVector(v);
    if (v->size < v->Memory_SIZE && Index <= v->size) {
        printf("Add Item.\n");
        void* Src = &(((char*)v->Memory)[Index * v->ELEMENT_SIZE]);
        void* Dst = &(((char*)v->Memory)[(Index + 1) * v->ELEMENT_SIZE]);
        memcpy(Dst, Src, (size_t)((v->size - Index) * v->ELEMENT_SIZE));
        SetOfVector(v, Item, Index);
    }
    else {
        printf("Still Not Able to Add.\n");
    }
}

void PopTopOfVector(Vector* v) {
    if (v->size > 0) {
        v->size--;
        printf("Poped Top: \n");
        CompressVector(v);
    }
    else {
        printf("Can't Pop Top: \n");
    }
}

void RemoveOfVector(Vector* v, u32 Index) {
    if (Index >= 0 && Index < v->size) {
        v->size--;
        printf("Removed At Index: %i\n", Index);
        void* Src = &(((char*)v->Memory)[(Index + 1) * v->ELEMENT_SIZE]);
        void* Dst = &(((char*)v->Memory)[Index * v->ELEMENT_SIZE]);
        memcpy(Dst, Src, (size_t)((v->size - Index) * v->ELEMENT_SIZE));
        CompressVector(v);
    }
    else {
        printf("Can't Remove At Index: %i\n", Index);
    }
}

void ClearOfVector(Vector* v) {
    if (v->Memory) free(v->Memory);
    v->Memory_SIZE = 0;
    v->size = 0;
    v->Memory = calloc(StartSize, v->ELEMENT_SIZE);
}

void PrintVector(Vector* v) {
    printf("Elements:%i\n", (int)v->size);
    printf("Element Size:%i\n", (int)v->ELEMENT_SIZE);
    for (int i = 0; i < v->size; i++) {
        for (int j = 0; j < 0; j++) {
            printf("%c ", ((char*)v->Memory)[i * v->ELEMENT_SIZE + j]);
        }
        printf("Element %i: \n", i);
    }
}

void FreeVector(Vector* v) {
    if (v->Memory) free(v->Memory);
    v->Memory = NULL;
    v->ELEMENT_SIZE = (size_t)0ULL;
    v->size = 0U;
    printf("Freed Hole Vector.\n");
}