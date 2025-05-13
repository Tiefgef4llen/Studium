#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>

typedef struct string_c {
    unsigned int size;
    char name[50];
} string_t;
 
/* Thread-Funktion */
void *example_fct(void *args){
    /* DieÜbergabe wird zurück aufeinen int-Pointer gecastet*/
    //uintptr_t *inParam=(uintptr_t*)args;
    string_t* str = (string_t*)args;
    str->size = strlen(str->name);   
 
    return NULL;
}

int main(){
    /* Legeein Thread-Handle, einenÜbergabe-und einen Rückgabeparameter an*/
    pthread_t thread;

    string_t str = {0, "Julian"};

    printf("Length: %u,  Name: %s\n", str.size, str.name);

    pthread_create(&thread,NULL,&example_fct,(void*)&str);
    /* Warteauf Beendigung des Threads */
    //pthread_join(thread,(void **)(&threadRetParam));
    pthread_join(thread, NULL);


    /* Inhalt desRückgabeparameters ausgeben */
    //printf("Rueckgabe von Thread:%llu\n",threadRetParam);
    printf("Length: %u,  Name: %s\n", str.size, str.name);

    return 0;
}