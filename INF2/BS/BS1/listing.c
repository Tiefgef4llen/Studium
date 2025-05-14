#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>

typedef struct string_c {
    unsigned int size;
    char name[50];
} string_struct;
 
/* Thread-Funktion */
void *example_fct(void *args){
    /* DieÜbergabe wird zurück aufeinen struct-Pointer gecastet*/
    //uintptr_t *inParam=(uintptr_t*)args;

    printf("Thread Funktion...\n");
    string_struct* str = (string_struct*)args;
    str->size = strlen(str->name);   
 
    return NULL;
}

int main(){
    pthread_t thread;

    string_struct str = {0, "Julian"};

    printf("Length: %u,  Name: %s\n", str.size, str.name);

    pthread_create(&thread,NULL,&example_fct,(void*)&str);

    /* Warteauf Beendigung des Threads */
    pthread_join(thread, NULL);

    printf("Length: %u,  Name: %s\n", str.size, str.name);

    return 0;
}