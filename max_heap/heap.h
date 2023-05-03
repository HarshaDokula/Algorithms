#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define aloc (Node *)malloc(sizeof(Node))

typedef struct Node
{
    int len;
    char sen[2046];
} Node;

void init_node(Node *n, char s[])
{
    // printf("initializing the node \n\n");
    // n->len = snprintf(n->sen, sizeof(n->sen), "%s", s);
    strcpy(n->sen,s);
    // printf("sen copied\n");
    n->len = strlen(s);
}

void print_node(Node *n)
{
    printf("===================\n");
    printf("len -> %d\n", n->len);
    printf("sentence -> %s\n", n->sen);
    printf("===================\n\n");
}
