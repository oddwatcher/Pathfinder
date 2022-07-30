#include "Net.h"
typedef struct path
{
    struct path *n;
    netnode *node;
} path; // path register the nodes on path on a reverse order head->tail,always insert the new node in the front;and rember to update the queue to point at it

typedef struct queue
{
    struct queue *n;
    struct queue *l;
    path *path;
    int plength;
} queue; // queue register the beginning of pathes ;

queue *nqueue(queue *head)
{
    queue *newpath = (queue *)malloc(sizeof(queue));
    newpath->n = head->n;
    head->n = newpath;
    newpath->path = NULL;
    return newpath;
}

queue *initqueue(char s, netnode *nethead)
{
    queue *qhead = (queue *)malloc(sizeof(queue));
    qhead->n = NULL;
    qhead->path = NULL;
    queue *f = nqueue(qhead);
    path *p = (path *)malloc(sizeof(path));
    netnode *S = findnet(s, nethead);
    if (S != NULL)
    {
        p->node = S;
        p->n = NULL;
        f->path = p;
    }
    else
    {
        printf("node not exist");
        return NULL;
    }
    f->n = NULL;
    f->plength = 1;
    p->n = NULL;
    return qhead;
}

int findinpath(netnode *t, path *p)
{
    while (p != NULL)
    {
        if (p->node == t)
        {
            return 1;
        }
        p = p->n;
    }
    return 0;
}

int findinedge(netnode *t, edge *h)
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
}

queue *enqueue(queue *p,netnode *enlist)
{
    queue *newqueue = (queue *)malloc(sizeof(queue));
    path *pa = p->path;
    path *P = (path *)malloc(sizeof(path));
    newqueue->l = NULL;
    newqueue->n = NULL;
    newqueue->plength = 0;
    newqueue->path = P;
    P->node = enlist;
    while (pa != NULL)
    {
        (newqueue->plength)++;
        P->n = (path *)malloc(sizeof(path));
        P = P->n;
        P->node = pa->node;
        pa = pa->n;
    }
    P->n = NULL;
    return newqueue;

} // copy the path of given queue and return the new address to connect to the rest of queue;


queue *growth(queue *t,netnode*goal) // grow the path of a given queue and return the new queue (the address of first branch )
{
    path *p = t->path;
    edge *e = (p->node)->edge;
    int i=0;
    while (e!=NULL)
    {
        i = i++;
        e = e->n;
    }
    if(i == 1){
        return NULL;
    }
    e = (p->node)->edge;
    
    while (e != NULL)
    {
        if (findinpath(e->node, p)==0)
        {
            temp = (path *)malloc(sizeof(path));
            temp->node = e->node;
        }
    }
}
