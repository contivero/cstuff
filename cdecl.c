/* Implementation taken from "Expert C Programming", pages 88-91 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define MAX_TOKENS    100
#define MAX_TOKEN_LEN 64
#define PUSH(s)       stack[++top]=(s)
#define POP           stack[top--]

enum typetag {IDENTIFIER, QUALIFIER, TYPE};

typedef struct Token {
    char type;
    char string[MAX_TOKEN_LEN];
} Token;

static int top = -1;
static Token stack[MAX_TOKENS];
static Token this;
static const char *types[] = {"void", "char", "signed", "unsigned", "short", "int",
                        "long", "float", "double", "struct", "union", "enum"};

enum typetag
classifystring(void){
    char *s = this.string;

    if(!strcmp(s, "const")){
        strcpy(s, "read-only");
        return QUALIFIER;
    }

    if(!strcmp(s, "volatile"))
        return QUALIFIER;

    for(int i = 0; i < NELEMS(types); i++){
        if(!strcmp(s, types[i]))
            return TYPE;
    }

    return IDENTIFIER;
}

void
gettoken(void){
    char *p = this.string;

    /* read past any spaces */
    while((*p = getchar()) == ' ')
        ;

    if(isalnum(*p)){
        while(isalnum(*++p = getchar()))
            ;
        ungetc(*p, stdin);
        *p = '\0';
        this.type = classifystring();
        return;
    }

    if(*p == '*'){
        strcpy(this.string, "pointer to");
        this.type = '*';
        return;
    }
    this.string[1] = '\0';
    this.type = *p;
    return;
}

void
readtillfirstidentifier(void){
    gettoken();
    while(this.type != IDENTIFIER){
        PUSH(this);
        gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
}

void
arrays(){
    while(this.type == '['){
        printf("array ");
        gettoken();
        if(isdigit(this.string[0])){
            printf("0..%d ", atoi(this.string) - 1);
            gettoken(); /* consume the ']' */
        }
        gettoken();
        printf("of ");
    }
}

void
pointers(){
    while(stack[top].type == '*'){
        printf("%s ", POP.string);
    }
}

void
functionargs(void){
    while(this.type != ')'){
        gettoken();
    }
    gettoken();
    printf("function returning ");
}

void
declarator(void){
    /* deal with possible array/function following the identifier */
    switch(this.type){
    case '[': arrays();
              break;
    case '(': functionargs();
              break;
    }
    pointers();

    while(top >= 0){
        if(stack[top].type == '('){
            top--;
            gettoken(); /*read past ')' */
            declarator();
        } else {
            printf("%s ", POP.string);
        }
    }
}

int
main(int argc, char **argv){
    if(argc)

    readtillfirstidentifier();
    declarator();
    printf("\n");
    return 0;
}
