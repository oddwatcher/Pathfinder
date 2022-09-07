#ifndef Net
#include "Net.h"
#endif
typedef struct path
{
    struct path *n;
    int w;
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
    queue *head = (queue *)malloc(sizeof(queue));
    queue *qhead = (queue *)malloc(sizeof(queue));
    head->l = NULL;
    head->path = NULL;
    head->plength = 0;
    head->r = qhead;
    qhead->l = head;
    qhead->r = NULL;
    qhead->plength = 1;
    path *p = (path *)malloc(sizeof(path));
    p->node = S;
    p->n = NULL;
    qhead->path = p;
    return head;
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

void outputqueue(queue *head) // verified
{                             // give the head of a queue at rightest,will print every queue and the path it had
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
        head = head->r;
        i++;
        printf("\n");
    }
}

queue *growth(queue *t, netnode *G) // verified
{                                   // grow the path of a given queue and return the new queue (the address of first branch ) if the branch is at end ,it return t
    path *p = t->path;
    edge *e = (p->node)->edge;
    queue head; // holds grown queues
    head.l = NULL;
    head.r = NULL;
    head.path = NULL;
    head.plength = 0;
    queue *temp = NULL;       // temp to hold just generated new queue address
    int i = 0;                // counter for growth check
    if ((p->node)->flag == 1) // if the current queue is already growned by else, do nothing
    {
        return t;
    }

    (p->node)->flag = 1; // set the current node as extended

    while (e != NULL)
    {                                                                // goes over the edges of last node on path and not going back or go to extended ones use enqueue to get the queue and attach it behind the head
        if ((findinpath(e->node, p) == 0) && ((e->node)->flag == 0)) // use of extended list
        {
            temp = enqueue(t, e->node); // generates new queue
            temp->l = &head;            // attach the new queue to head
            temp->r = head.r;
            if (head.r != NULL)
            {
                (head.r)->l = temp;
            }
            head.r = temp;
            i++;
        }

        if (G == e->node) // if reachs goal stop at once
        {
            break;
        }
        e = e->n;
    }
    if (i != 0) // if there is a new branch grown
    {
        temp->l = NULL;
        return temp; // temp is at the leftest(head) of queue only use its left to attach
    }
    else
    {
        return t; // if all edges are grown by else nothing will be grown so do nothing
    }
}

queue *delqueue(queue *Q) // verified
{                         // remove given queue and return right or left of it if its not NULL
    queue *t;
    if (Q->l != NULL)
    {
        (Q->l)->r = Q->r;
        t = Q->l;
    }
    if (Q->r != NULL)
    {
        (Q->r)->l = Q->l;
        t = Q->r;
    }
    free(Q);
    return t;
}

queue *depfirst(netnode *S, netnode *G) // verified
{
    queue *P = initqueue(S); // head to queue and at rightest
    queue *temp = NULL;
    queue *Q = P->r;
    while (1)
    {
        if ((Q->path)->node == G) // check if current path reaches goal
        {
            return Q;
        }
        if (((Q->path)->node)->flag == 1) // see if current queue is already extended by else
        {
            Q = delqueue(Q); // if is grown remove this queue
        }
        else
        {
            temp = growth(Q, G); // grow the queue
            if (temp == Q)       // if not growable
            {
                Q = delqueue(Q); // delete queue
                if (Q == P)      // if no more queue is avaliable
                {
                    printf("No Path\n"); // exit
                    return NULL;
                }
            }
            else // if the queue is growable
            {
                Q = delqueue(Q); // remove growed queue
                Q->r = temp;     // attach new branches to the tree
                temp->l = Q;
                while (Q->r != NULL) // move Q to the rightest of queues
                {
                    Q = Q->r;
                }
            }
        }
    }
}

queue *brefirst(netnode *S, netnode *G) //verified
{
    queue *P = initqueue(S); // head to queue and at rightest
    queue *temp = NULL;
    queue *Q = NULL;
    queue *tail = NULL;
    while (1)
    {
        Q = P->r;
        if ((Q->path)->node == G) // check if current path reaches goal
        {
            return Q;
        }
        if (((Q->path)->node)->flag == 1) // see if current queue is already extended by else
        {
            Q = delqueue(Q); // if is grown remove this queue
            if (P->r == NULL)
            {                          // if no more queue is avaliable
                printf("No Path 0\n"); // exit
                return NULL;
            }
        }
        else
        {
            temp = growth(Q, G); // grow the queue

            if (temp == Q) // if not growable
            {
                Q = delqueue(Q);  // delete queue
                if (P->r == NULL) // if no more queue is avaliable
                {
                    printf("No Path 1\n"); // exit
                    return NULL;
                }
            }
            else // if the queue is growable
            {
                tail = P;               // maintain tail
                while (tail->r != NULL) // move tail to the rightest of queues
                {
                    tail = tail->r;
                }
                tail->r = temp; // attach new branches to the tree
                temp->l = tail;
                delqueue(Q); // remove growed queue
            }
        }
    }
}

int pathw (path* p ){

}

queue *Apath(netnode *S, netnode *G)
{
    queue *head = initqueue(S);
    
}