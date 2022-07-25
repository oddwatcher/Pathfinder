#include"tb.h"

int main(){
    netnode* head = (netnode*)malloc(sizeof(netnode));
    head->head=NULL;
    head->l=NULL;
    head->r=NULL;
    head->name=1;
    printf("%d\n",initnetnode(head));
    printf("%d\n",initedge(head));
}