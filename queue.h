#include"tb.h"
typedef struct path
{
    struct path *n;
    netnode *data;
    int altflag;
} path; // qmenbers register the nodes on path on a reverse order head->tail->...->start,always insert the new node after head

typedef struct queue
{
    struct queue *n;
    path *head;
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
    path *p = (path *)malloc(sizeof(path));
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

