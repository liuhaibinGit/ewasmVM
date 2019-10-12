#include <FreeRTOS.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Call table/trapping table lookups/execution
#include <signal.h>

#include "util.h"
#include "platform.h"
#include "wa.h"
#include "thunk.h"
#include "system_api.h"

// WASM test files

// https://wasdk.github.io/WasmFiddle/
/*
char str[] = "welcome to webassembly!";

int add(int a, int b)
{
  return a+b;
}

int sub(int a, int b)
{
  return a-b;
}

int mul(int a, int b)
{
   return a*b;
}

int div(int a, int b)
{
  return a/b;
}

int test() { 
     int a = 250, b = 15;
     int c = a*b;
     c += a;
     c = c/a;
     c -= 1;
     if(c == b){
       prints(str);
     }
   
}

*/

unsigned char test_wasm[] = {
	0,97,115,109,1,0,0,0,1,144,128,128,128,0,3,96,0,
	1,127,96,1,127,1,127,96,2,127,127,1,127,2,142,128,
	128,128,0,1,3,101,110,118,6,112,114,105,110,116,115,
	0,1,3,134,128,128,128,0,5,2,2,2,2,0,4,132,128,128,
	128,0,1,112,0,0,5,131,128,128,128,0,1,0,1,6,129,128,
	128,128,0,0,7,169,128,128,128,0,6,6,109,101,109,111,
	114,121,2,0,3,97,100,100,0,1,3,115,117,98,0,2,3,109,
	117,108,0,3,3,100,105,118,0,4,4,116,101,115,116,0,5,
	10,193,128,128,128,0,5,135,128,128,128,0,0,32,1,32,
	0,106,11,135,128,128,128,0,0,32,0,32,1,107,11,135,128,
	128,128,0,0,32,1,32,0,108,11,135,128,128,128,0,0,32,0,
	32,1,109,11,139,128,128,128,0,1,1,127,65,16,16,0,26,32,
	0,11,11,158,128,128,128,0,1,0,65,16,11,24,119,101,108,
	99,111,109,101,32,116,111,32,119,101,98,97,115,115,101,
	109,98,108,121,33,0};

Module *vm_create(char *code, int len){
    uint8_t  *bytes = NULL;
    int       byte_count;

    bytes =  code;
    byte_count = len;
	
    Options opts;
    Module *m = load_module(bytes, byte_count, opts);
    m->path = "";
    init_thunk_in(m);

    return m;
}


int set_Pi32(int32_t num, Module *m){
    m->stack[++m->sp].value_type = I32;
    m->stack[m->sp].value.uint32 = num; 
    return 0;

}

int set_Pi64(int64_t num, Module *m){
    m->stack[++m->sp].value_type = I64;
    m->stack[m->sp].value.uint32 = num; 
    return 0;

}

int set_Pf32(float num, Module *m){
    m->stack[++m->sp].value_type = F32;
    m->stack[m->sp].value.uint32 = num; 
    return 0;   

}

int set_Pf64(double num, Module *m){
    m->stack[++m->sp].value_type = F64;
    m->stack[m->sp].value.uint32 = num; 
    return 0;    

}


int vm_exec(Module *m, char *func){
    int fidx = 0, res = 0;
    fidx = get_export_fidx(m, func);
    if (fidx == -1) {
	FATAL("no exported function %s\n", func);
    }
    res = invoke(m, fidx);

    if (!res) {
        error("Exception: %s\n", exception);
        return 1;
    }
    return 0;
}

int32_t get_Ri32(Module *m){
    if (m->sp >= 0) {
    StackValue *result = &m->stack[m->sp--];
    if(result->value_type == I32) {
	return  result->value.uint32;
	}
    }
    return 0;
}

int64_t get_Ri64(Module *m){
    if (m->sp >= 0) {
    StackValue *result = &m->stack[m->sp--];
    if(result->value_type == I64) {
	return result->value.uint64;
    }
    }
    return 0;
}

float get_Rf32(Module *m){
    if (m->sp >= 0) {
    StackValue *result = &m->stack[m->sp--];
    if(result->value_type == F32) {
	return result->value.f32;
    }
    }
    return 0;

}	

double get_Rf64(Module *m){
    if (m->sp >= 0) {
    StackValue *result = &m->stack[m->sp--];
    if(result->value_type == F64) {
	return result->value.f64;
    }
    }
    return 0;

}

int main() {
    Module *m;
    char *p;
    int len;
    init_table();
    len = sizeof(test_wasm)/sizeof(char);
    if(len > 1024) {//限制用户代码大小
        return NULL;
    }
    m = vm_create(test_wasm, len);
    vm_exec(m, "test");
    free_memory();
    return 0;
}




