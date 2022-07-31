#include "queue.h"
int main()
{
    netnode *head = initnetnode();
    printf("%d\n", (int)head->name);
    printf("total edges:%d\n", initedge(head));
    char a, b;
    scanf("%c,%c", &a, &b);
    netnode *A = findnet(a, head);
    netnode *B = findnet(b, head);
    queue *qhead = initqueue(A);
    //printf("test queue init:\n");
    //outputqueue(qhead);
    queue *temp = enqueue(qhead->r, B);
   // printf("test queue findinpath:\n");
    //printf("%d\n", findinpath(A, temp->path));
    //printf("test queue enqueue:\n");
    //qhead->r = temp;
   // temp->l = qhead;
    //outputqueue(qhead);
    //printf("test queue growth:\n");
    //temp = growth(temp, B);
    //if (temp == NULL)
    //{
       // printf("temp is NULL");
    //}
    //queue *tail = qhead;
    //while (tail->r != NULL)
    //{
     //   tail = tail->r;
    //}
    //if (temp != tail)
    //{
    //    tail->r = temp;
    //    temp->l = tail;
    //}
   // outputqueue(qhead);
    //printf("test queue delete:\n");
   // delqueue(temp);
   // outputqueue(qhead);
    fflush(stdin);
    scanf("%c,%c",&a,&b);
    A = findnet(a, head);
    B = findnet(b, head);
    printf("test queue depfirst:\n");
    temp = depfirst(A,B);
    qhead->r =temp;
    temp->r = NULL;
    outputqueue(qhead);
}