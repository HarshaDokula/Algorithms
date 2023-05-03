#include "heap.h"
#include "fileops.h"
#define rows 20000
#define cols 200


void insert(int *a, int n)
{
    int i = n;
    int item = a[n];

    while ((i > 1) && (a[(i / 2)] < item))
    {
        a[i] = a[i / 2];
        i /= 2;
    }
    a[i] = item;
}

// take array, root index, num of elements
void adjust(Node **a, int i, int n)
{

    int j = 2 * i;
    Node *item = a[i];
    while (j <= n)
    {
        if (j < n && (strcmp(a[j]->sen, a[j + 1]->sen) < 0)) // I think we just need to change int *a to a Node* type and the conditions that check for a[i] to n[i]->len.
        {
            j += 1;
        }

        if (strcmp(item->sen, a[j]->sen) > 0)
        {
            break;
        }
        a[j / 2] = a[j];

        j *= 2;
    }

    a[j / 2] = item;
}



void buildHeap(Node **nodes, int *n)
{
    for (int i = (*n) / 2; i > 0; i--)
    {
        adjust(nodes, i, *n);
    }
}


void heapSort(Node **nodes, int *n){
    for (int i=*n;i>0;i--){
        Node *t = nodes[i];
        nodes[i] = nodes[1];
        nodes[1] = t;
        adjust(nodes, 1, i-1);
    }
}

char *maxe(Node **nodes, int *n)
{
    char *se = "\0";
    if (n == 0)
    {
        return se;
    }
    se = nodes[1]->sen;
    nodes[1] = nodes[*n];
    *n -= 1;
    adjust(nodes, 1, *n);
    return se;
}

int main(int args,char *filename[])
{

    // printf("filename %s\n", filename[1]);
    char ar[rows][cols];

    // ==================reading lines from the input text file======================
    int rows_in_file = readLines(ar, filename[1]) + 1;
    // printf("lines in the file -> %d\n",rows_in_file);
    // =============================initialising nodes=====================================

    Node *nodes[rows];
    for (int i = 0; i < rows_in_file; i++)
    {
        // printf("%s\n", ar[i]);
        nodes[i + 1] = aloc;
        init_node(nodes[i + 1], ar[i]);
        // print_node(nodes[i + 1]);
    }
        buildHeap(nodes, &rows_in_file);

    // for (int i = 1; i <= rows_in_file; i++)
    // {
    //     print_node(nodes[i]);
    // }

    // ===========================sorting the nodes==================================
    heapSort(nodes, &rows_in_file);

    //===========copying the data to char array to output to the output file===============================
    for (int i = 1; i <= rows_in_file; i++)
    {
        // snprintf(ar[i - 1], cols, "%s", nodes[i]->sen);
        strcpy(ar[i-1],nodes[i]->sen);
    }
    for (int i = 0; i <rows_in_file; i++)
    {
        printf("%s", ar[i]);
        if(i!=rows_in_file-1){
            printf("\n");
        }
    }
//  =============================writing lines to a text file============================
    writeLines(ar, "output_text.txt", rows_in_file);
}

