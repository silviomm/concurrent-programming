#include "aux.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
v0 = malloc(sizeof(int)*10);
int i;
for(i=0;i<10;i++){v0[i] = 0;}
vPrincipal = v0;
TAM = 10;
int v1[] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op1(1, v1, 0);
int v2[] = {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op2(1, v2, 1);
int v3[] = {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op1(1, v3, 0);
int v4[] = {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op1(3, v4, 0);
int v5[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op2(3, v5, 1);
int v6[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op1(3, v6, 0);
int v7[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op1(2, v7, 0);
int v8[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op4(3, v8, 0);
int v9[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};op1(3, v9, 0);
int v10[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0};op3(2, v10, 1);
int v11[] = {1 ,3 ,0 ,0 ,0 ,0 ,0 ,2 ,0 ,0};op1(2, v11, 0);

 return 0;
}