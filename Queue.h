typedef int ElementType;

#ifndef _Queue_h
#define _Queue_h
#define ProgNum 3

struct QueueRecord; 
typedef struct QueueRecord *Queue;

//Criação e destruição de Queues
Queue CreateQueue( int MaxElements );
void DisposeQueue( Queue Q );

//Controlo das Queues
int IsEmptyQueue(Queue Q);
int IsFullQueue( Queue Q );
void MakeEmptyQueue( Queue Q );

//Operações das Queues
int Front( Queue Q );
void Enqueue( int X, Queue Q );
int Dequeue( Queue Q );

//Others
void printQueue(Queue Q);

//Auxiliares
int firstNonZeroPosition(int ID, int array[ID][8]);
int arrayIsEmpty(int array[ProgNum][8]);
#endif