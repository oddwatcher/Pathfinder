#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    char data;
    struct edge *n;
} edge;

typedef struct netnode
{
    char name;
    struct netnode *l;
    struct netnode *r;
    edge *head;
} netnode;


int initnetnode(netnode *nethead) // generates node list without edges a nethead which indicates the beginnning of the net
{
    int p;
    char c;
    netnode *newnode;
    printf("number of nodes:");
    scanf("%d", &p);
    fflush(stdin);
    printf("enter node name with a signal char\n");
    for (int i = p; i > 0;  i--)
    {
        newnode = (netnode *)malloc(sizeof(netnode));
        scanf("%c", &c);
        fflush(stdin);
        newnode->name = c;
        newnode->l = nethead;
        newnode->r = nethead->r;
        newnode->head = NULL;
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
    printf("connected nodes of %c :\n", target->name);
    int i =0;
    while (1)
    {
        if (p != NULL)
        {
            printf("%c\n", p->data);
            p = p->n;
            i++;
        }
        else
        {   
            if(i!=0){
                printf("total %d connected\n",i);
            }else{
                printf("no connected edges yet\n");
            }
            break;
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
                addedge(current->name,t);
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

