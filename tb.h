#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char data;
    edge *n;
} edge;

typedef struct
{
    char name;
    netnode *l;
    netnode *r;
    edge *head;
} netnode;

int initnetnode(char data, netnode *nethead) //generates the node list without edges with a given nethead which indicates the beginnning of the net
{
    int p;
    netnode *newnode;
    printf("number of nodes:");
    scanf("%d", &p);
    for (int i =p ; i > 0; i--)
    {
        newnode = (netnode *)malloc(sizeof(netnode));
        scanf("%c\n",newnode->name);
        newnode->l = nethead;
        newnode->r = nethead->r;
        if(nethead->r!=NULL){
            (nethead->r)->l =newnode;
        }
        nethead->r = newnode;
    }
    return p;//number of nodes

}

netnode *findnet(char name, netnode *head)
{
    for (netnode *p = head; p != NULL; p = p->r)
    {
        if (p->name == name)
        {
            return p;
        }
    }
    return NULL;
}

edge *addedge(char data, netnode *nethead)
{
    char e;
    scanf("%c", &e);
    netnode *node = findnet(e, nethead);
    edge *newnode = (edge *)malloc(sizeof(edge));
    newnode->data = data;
    newnode->n = (node->head)->n;
    node->head = newnode;
    return newnode;
}

void output(edge *p)
{
    do
    {
        printf("%d,%p,%p,%p\n", p->data, p->n);
        p = p->n;
    } while (p != NULL);
}
