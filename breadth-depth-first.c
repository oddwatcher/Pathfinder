#include"Net.h"
#include"queue.h"
int main(){
    netnode *head = initnetnode();
    printf("%d\n",(int)head->name);
    printf("total edges:%d\n",initedge(head));
    printf("enter two node to perform search:");
    char a,b;
    scanf("%c,%c",&a,&b);
    printf ("looking for path from %c to %c :\n",a,b);
    queue * ans = depfirst(findnet(a,head),findnet(b,head));
    path * o = ans->path;
    while (o!=NULL)
    {
        printf("%c->",(o->node)->name);
    }
    printf("Done");
}