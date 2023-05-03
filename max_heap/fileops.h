#include <stdio.h>
#include <stdlib.h>
#define cols 200
#define LINES 20000

int readLines(char arr[][cols], char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("check filename properly");
        return -1;
    }

    int ch = fgetc(fp);
    // ar = (char**)malloc(4*32*sizeof(char));
    int i = 0;
    int k = 0;
    while ((char)ch != EOF)
    {
        // printf("%c ",ch);
        if (ch == 10)
        {
            // inc the row
            arr[i][k] = '\0';
            i += 1;
            k = 0;
            // printf("\n");
            ch = fgetc(fp);

            continue;
        }
        arr[i][k++] = ch;
        ch = fgetc(fp);
    }
    arr[i][k] = '\0';
    fclose(fp);
    return i;
}

void writeLines(char arr[][cols], char *filename, int rows)
{
    FILE *op;

    op = fopen(filename, "w");

    for (int i = 0; i < rows; i++)
    {
        // fputs(arr[i], op);
        fprintf(op,"%s",arr[i]);
        if (i < rows - 1)
        {
            fputs("\n", op);
        }
    }

}
