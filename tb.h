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

int initnetnode(char data, netnode *nethead) // generates node list without edges a nethead which indicates the beginnning of the net
{
    int p;
    netnode *newnode;
    printf("number of nodes:");
    scanf("%d", &p);
    for (int i = p; i > 0; i--)
    {
        newnode = (netnode *)malloc(sizeof(netnode));
        scanf("%c\n", newnode->name);
        newnode->l = nethead;
        newnode->r = nethead->r;
        if (nethead->r != NULL)
        {
            (nethead->r)->l = newnode;
        }
        nethead->r = newnode;
    }
    return p; // number of nodes
}

netnode *findnet(char name, netnode *head) // find the address of netnode by name
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

void printedge(netnode *target)
{
    edge *p = target->head;
    printf("connected nodes of  %c", target->name);
    while (1)
    {
        if (p != NULL)
        {
            printf("%c", p->data);
            p = p->n;
        }
        else
        {
            printf("end of edge\n");
        }
    }
}

edge* addedge(char i, netnode *t)
{
    edge *newedge = (edge *)malloc(sizeof(edge));
    newedge->data = i;
    newedge->n = t->head;
    t->head = newedge;
    return newedge;
}
int initedge(netnode *nethead) // add edge to netnode netnode->head,and search for related node to add edge edge are oneway chain ;head contains data
{
    int edgemount=0;
    netnode *current = nethead->r;
    while (current != NULL)
    {
        printf("enter connected nodes of %c ,endwith 0\n", current->name);
        printedge(current);
        while (1)
        {
            char i;
            netnode *t;
            scanf("%c", &i);
            t = findnet(i, nethead);
            if (t != NULL)
            {
                addedge(i,t);
                addedge(i,current);
                edgemount++;
            }else{
                printedge(current);
                break;
            }

        }
        current = current->r;
    }
    return edgemount;
}

