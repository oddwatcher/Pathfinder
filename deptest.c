#include"queue.h"
int main(){
    netnode *head = initnetnode();
    printf("%d\n", (int)head->name);
    printf("total edges:%d\n", initedge(head));
    char a, b;
    scanf("%c,%c", &a, &b);
    netnode *A = findnet(a, head);
    netnode *B = findnet(b, head);
    queue * qhead = (queue*)malloc(sizeof(queue));
    qhead->r = depfirst(A,B);
    outputqueue(qhead);
}