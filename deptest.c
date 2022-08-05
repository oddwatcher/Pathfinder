#include "queue.h"
int main()
{
    netnode *head = initnetnode();
    printf("%d\n", (int)head->name);
    printf("total edges:%d\n", initedge(head));
    char a, b;
    while (1)
    {
        fflush(stdin);
        scanf("%c,%c", &a, &b);
        netnode *A = findnet(a, head);
        netnode *B = findnet(b, head);
        if ((A == NULL) || (B == NULL))
        {
            printf("node not exist\n");
        }
        else
        {
            queue *qhead = (queue *)malloc(sizeof(queue));
            qhead->r = depfirst(A, B);
            (qhead->r)->r = NULL;
            outputqueue(qhead);
            printf("purging flags:%d\n", flagpurge(head));
            qhead->r = brefirst(A, B);
            (qhead->r)->r = NULL;
            outputqueue(qhead);
            printf("purging flags:%d\n", flagpurge(head));
        }
    }
}