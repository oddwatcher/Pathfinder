#ifndef Net
#include "Net.h"
#endif
typedef struct path
{
    struct path *r;
    netnode *node;
} path; // path register the nodes on path on a reverse order head->tail,always insert the new node in the front;and rember to update the queue to point at it

typedef struct queue
{
    struct queue *r;
    struct queue *l;
    path *path;
    int plength;
} queue; // queue register the beginning of pathes ;

queue *nqueue(queue *head)
{
    queue *newpath = (queue *)malloc(sizeof(queue));
    newpath->r = head->r;
    head->r = newpath;
    newpath->path = NULL;
    return newpath;
}

queue *initqueue(netnode *S)
{ // gives you a head to your queue and first queue is enlisted with S
    queue *qhead = (queue *)malloc(sizeof(queue));
    qhead->r = NULL;
    qhead->l = NULL;
    qhead->path = NULL;
    path *p = (path *)malloc(sizeof(path));
    if (S != NULL)
    {
        p->node = S;
        p->r = NULL;
        qhead->path = p;
    }
    else
    {
        printf("node not exist");
        return NULL;
    }
    qhead->plength = 1;
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
        p = p->r;
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

queue *enqueue(queue *p, netnode *enlist)
{
    queue *newqueue = (queue *)malloc(sizeof(queue));
    path *pa = p->path;
    path *P = (path *)malloc(sizeof(path));
    newqueue->l = NULL;
    newqueue->r = NULL;
    newqueue->plength = 0;
    newqueue->path = P;
    P->node = enlist;
    while (pa != NULL)
    {
        (newqueue->plength)++;
        P->r = (path *)malloc(sizeof(path));
        P = P->r;
        P->node = pa->node;
        pa = pa->r;
    }
    P->r = NULL;
    return newqueue;

} // copy the path of given queue and return the new address to connect to the rest of queue;

queue *growth(queue *t, netnode *G) // grow the path of a given queue and return the new queue (the address of first branch ) if the branch is at end ,it return NULL
{
    path *p = t->path;
    edge *e = (p->node)->edge;
    queue *head = (queue *)malloc(sizeof(queue)); // holds grown queues
    head->l = NULL;
    head->r = NULL;
    queue *temp = NULL; // temp to hold just generated new queue address
    int i = 0;          // counter for leaf check

    (p->node)->flag = 1; // set the current node as extended

    while (e != NULL) // tell if this node is at leaf
    {
        i = i++;
        e = e->n;
    }

    if (i <= 1) // if node is already at leaf it is grown
    {
        return NULL;
    }

    e = (p->node)->edge; // reset edge indicator

    while (e != NULL)
    {                                                                // goes over the edges of last node on path and not going back or go to extended ones use enqueue to get the queue and attach it behind the head
        if ((findinpath(e->node, p) == 0) && ((e->node)->flag == 0)) // use of extended list
        {
            temp = enqueue(t, e->node); // attach the new queue to head
            temp->l = head;
            temp->r = head->r;
            if (head->r != NULL)
            {
                (head->r)->l = temp;
            }
            head->r = temp;
        }
        if (G == e->node)
        {
            break;
        }
        e = e->n;
    }
    temp = head->r; // remove head
    temp->l = NULL;
    free(head);
    return temp; // temp is at the leftest(head) of queue only use its left to attach
}

queue *depfirst(netnode *S, netnode *G)
{
    queue *Q = initqueue(S);
    queue *temp = NULL;
    while (1)
    {
        temp = growth(Q, G);
        Q->r = temp;
        temp->l = Q;
        while (Q->r != NULL)
        {
            if ((Q->path)->node == G)
            {
                return Q;
            }
            Q = Q->r;
        }
    }
}