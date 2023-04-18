#include"util.h"
#define codelen 32768 //increase this if you get stack smashing detected error.

//====================== huffman tree gen code==========================================================================
// constructs a huffman tree and returns the root of the tree.
Node *huffmanTree(Node **nodes,size_t low_bound, size_t up_bound){
    size_t idx = up_bound;
    while(idx > 1){

        int min1 = getMinNode(nodes,up_bound);
        nodes[min1]->isUsed = true;
        int min2 = getMinNode(nodes,up_bound);
        nodes[min2]->isUsed = true;
        Node *temproot = aloc;
        init_node(temproot,(nodes[min1]->freq+nodes[min2]->freq),min1,min2,'\0');
        temproot->source_data[0] = '\0';
        snprintf(temproot->source_data, sizeof(temproot->source_data),"%s%s",nodes[min1]->source_data,nodes[min2]->source_data);

        nodes[up_bound++] = temproot; //rewriting the 0th node to temproot
        idx-=1; //keeps track of how many un-used nodes still left.

    }
    return nodes[up_bound-1]; //nodes[0] has the root of the final huffman tree.
}



// encodes the message.
void encode(Node *root, Node **nodes, char *message, char *code){
    size_t code_counter=0;
    for(size_t i = 0;i<strlen(message);i++){
        // printf("finding code for char: %c\n\n",message[i]);
        Node *tempRoot = root;
        while(tempRoot->left >-1 || tempRoot->right >-1){
            if(nodes[tempRoot->left]->data == message[i]){
                code[code_counter++] = '0';
                tempRoot = nodes[tempRoot->left];
            }
            else if(nodes[tempRoot->right]->data == message[i]){
                code[code_counter++] = '1';
                tempRoot = nodes[tempRoot->right];
            }
            // check if we can find the required data in left subtree
            else if(isReachable(message[i],nodes[tempRoot->left]->source_data,strlen(nodes[tempRoot->left]->source_data))){
                code[code_counter++] = '0';
                tempRoot = nodes[tempRoot->left];
            // check if we can find the required data in right subtree
            }else if(isReachable(message[i],nodes[tempRoot->right]->source_data,strlen(nodes[tempRoot->right]->source_data))){
                code[code_counter++] = '1';
                tempRoot = nodes[tempRoot->right];
            }
            else{
                // nothing here
            }
        }
    }
    code[code_counter]='\0';
    printf("code: %s\n\n",code);
}



// decodes the code.
void decode(Node * root, Node **nodes, char *code, char *decoded_msg,int code_len){
    int msg_counter=0;
    Node *current = root;
    char c;
    for(int i = 0;i<=code_len;i++){
        c = code[i];
        if(isLeaf(current)){

            decoded_msg[msg_counter++] = current->data;
            current = root;
        }
        if(c=='0'){
            if(current->left!=-1){
                current= nodes[current->left];
            }
        }
        else if(c=='1'){
            if(current->right!=-1){
                current= nodes[current->right];
            }
        }
    }
    decoded_msg[msg_counter]='\0';
    printf("decoded message: %s\n", decoded_msg);
}



//======================================== main code===========================================================================
int main(int argc, char * argv[]){

 if(argc != 2)
    {
        printf("no file name given or wrong executoin\n");
        exit(1);
    }


    FILE* file_in = fopen(argv[1],"r");
    int symbol_count[charcount] = {0};

    if (file_in == NULL)
    {
        printf("file can't be opened \n");
        exit(1);
    }

    int symbol = fgetc(file_in);
    while((char)symbol != EOF)
    {	
	    symbol_count[symbol]++;
	    symbol = fgetc(file_in);
    }

    fclose(file_in);

    printf("\n");

    size_t up_bound = charcount;
    Node *nodes[Nodes_size];

    // initializing the pointer array that points to Node data type from symbol_count
    for(size_t i = 0;i<up_bound;i++){

        nodes[i] = aloc;
        init_node(nodes[i],symbol_count[i],-1,-1,i);
    }
    

    size_t low_bound = 0;

    Node *root = huffmanTree(nodes, low_bound, up_bound); //returns root of the constructed huffman tree.

    char code[codelen];

     FILE *fpp;
    char *str;
    long file_size;

    fpp = fopen(argv[1], "rb");
    if(fpp == NULL) {
        printf("Unable to open file\n");
        return 1;
    }

    
    fseek(fpp, 0, SEEK_END);
    file_size = ftell(fpp);

    rewind(fpp); // sets the pointer to the starting of the file.

    str = (char*) malloc(file_size + 1);

    fread(str, 1, file_size, fpp);
    fclose(fpp);

    str[file_size] = '\0';

    
    //compressing the message.
    printf("\nencoding message: %s\n\n",str);
    encode(root,nodes,str,code);
    
    //Decoding the compressed message.
    char decoded_message[codelen];
    decode(root,nodes,code,decoded_message,strlen(code));

    //writing the output to file.
    FILE *out_file ;
    out_file = fopen("outfile.txt","wb");
    int numw = fwrite(decoded_message, sizeof(char), file_size, out_file);
    printf("%d chars written",numw);
    fclose(out_file);

    //free memory space.
    free(str);
    
    for(size_t i = 1; i < Nodes_size; i++) {
        if(nodes[i]!=NULL)
        free(nodes[i]);
    }

    return 0;
}
