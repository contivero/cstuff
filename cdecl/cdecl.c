/* Based on the finite state machine implementation
 * on "Expert C Programming"
 *
 * TODO: fix const not printing properly when at the start of the declaration
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..util.h"

#define MAX_TOKENS    40
#define MAX_TOKEN_LEN 64

enum kind {CONST, VOLATILE, TYPE, IDENTIFIER, POINTER, ARRAY, FUNCTION };

typedef struct Token {
    char kind;
    char string[MAX_TOKEN_LEN];
} Token;

enum kind classifytoken(void);
void gettoken(void);
void parseuntilidentifier(void);
void processvolatile(void);
void processconst(void);
void processarray(void);
void processpointer(void);
void processparams(void);
void processleftparen(void);
void processtype(void);
void arrangetype(void);

int top = -1;
Token stack[MAX_TOKENS];
Token currenttoken;
const char *types[] = {"void", "char", "signed", "unsigned", "short", "int",
                       "long", "float", "double", "struct", "union", "enum"};
const char *texts[] = {"read-only ", "pointer to ", "array of ",
                       "function returning " };

void (*nextstate)(void) = parseuntilidentifier;

void
parseuntilidentifier(void){
    gettoken();
    while(currenttoken.kind != IDENTIFIER){
        if(++top >= MAX_TOKENS){
            die("error: too many tokens\n");
        }
        stack[top] = currenttoken;
        gettoken();
    }
    printf("%s is ", currenttoken.string);
    gettoken();
    nextstate = processarray;
}

void
gettoken(void){
    char *s = currenttoken.string;

    while((*s = getchar()) == ' ' || *s == '\t')
        ; /* ignore starting whitespaces */

    if(isalnum(*s)){
        while(isalnum(*++s = getchar()))
            ; /* parse token */
        ungetc(*s, stdin);
        *s = '\0';
        currenttoken.kind = classifytoken();
        return;
    }
    currenttoken.string[1] = '\0';
    currenttoken.kind = *s;
    return;
}

enum kind
classifytoken(void){
    char *s = currenttoken.string;
    if(!strcmp(s, "const")){
        strcpy(s, "read-only");
        return CONST;
    }

    if(!strcmp(s, "volatile"))
        return VOLATILE;

    for(int i = 0; i < NELEMS(types); i++)
        if(!strcmp(s, types[i]))
            return TYPE;

    return IDENTIFIER;
}

void
processconst(void){
    printf("read-only");
}

void
processvolatile(void){

}

void
processarray(void){
    nextstate = processparams;
    while(currenttoken.kind == '['){
        printf("an array of ");
        gettoken(); /* number or ']' */
        if(isdigit(currenttoken.string[0])){
            printf("%d ", atoi(currenttoken.string));
            gettoken(); /* read the ']' */
        }
        gettoken();
        printf("of ");
        nextstate = processleftparen;
    }
}

void
processfunction(void){}

void
processparams(void){
    if(currenttoken.kind == '('){
        while(currenttoken.kind != ')'){
            gettoken();
        }
        gettoken();
        printf("function returning ");
    }
    nextstate = processleftparen;
}

void
processleftparen(void){
    nextstate = processpointer;
    if(top >= 0){
        if(stack[top].kind == '('){
            top--;
            gettoken(); /* read past ')' */
            nextstate = processarray;
        }
    }
}

void
processpointer(void){
    if(stack[top].kind == '*'){
        printf("pointer to ");
        top--;
        nextstate = processleftparen;
    } else if(stack[top].kind == VOLATILE){
        printf("%s ", stack[top--].string);
        nextstate = processleftparen;
    } else if(stack[top].kind == CONST){
        printf("constantin ", stack[top--].string);
    } else {
        nextstate = processtype;
    }
}

void
processtype(void){
    arrangetype();
    printf("\n");
    nextstate = NULL;
}

void
arrangetype(void){
    if(top < 0)
        return;

    int t = top--;
    arrangetype();
    printf("%s ", stack[t].string);
}

int
main(void){
    while(nextstate)
        (*nextstate)();

    return 0;
}
