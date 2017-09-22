#define INIT_SIZE 32

typedef void * dataT;
typedef struct Stack Stack;

Stack *newstack(void);
void   freestack(Stack *stack);
void   stackpush(Stack *stack, dataT data);
dataT  stackpop(Stack *stack);
dataT  stackpeek(Stack *stack);
bool   stackisempty(Stack *stack);
