#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fatal.h"
#include "Queue.h"

#define ProgNum 3

int main()
{

    int time = 0;
    int New = -1;
    int contadorNewQ = 0;
    Queue NewQ = CreateQueue(ProgNum * 8 * 10);
    Queue ReadyQ = CreateQueue(ProgNum * 8 * 10);
    Queue BlockedQ = CreateQueue(ProgNum * 8 * 10);
    Queue ExitQ = CreateQueue(ProgNum);

    int programas[3][8] = {
        {0, 6, 9, 3, 3, 4, 0, 0},
        {1, 7, 2, 4, 1, 2, 0, 0},
        {2, 1, 1, 5, 1, 1, 0, 0}};

    for (int ID = 0; ID < ProgNum; ID++){
                Enqueue(ID, NewQ);
        }

    printf("  instante  |   proc1   |   proc2   |   proc3\n\n");
    while (!(IsEmptyQueue(BlockedQ) && IsEmptyQueue(NewQ) && IsEmptyQueue(ReadyQ)) ){
        if(!IsEmptyQueue(NewQ)){
            if (programas[Front(NewQ)][0] == time + 1 || programas[Front(NewQ)][0] >= time  ){
                Enqueue(Dequeue(NewQ), ReadyQ); // passa os IDs NEW para READY
            }
        }
  
        printf("      %d      ", time);
        for(int printar = 0 ; printar < ProgNum ; printar++){
        
            if(firstNonZeroPosition(printar, programas) < 0 ){
                printf("   EXIT     ");
            }else if(programas[printar][0] == time){
                printf("    NEW     ");
            }else if(programas[printar][0] > time){
                    printf("           ");
            }
            else if(firstNonZeroPosition(printar, programas) % 2 == 0){
                printf("  BLOCKED:%d   ",programas[printar][firstNonZeroPosition(printar, programas)]);
            }   
            else if(firstNonZeroPosition(printar, programas) % 2 == 1){
                if(printar == Front(ReadyQ)){
                    printf("  RUNNING:%d   ", programas[printar][firstNonZeroPosition(printar, programas)]);
                }else if(programas[printar][0] > time){
                    printf("           ");
                }
                else{
                    printf("   READY    ");
                }
            }
         
        }
        printf("\n");
        

        // RUNNING---->BLOCKED; RUNNING--->EXIT
        if (programas[Front(ReadyQ)][firstNonZeroPosition(Front(ReadyQ), programas)] == 1){ // ReadyQ -> &ID == 1 -> &ID == 0

            programas[Front(ReadyQ)][firstNonZeroPosition(Front(ReadyQ), programas)] --;
            if (firstNonZeroPosition(Front(ReadyQ), programas) < 0){
                Enqueue(Dequeue(ReadyQ), ExitQ);  // ready --> exit
            } else {
                Enqueue(Dequeue(ReadyQ), BlockedQ); // ou ready -->blocked
            }

        } else {

            programas[Front(ReadyQ)][firstNonZeroPosition(Front(ReadyQ), programas)] --;

        }

        // BLOCKED------>READY
        //  Se um proccesso tiver que ir para fila blocked na ciclo seguinte, altera a sua queue enquanto o valor e substituido decrementado
       /* if (programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)] == 1) { // BlockeQ -> ID == 1 -> ID == 0
           // printf("%d\n",programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)]);
            printf("\n");
            printQueue(BlockedQ);
            printf("\n");
            programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)]--;
           // printf("%d\n",programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)]);
            Enqueue(Dequeue(BlockedQ), ReadyQ);
        } else {
           // printf("%d\n",programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)]);
            programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)]--;
           // printf("%d\n",programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ), programas)]);
        }*/

        if(!IsEmptyQueue(BlockedQ)){
            if(programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ),programas)]>1){
                programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ),programas)]--;
            }else if(programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ),programas)] == 1){
                programas[Front(BlockedQ)][firstNonZeroPosition(Front(BlockedQ),programas)]--;
                int aux = Dequeue(BlockedQ);
                Enqueue(aux,ReadyQ);
            }
        }
        
        //printf("Time is: %d\n", time);
        //printf("Array principal -> %d\n", arrayIsEmpty(programas));

        time++;
        if(time>40){
            printf("QueueR: ");
            printQueue(ReadyQ);
            printf("\n BlockDQ:");
            printQueue(BlockedQ);
            printf("\nExitQ:");
            printQueue(ExitQ);
            break;
        }

    }
            printf("\n");
            printf("QueueReady: ");
            printQueue(ReadyQ);
            printf("\nQueueBlocked:");
            printQueue(BlockedQ);
            printf("\nQueueExit:");
            printQueue(ExitQ);
    return 0;
}

/* 
    printf("  instante |   proc1   |   proc2   |   proc3\n");

    "  BLOCKED   "
    "   READY    "
    "  RUNNING   "
    "    NEW     " 
    "   EXIT     "*/