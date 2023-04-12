#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("no file name given or wrong executoin\n");
        exit(1);
    }


    FILE* file_in = fopen(argv[1],"r");
    int symbol_count[256] = {0};

    if (file_in == NULL)
    {
        printf("file can't be opened \n");
        exit(1);
    }

    int symbol = fgetc(file_in);
    while((char)symbol != EOF)
    {	
	    //printf("/%c/",(char)symbol);
	    symbol_count[symbol]++;
	    symbol = fgetc(file_in);
    }

    printf("char count of A:%d\n",symbol_count[65]);
    printf("char count of 5:%d\n",symbol_count[53]);
    printf("char count of @:%d\n",symbol_count[64]);
    printf("char count of }:%d\n",symbol_count[125]);
    fclose(file_in);
    return 0;
}
