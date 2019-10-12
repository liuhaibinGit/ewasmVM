#ifndef SYS_API_H
#define SYS_API_H


int init_table();

bool resolvesym(char *filename, char *symbol, void **val, char **err);

#endif

