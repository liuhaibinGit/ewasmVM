#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "wa.h"


#define apis 10

struct api_func table[apis];

struct api_func{
    char *name;
    void *addr;
};

char msg[100];


int printi(int num){
    debug("%d\n", num);
    return 0;
}

int prints(int p, Module *m){
    strcpy(msg, (m->memory.bytes + p));
    debug("%s\n", msg);
    return 0;
}

int add_func(int index, int nameLen, char *name, void *funcAddr){
    table[index].name = malloc(nameLen);
    table[index].addr = funcAddr;
    memcpy(table[index].name , name, nameLen);
    return 0;
}

int init_table(){
    add_func(0, 7, "printi", (void*)printi);
    add_func(1, 7, "prints", (void*)prints);
    add_func(2, 7, "malloc", (void*)malloc);
    add_func(3, 5, "free", (void*)free);
	add_func(4, 7, "memset", (void*)memset);
	add_func(5, 7, "memcpy", (void*)memcpy);
	add_func(6, 7, "memcmp", (void*)memcmp);
    return 0;
}

void *sym_table_lookup(char *symbol){
    int i;
    for (i = 0; i < apis; i++){
       if (strcmp(symbol, table[i].name ) == 0){
                return table[i].addr;
       }
    }
    return NULL;
}

bool resolvesym(char *filename, char *symbol, void **val, char **err) {
    info("resolvesym filename: '%s', symbol: '%s'\n", filename, symbol);
    if (filename && strcmp(filename, "env") != 0) {
        *err = "resolvesym with filename unimplmented";
        return false;
    }
    *val = sym_table_lookup(symbol);
    info("           *val: %p\n", *val);
    return true;
}





