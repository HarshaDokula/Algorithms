#include"huffman.h"
#include<limits.h>
#define aloc (Node*)malloc(sizeof(Node))
#define charcount 127

// initializes a Node* type memory block with freq left child, right child and data


void init_node(Node *node, int f, int L, int R, char c){
    node->freq = f;
    node->data = c;
    snprintf(node->source_data, sizeof(node->source_data),"%c",node->data);
    node->left = L;
    node->right = R;
    node->isUsed = false;
}


bool isLeaf(Node *node){
    if(node->left==-1 && node->right==-1){
        return true;
    }
    return false;
}
// checks if the required char is in the source_data of the node so we can decide which subtree to traverse
bool isReachable(char c, char arr[], size_t size) {
    for (size_t i = 0; i < size+1; i++) {
        if (arr[i] == c) {
            return true;
        }
    }
    return false;
}

// sorts the Node* pointers array in ascending order.
void sort_array(Node **nodes,size_t low_bound, size_t up_bound){
    for(size_t i = low_bound; i<up_bound;i++){
        for(size_t j = i+1; j<up_bound;j++){
            if(nodes[i]!=NULL){

                if(nodes[i]->freq>nodes[j]->freq){
                    Node *temp = nodes[i];
                    nodes[i] = nodes[j];
                    nodes[j] = temp;
                }
            }
        }
    }
}

// prints the data of the node.
void print_node(Node *n){
    printf("node block\n++++++++++\n");
    printf("freq: %d\ndata: %c\n\nsource_data: %s\n is used: %d\n",n->freq,n->data,n->source_data,n->isUsed);
    printf("++++++++++\n\n");
}

int getMinNode(Node **nodes, size_t up_upbound){
    int min = INT_MAX;
    size_t minidx = 0;
    for(size_t i=0;i<up_upbound;i++){
        if(!nodes[i]->isUsed){
            if(nodes[i]->freq < min){
                min = nodes[i]->freq;
                minidx = i;
            }
        }
    }
    return minidx;
}


void pack_zero(unsigned char *c) {
   *c = *c << 1;
}

void pack_one(unsigned char *c) {
   *c = *c << 1;
   *c |= 1;
}

void itob(unsigned char asci, char *bin) {
   unsigned char tb[9] = {0};
   for(int i = 7; i >= 0; i--) {
      unsigned char bb = (asci >> i) & 1;
      if(bb){
         tb[7-i] = '1';
      }else{
         tb[7-i] = '0';

      }
   }
   snprintf(bin,9,"%s",tb);
}
