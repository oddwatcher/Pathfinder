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

netnode *initnetnode() // generates node list without edges a nethead which indicates the beginnning of the net
{
    int p;
    char c;
    netnode *newnode;
    netnode *nethead = (netnode *)malloc(sizeof(netnode));
    nethead->head = NULL;
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
        newnode->head = NULL;
        if (nethead->r != NULL)
        {
            (nethead->r)->l = newnode;
        }
        nethead->r = newnode;
    }
    nethead->name = (char)p;
    return nethead;
}

netnode *findnet(char name, netnode *head) // find the address of netnode by name
{
    for (netnode *p = head->r; p != NULL; p = p->r)
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
    int i = 0;
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
}

edge *addedge(char i, netnode *t)
{
    edge *newedge = (edge *)malloc(sizeof(edge));
    newedge->data = i;
    newedge->n = t->head;
    t->head = newedge;
    return newedge;
}
int initedge(netnode *nethead) // add edge to netnode netnode->head,and search for related node to add edge edge are oneway chain ;head contains data
{
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
                addedge(current->name, t);
                addedge(i, current);
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
}

typedef struct qmember
{
    struct qmember *n;
    netnode *data;
    int altflag;
} qmember; // qmenbers register the nodes on path on a reverse order head->tail->...->start,always insert the new node after head

typedef struct queue
{
    struct queue *n;
    qmember *head;
    int legth;
} queue;

queue *nqueue(queue *head)
{
    queue *newpath = (queue *)malloc(sizeof(queue));
    newpath->n = head->n;
    head->n = newpath;
    newpath->head = NULL;
    newpath->legth = 0;
    return newpath;
}

queue *queuen(queue *head)
{
    while (head->n != NULL)
    {
        head = head->n; // get tail of queue
    }

    queue *newpath = (queue *)malloc(sizeof(queue));
    head->n = newpath;
    newpath->n = NULL;
    newpath->head = NULL;
    return newpath;
}

queue *initqueue(char s, netnode *nethead)
{
    queue *qhead = (queue *)malloc(sizeof(queue));
    qhead->n = NULL;
    queue *f = nqueue(qhead);
    qmember *p = (qmember *)malloc(sizeof(qmember));
    netnode *S = findnet(s, nethead);
    if (S != NULL)
    {
        p->data = S;
        p->n = NULL;
        f->head = p;
    }
    else
    {
        printf("node not exist");
        return NULL;
    }
    return qhead;
}

int growth(queue *q)
{
    edge *eg = ((q->head)->data)->head;
    qmember *path = q->head;
    int flag;
    while (eg != NULL)
    {
        while (path != NULL)
        {
            flag = 0;
            if (eg->data != (path->data)->name)
            {
                path = path->n;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
        }
    }
}
