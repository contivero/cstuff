typedef void * queueElemT;
typedef struct Queue Queue;

Queue     *newqueue(void);
void       freequeue(Queue *queue);

queueElemT dequeue(Queue *queue);
void       enqueue(Queue *queue, queueElemT element);
int        queueisempty(Queue *queue);
int        queueisfull(Queue *queue);
int        queuelength(Queue *queue);
