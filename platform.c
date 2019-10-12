#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "util.h"


#define num 1000

void *pTable[num];

int count = 0; //限制分配内存块的数量
int allocated = 0; //限制虚拟机使用内存大小
void free_memory(){
    for(int i = 0; i < count; i++){
	 free(pTable[i]);
    }
}

// Assert calloc
void *acalloc(size_t nmemb, size_t size, char *name)
{
    allocated += nmemb*size;
    if(allocated > 10240){
            return NULL;
    }
    void *res = calloc(nmemb, size);
    if (nmemb * size == 0){
        warn("acalloc: %s requests allocating 0 bytes.\n", name);
    }
    else if (res == NULL || count == num){
        FATAL("Could not allocate %ul bytes for %s", nmemb * size, name);
    }
    warn("*** %s allocated %d ***\n", name, nmemb*size);
    pTable[count++] = res;
    return res;
}

// Assert realloc/calloc
void *arecalloc(void *ptr, size_t old_nmemb, size_t nmemb,
                size_t size, char *name)
{
    allocated += (nmemb - old_nmemb)*size;
    if(allocated > 10240){
            return NULL;
            
    }

    char *res = realloc(ptr, nmemb * size);
    if (res == NULL){
        FATAL("Could not allocate %ul bytes for %s", nmemb * size, name);
    }
    // Initialize new memory
    memset(res + old_nmemb * size, 0, (nmemb - old_nmemb) * size);
    if(ptr != res){ //内存搬移
         warn("%p move to %p \n",ptr,res);
         for(int i=0; i < count; i++){
            if(pTable[i] == ptr){
                trace("update %d pointer\n", i);
                pTable[i] = res;
            }

         }
             
    }
    return res;
}

/**
 *  dumpMemoryInfo - RTOS specific function to trace available heap memory
 *
 */
void dumpMemoryInfo()
{

}



