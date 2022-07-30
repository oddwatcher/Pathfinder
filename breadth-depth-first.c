#include"Net.h"
#include"queue.h"
int main(){
    netnode *head = initnetnode();
    printf("%d\n",(int)head->name);
    printf("total edges:%d\n",initedge(head));
    char a,b;
    scanf("%c,%c",&a,&b);
    queue* qhead = initqueue(findnet(a,head));
    outputqueue(qhead);
    queue* temp = enqueue(qhead,findnet(b,head));
    printf("%d",findinpath(findnet(a,head),temp->path));
    outputqueue(temp);
}