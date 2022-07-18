#include<stdio.h>
#include<stdlib.h>
typedef struct {
    node * left;
    node * right;
    char data;
} node;

node * chain_init(){
    node*head = (node*)malloc(sizeof(node));
    return head;
}