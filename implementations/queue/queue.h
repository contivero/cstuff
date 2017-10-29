typedef void * elemT;
typedef struct Queue Queue;

Queue  *newqueue(void);
void   freequeue(Queue *queue);

elemT  dequeue(Queue *queue);
void   enqueue(Queue *queue, elemT element);
size_t queuesize(Queue *queue);
bool   queueisempty(Queue *queue);
bool   queueisfull(Queue *queue);
