#define INIT_SIZE 10

typedef void * dataT;
typedef struct Stack Stack;

Stack *newstack(void);
void   freestack(Stack *stack);
void   stackpush(Stack *stack, dataT data);
dataT  stackpop(Stack *stack);
dataT  stackpeek(Stack *stack);
int    stackisempty(Stack *stack);

#endif
