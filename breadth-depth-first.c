#include"Net.h"

int main(){
    netnode *head = initnetnode();
    printf("%d\n",(int)head->name);
    printf("total edges:%d\n",initedge(head));
    printf("enter two node to perform search:");
    char a,b;
    scanf("%c,%c",&a,&b);
     
}