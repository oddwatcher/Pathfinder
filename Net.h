#include <stdio.h>
#include <stdlib.h>
#define Net
typedef struct edge
{
    struct edge *n;
    struct netnode *node;
} edge;

typedef struct netnode
{
    char name;
    struct netnode *l;
    struct netnode *r;
    int flag;
    edge *edge;
} netnode;

netnode *initnetnode() //verified
{// generates node list without edges a nethead which indicates the beginnning of the net
    int p;
    char c;
    netnode *newnode;
    netnode *nethead = (netnode *)malloc(sizeof(netnode));
    nethead->edge = NULL;
    nethead->r = NULL;
    nethead->name = '1';
    nethead->l = NULL;
    printf("number of nodes:");
    scanf("%d", &p);
    fflush(stdin);
    printf("enter node name with a signal char\n");
    for (int i = p; i > 0; i--)
    {
        newnode = (netnode *)malloc(sizeof(netnode));
        scanf("%c", &c);
        fflush(stdin);
        newnode->name = c;
        newnode->l = nethead;
        newnode->r = nethead->r;
        newnode->edge = NULL;
        newnode->flag = 0;
        if (nethead->r != NULL)
        {
            (nethead->r)->l = newnode;
        }
        nethead->r = newnode;
    }
    nethead->name = (char)p;
    return nethead;
}

netnode *findnet(char name, netnode *head) //verified
{// find the address of netnode by name
    for (netnode *p = head->r; p != NULL; p = p->r)
    {
        if (p->name == name)
        {
            return p;
        }
    }
    return NULL;
}

int findinedge(netnode *t, edge *h)//verified
{
    while (h != NULL)
    {
        if ((h->node) == t)
        {
            return 1;
        }
        h = h->n;
    }
    return 0;
}//verified

void printedge(netnode *target)//verified
{
    edge *p = target->edge;
    printf("connected nodes of %c :\n", target->name);
    int i = 0;
    while (1)
    {
        if (p != NULL)
        {
            printf("%c\n", (p->node)->name);
            p = p->n;
            i++;
        }
        else
        {
            if (i != 0)
            {
                printf("total %d connected\n", i);
            }
            else
            {
                printf("no connected edges yet\n");
            }
            break;
        }
    }
}//verified

edge *addedge(netnode *i, netnode *t)//verified
{
    edge *newedge = (edge *)malloc(sizeof(edge));
    newedge->node = i;
    newedge->n = t->edge;
    t->edge = newedge;
    return newedge;
}//verified
int initedge(netnode *nethead) //verified
{// add edge to netnode netnode->head,and search for related node to add edge edge are oneway chain ;head contains data
    int edgemount = 0;
    netnode *current = nethead->r;
    while (current != NULL)
    {
        printf("enter connected nodes of %c ,already ", current->name);
        printedge(current);
        while (1)
        {
            char i;
            netnode *t;
            scanf("%c", &i);
            fflush(stdin);
            t = findnet(i, nethead);
            if (t != NULL)
            {
                addedge(current, t);
                addedge(t, current);
                edgemount++;
            }
            else
            {
                printedge(current);
                break;
            }
        }
        current = current->r;
    }
    return edgemount;
}//verified
