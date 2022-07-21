#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    char data;
    struct edge *n;
} edge;

typedef struct
{
    char data;
    netnode *l;
    netnode *r;
    edge *head;
} netnode;

edge *addedge(char data, edge *n)
{
    edge *newnode = (edge *)malloc(sizeof(edge));
    newnode->data = data;
    newnode->n = n;
    return newnode;
}

netnode *addnetnode(char data, netnode *l, netnode *r)
{
    netnode *newnode = (netnode *)malloc(sizeof(netnode));
    newnode->data = data;
    newnode->l = l;
    newnode->r = r;
    return newnode;
}

edge *appendedge(edge *R, char din)
{
    edge *temp = addedge(din,NULL);
    R->n = temp;
    return temp;
}

netnode *appendnetnode(netnode *R, char din)
{
    netnode *temp = addnetnode(din, R, R->r);
    R->l = temp;
    if (R->r != NULL)
    {
        (R->r)->l = temp;
    }
    return temp;
}

int findedge(char t, edge *head)
{
    while (head->n != NULL)
    {
        head = head->n;
        if (head->data == t)
        {
            return 1;
        }
    }
    return 0;
}

netnode * findnetnode(char t, netnode *head)
{
    while (head->r != NULL)
    {
        head = head->r;
        if (head->data == t)
        {
            return head;
        }
    }
    return NULL;
}

void output(edge *p)
{
    do
    {
        printf("%d,%p,%p,%p\n", p->data, p->n);
        p = p->n;
    } while (p != NULL);
}

netnode *netinit()
{
    netnode *N = addnetnode('0', NULL, NULL);
    char C = '0';
    int i = 0;
    printf("Enter all nodes,end with !\n");
    while (C != '!')
    {
        scanf("%c", &C);
        appendnetnode(N, C);
        i++;
    }
    printf("Total : %d", i);
    return N;
}

int initEDGE(netnode *N){
    char C = '1';
    netnode *temp = N;
    edge *p = NULL;
    netnode *f = NULL;
    while (temp->r!=NULL)
    {
        temp = temp->r;
        printf("edge:%c,connected edge :",temp->data);
        p = temp->head;
        while (p->l!=NULL)
        {
            printf("%c,",p->data);
            p = p->l;
        }
        printf("\n input new edge connected to %c end with 0",temp->data);
        while (C != '0')
        {
            scanf("%c",&C);
            netnode *f = findnetnode(C,N);
            if(f!=NULL){
                 appendedge(temp->head,C);
                 appendedge(f->head,temp->data);
            }else{
                printf("node not decleared\n");
            }
           
        }
        

        
        
    }
    
}
