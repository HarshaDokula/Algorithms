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
    char word[1024];
    char 
    if (file_in == NULL)
    {
        printf("file can't be opened \n");
        exit(1);
    }

    while(fgets(word,1024,file_in) != NULL)
    {
	//TODO: count occurences of each character in the file.	
	
    }

    fclose(file_in);
    return 0;
}
