#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define charcount 127
#define Nodes_size  (charcount*2)-1

typedef struct node{
    int freq;
    int left;
    int right;
    char source_data[4096];
    char data;
    bool isUsed;
}Node;


Node *huffmanTree(Node **nodes,size_t low_bound, size_t up_bound);
void encode(Node *root, Node **nodes, char *message, char *code);
void decode(Node * root, Node **nodes,char *code, char *decoded_msg,int code_len);
