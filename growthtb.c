#include "queue.h"
int main()
{
    netnode *head = initnetnode();
    printf("total egdes:%d\n", initedge(head));

    while (1)
    {
        char a, b;
        printf("input nodes:");
        scanf("%c,%c", &a, &b);
        netnode *A = findnet(a, head);
        netnode *B = findnet(b, head);
        queue *P = initqueue(A);
        outputqueue(P);
        queue *temp = growth(P->r, B);
        P->r = temp;
        outputqueue(P);
        flagpurge(head);
    }
}