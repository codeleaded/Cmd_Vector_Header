#include ".\Vector.h"

#define TYPE_USED u8

int main(int argc,char **argv){
    printf("Start:\n");

    Vector v = NewVector(sizeof(TYPE_USED));

    PrintVector(&v);

    for(int i = 0;i<31;i++){
        PushOfVector(&v,(void*)calloc(1,v.ELEMENT_SIZE));
        TYPE_USED *ptr = (TYPE_USED*)(v.Memory[i]);
        *ptr = (TYPE_USED)i;
    }
    /*printf("1------------------------------------------\n");
    int Elements = 15;
    for(int i = Elements;i>0;i--){
        printf("Pop Element: %i\n",v.size);
        PopTopOfVector(&v);
    }
    printf("2------------------------------------------\n");
    Elements = 6;
    for(int i = 0;i<Elements;i++){
        AddOfVector(&v,(void*)calloc(1,v.ELEMENT_SIZE));
    }
    printf("3------------------------------------------\n");*/
    for(int i = 0;i<2;i++){
        //RemoveOfVector(&v,(u32)5);
        //PrintVector(&v);
    }
    for(int i = 0;i<2;i++){
        AddOfVector(&v,(void*)calloc(1,v.ELEMENT_SIZE),2);
        PrintVector(&v);
    }
    printf("4------------------------------------------\n");
    //ClearOfVector(&v);

    /*for(int i = 0;i<v.size;i++){
        TYPE_USED *ptr = (TYPE_USED*)v.Memory[i];
        *ptr = (TYPE_USED)100;
    }
    for(int i = 0;i<v.size;i++){
        TYPE_USED *ptr = (TYPE_USED*)v.Memory[i];
        printf("Element At %i: %i\n",i,(int)(*ptr));
    }*/

    PrintVector(&v);
    FreeVector(&v);

    return 0;
}