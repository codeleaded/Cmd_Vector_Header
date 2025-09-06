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
    u32 size;
    size_t ELEMENT_SIZE;
    u32 Memory_SIZE;
    void **Memory;
} Vector;

Vector NewVector(size_t ELEMENT_SIZE){
    Vector v;
    v.size = 0U;
    v.ELEMENT_SIZE = ELEMENT_SIZE;
    v.Memory_SIZE = StartSize;
    v.Memory = (void**)calloc(v.Memory_SIZE,sizeof(void*));
    printf("init -> Vector.\n");
    printf("Size -> Vector: %i.\n",(int)v.Memory_SIZE);
    return v;
}

void Free2D(void ***Memory,u32 Memory_SIZE){
    printf("Begin.\n");
    for(int i = 0;i<Memory_SIZE;i++){
        if((*Memory)[i]){
            printf("Start Free.\n");
            printf("Adress: %p\n",(*Memory)[i]);
            printf("Size: %i\n",(int)sizeof((*Memory)[i]));
            free((*Memory)[i]);
            (*Memory)[i] = NULL;
            printf("End Freed: %i.\n",i);
        }else{
            printf("Can't Free nullptr.\n");
        }
    }
    if((*Memory)) free((*Memory));
    (*Memory) = NULL;
    printf("Freed 2D Memory Block.\n");
}

void ExpandVector(Vector *v){
    if(v->size>=v->Memory_SIZE){
        printf("Expand Vector.\n");
        u32 NewSize = v->Memory_SIZE+ExpandSize;
        void** NewMemory = (void**)calloc(NewSize,sizeof(void*));
        for(int i = 0;i<v->size;i++){
            if(i<NewSize&&i<v->Memory_SIZE){
                printf("Copied:\n");
                NewMemory[i] = v->Memory[i];//Dont Free Pointer -> Copied it
            }else{
                printf("Copy Error:\n");
                printf("Can't Get At Index: %i\n",i);
            }
        }
        //Just Free Pointer -> Copied Pointers not Values
        if(v->Memory) free(v->Memory);
        v->Memory = NULL;
        v->Memory = NewMemory;
        v->Memory_SIZE = NewSize;
    }else{
        printf("Don't Expand Vector: \n");
    } 
}

void CompressVector(Vector *v){
    if(v->size<=(v->Memory_SIZE-ExpandSize)){
        u32 NewSize = v->Memory_SIZE - ExpandSize;
        printf("Start Freeing All:\n");
        for(int i = v->size;i<v->Memory_SIZE;i++){
            printf("Freeing %i:\n",i);
            if(v->Memory[i]) free(v->Memory[i]);
            v->Memory[i] = NULL;
        }
        printf("Freed All:\n");
        void** NewVector = (void**)calloc(v->size,sizeof(void*));
        for(int i = 0;i<v->size;i++){
            printf("Copied: %i\n",i);
            NewVector[i] = v->Memory[i];
        }
        if(v->Memory) free(v->Memory);
        v->Memory = NULL;
        v->Memory = NewVector;
        v->Memory_SIZE = v->Memory_SIZE - ExpandSize;
        printf("Resized Vector: \n");
    }else{
        printf("Don't Expand Vector: \n");
    } 
}

void PushOfVector(Vector *v,void* Item){
    printf("size: %i.\n",(int)v->size);
    printf("Size: %i.\n",(int)v->Memory_SIZE);
    ExpandVector(v);
    if(v->size<v->Memory_SIZE){
        printf("Add Item.\n");
        if(v->Memory[v->size]) free(v->Memory[v->size]);
        v->Memory[v->size] = NULL;// Watch out
        v->Memory[v->size] = Item;
        v->size++;
    }else{
        printf("Still Not Able to Add.\n");
    }
}

void AddOfVector(Vector *v,void* Item,int Index){
    printf("size: %i.\n",(int)v->size);
    printf("Size: %i.\n",(int)v->Memory_SIZE);
    ExpandVector(v);
    if(v->size<v->Memory_SIZE&&Index<=v->size){
        printf("Add Item.\n");
        for(int i = v->size-1;i>=Index;i--){
            printf("Set %i to %i.\n",i+1,i);
            v->Memory[i+1] = v->Memory[i];
        }
        printf("Set Inserted Element.\n");
        v->Memory[Index] = Item;
        v->size++;
    }else{
        printf("Still Not Able to Add.\n");
    }
}

void PopTopOfVector(Vector *v){
    if(v->size>0){
        v->size--;
        printf("Poped Top: \n");
        CompressVector(v);
    }else{
        printf("Can't Pop Top: \n");
    }
}

void RemoveOfVector(Vector *v,u32 Index){
    if(Index>=0&&Index<v->size){
        if(v->Memory[Index]) free(v->Memory[Index]);
        v->Memory[Index] = NULL;
        v->size--;
        printf("Removed At Index: %i\n",Index);
        for(int i = Index;i<v->size;i++){
            printf("Copy %i to %i:\n",i+1,i);
            v->Memory[i] = v->Memory[i+1];
        }
        v->Memory[v->size] = NULL;
        CompressVector(v);
    }else{
        printf("Can't Remove At Index: %i\n",Index);
    }
}

void ClearOfVector(Vector *v){
    int Elements = v->size;
    printf("Clear Vector: \n");
    for(int i = Elements;i>0;i--){
        PopTopOfVector(v);
    }
}

void *GetOfVector(Vector *v,int Index){
    if(Index>=0&&Index<v->size){
        return v->Memory[Index];
    }else{
        printf("Can't Get At Index: %i\n",Index);
    }
    return NULL;
}

void SetOfVector(Vector *v,void *Item,int Index){
    if(Index>=0&&Index<v->size){
        free(v->Memory[Index]);
        v->Memory[Index] = NULL;
        v->Memory[Index] = Item;
    }else{
        printf("Can't Set At Index: %i\n",Index);
    }
}

void PrintVector(Vector *v){
    printf("Elements:%i\n",(int)v->size);
    printf("Element Size:%i\n",(int)v->ELEMENT_SIZE);
    for(int i = 0;i<v->size;i++){
        printf("Element %i: %i\n",i,*((int*)v->Memory[i]));
    }
}

void FreeVector(Vector *v){
    Free2D(&(v->Memory),v->Memory_SIZE);
    v->ELEMENT_SIZE = (size_t)0ULL;
    v->size = 0U;
    printf("Freed Hole Vector.\n");
}
