#ifndef Net
#include "Net.h"
#endif
typedef struct path
{
    struct path *n;
    netnode *node;
} path; // path register the nodes on path on a reverse order head->tail,always insert the new node in the front;and rember to update the queue to point at it

typedef struct queue
{
    struct queue *r;
    struct queue *l;
    path *path;
    int plength;
} queue; // queue register the beginning of pathes ;

queue *initqueue(netnode *S) // verified
{                            // gives you a head to your queue and first queue is enlisted with S
    queue *qhead = (queue *)malloc(sizeof(queue));
    qhead->r = NULL;
    qhead->l = NULL;
    qhead->plength = 1;
    path *p = (path *)malloc(sizeof(path));
    p->node = S;
    p->n = NULL;
    qhead->path = p;
    return qhead;
}

int findinpath(netnode *t, path *p) // verified
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

queue *enqueue(queue *t, netnode *enlist) // verified
{
    queue *newqueue = (queue *)malloc(sizeof(queue));
    path *pt = t->path;
    path *P = (path *)malloc(sizeof(path));
    newqueue->l = NULL;
    newqueue->r = NULL;
    newqueue->plength = 0;
    newqueue->path = P;
    P->node = enlist;
    while (pt != NULL)
    {
        (newqueue->plength)++;
        P->n = (path *)malloc(sizeof(path));
        P = P->n;
        P->node = pt->node;
        pt = pt->n;
    }
    P->n = NULL;
    return newqueue;

} // copy the path of given queue and return the new address to connect to the rest of queue;

void outputqueue(queue *head)//verified
{
    int i = 1;
    path *p;
    while (head != NULL)
    {
        printf("queue:%d,paths:", i);
        p = head->path;
        while (p != NULL)
        {
            printf("->%c", (p->node)->name);
            p = p->n;
        }
        head = head->l;
    }
    printf("\n");
}

queue *growth(queue *t, netnode *G) // grow the path of a given queue and return the new queue (the address of first branch ) if the branch is at end ,it return NULL
{
    path *p = t->path;
    edge *e = (p->node)->edge;
    queue *head = (queue *)malloc(sizeof(queue)); // holds grown queues
    head->l = NULL;
    head->r = NULL;
    head->path = NULL;
    head->plength=0;
    queue *temp = NULL; // temp to hold just generated new queue address
    int i = 0;          // counter for leaf check

    (p->node)->flag = 1; // set the current node as extended

    while (e != NULL) // tell if this node is at leaf
    {
        i++;
        e = e->n;
    }

    if (i == 1) // if node is already at leaf it is grown
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
    free(head);
    temp->l = NULL;
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