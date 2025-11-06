#if defined(__linux__)
    #include "/home/codeleaded/System/Static/Container/Vector.h"
#elif defined(_WINE)
    #include "/home/codeleaded/System/Static/Container/Vector.h"
#elif defined(_WIN32)
    #include "F:/home/codeleaded/System/Static/Container/Vector.h"
#elif defined(__APPLE__)
    #error "Apple not supported!"
#else
    #error "Platform not supported!"
#endif

int main(int argc,char **argv){
    Vector v = Vector_New(sizeof(int));

    Vector_Push(&v,(int[]){ 0 });
    Vector_PushCount(&v,(int[]){ 1,2,3,4,5,6,7,8,9,10 },10);

    Vector_PopTop(&v);
    Vector_Remove(&v,0);
    Vector_RemoveCount(&v,1,3);

    Vector_Print(&v);

    Vector_Clear(&v);

    Vector_Free(&v);
    return 0;
}