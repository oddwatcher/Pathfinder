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
            outputqueue(depfirst(A, B));
            printf("purging flags:%d\n", flagpurge(head));
            outputqueue(brefirst(A, B));
            printf("purging flags:%d\n", flagpurge(head));
        }
    }
}