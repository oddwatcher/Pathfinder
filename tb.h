#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *l;
    struct node *r;
} node;

typedef struct
{
    char data;
    netnode *l;
    netnode *r;
    node *head;
} netnode;

node *addnode(char data, node *l, node *r)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->l = l;
    newnode->r = r;
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

node *appendnode(node *R, char din)
{
    node *temp = addnode(din, R, R->r);
    R->l = temp;
    if (R->r != NULL)
    {
        (R->r)->l = temp;
    }
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

void deletenode(node *p)
{
    if (p->l != NULL)
    {
        (p->l)->r = p->r;
    }
    if (p->r != NULL)
    {
        (p->r)->l = p->l;
    }
    printf("Deleting:%p:%d\n", p, p->data);
    free(p);
}

node *getright(node *p)
{
    while (p->r != NULL)
    {
        p = p->r;
    }
    return p;
}

node *getleft(node *p)
{
    while (p->l != NULL)
    {
        p = p->l;
    }
    return p;
}

int findnode(char t, node *head)
{
    head = getleft(head);
    while (head->r != NULL)
    {
        head = head->r;
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

void output(node *p)
{
    p = getleft(p);
    do
    {
        printf("%d,%p,%p,%p\n", p->data, p->l, p, p->r);
        p = p->r;
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

int EDGE(netnode *N){
    char C = '1';
    netnode *temp = N;
    node *p = NULL;
    netnode *f = NULL;
    while (temp->r!=NULL)
    {
        temp = temp->r;
        printf("Node:%c,connected node :",temp->data);
        p = temp->head;
        while (p->l!=NULL)
        {
            printf("%c,",p->data);
            p = p->l;
        }
        printf("\n input new node connected to %c end with 0",temp->data);
        while (C != '0')
        {
            scanf("%c",&C);
            netnode *f = findnetnode(C,N);
            if(f!=NULL){
                 appendnode(temp->head,C);
                 appendnode(f->head,temp->data);
            }else{
                printf("node not decleared\n");
            }
           
        }
        

        
        
    }
    
}
