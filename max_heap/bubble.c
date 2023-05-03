#include<stdio.h>
#include<string.h>
#include"fileops.h"

int main(int argc, char *argv[]){

    char lines[20000][200];

    int rows = readLines(lines,"input_text.txt")+1;
    char t[200];
    for(int i=0;i<rows-1;i++){
        // printf("%s\n", lines[i]);
        for(int j=i+1;j<rows;j++){
            if(strcmp(lines[i],lines[j])>0){
                strcpy(t,lines[i]);
                strcpy(lines[i],lines[j]);
                strcpy(lines[j],t);
            }
        }
    }

    for(int i=0;i<rows;i++){
        printf("%s",lines[i]);
        if(i<rows-1){
            printf("\n");
        }
    }

    writeLines(lines,"output_text.txt",rows);
}
