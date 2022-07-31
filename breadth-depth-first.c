#include"Net.h"
#include"queue.h"
int main(){
    netnode *head = initnetnode();
    printf("%d\n",(int)head->name);
    printf("total edges:%d\n",initedge(head));
    char a,b;
    scanf("%c,%c",&a,&b);
    netnode *A = findnet(a,head);
    netnode*B = findnet(b,head);
    queue* qhead = initqueue(A);
    outputqueue(qhead);
    queue* temp = enqueue(qhead,B);
    printf("%d\n",findinpath(A,temp->path));
    outputqueue(temp);
    temp = growth(qhead,B);
    if(temp == NULL){
        printf("temp is NULL");
    }
    outputqueue(temp);
}