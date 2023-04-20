#include "util.h"
#include<math.h>
#define codelen 32768 // increase this if you get stack smashing detected error.

//====================== huffman tree gen code==========================================================================
// constructs a huffman tree and returns the root of the tree.
Node *huffmanTree(Node **nodes, size_t up_bound)
{
    size_t idx = up_bound;
    while (idx > 1)
    {

        int min1 = getMinNode(nodes, up_bound);
        nodes[min1]->isUsed = true;
        int min2 = getMinNode(nodes, up_bound);
        nodes[min2]->isUsed = true;
        Node *temproot = aloc;
        init_node(temproot, (nodes[min1]->freq + nodes[min2]->freq), min1, min2, '\0');
        temproot->source_data[1] = '\0';
        snprintf(temproot->source_data, sizeof(temproot->source_data), "%s%s", nodes[min1]->source_data, nodes[min2]->source_data);

        nodes[up_bound++] = temproot; // rewriting the 0th node to temproot
        idx -= 1;
    }
    return nodes[up_bound - 1]; // nodes[0] has the root of the final huffman tree.
}

// encodes the message.
void encode(Node *root, Node **nodes, char message, char *code, char encs[charcount][32])
{
    size_t code_counter = 0;
    Node *tempRoot = root;
    while (tempRoot->left > -1 || tempRoot->right > -1)
    {
        if (nodes[tempRoot->left]->data == message)
        {
            code[code_counter++] = '0';
            tempRoot = nodes[tempRoot->left];
        }
        else if (nodes[tempRoot->right]->data == message)
        {
            code[code_counter++] = '1';
            tempRoot = nodes[tempRoot->right];
        }
        // check if we can find the required data in left subtree
        else if (isReachable(message, nodes[tempRoot->left]->source_data, strlen(nodes[tempRoot->left]->source_data)))
        {
            code[code_counter++] = '0';
            tempRoot = nodes[tempRoot->left];
            // check if we can find the required data in right subtree
        }
        else if (isReachable(message, nodes[tempRoot->right]->source_data, strlen(nodes[tempRoot->right]->source_data)))
        {
            code[code_counter++] = '1';
            tempRoot = nodes[tempRoot->right];
        }
        else
        {
            // nothing here
            printf("you here?");
            break;
        }
    }
    code[code_counter] = '\0';
    int k = message;
    snprintf(encs[k], 32, "%s", code);
}

// decodes the code.
void decode(Node *root, Node **nodes, char *code, char *decoded_msg, int code_len)
{
    int msg_counter = 0;
    Node *current = root;
    char c;
    for (int i = 0; i <= code_len; i++)
    {
        c = code[i];
        if (isLeaf(current))
        {
            decoded_msg[msg_counter++] = current->data;
            current = root;
        }
        if (c == '0')
        {
            if (current->left != -1)
            {
                current = nodes[current->left];
            }
        }
        else if (c == '1')
        {
            if (current->right != -1)
            {
                current = nodes[current->right];
            }
        }
    }
    decoded_msg[msg_counter] = '\0';
    printf("decoded message: %s\n", decoded_msg);
}

//======================================== main code===========================================================================
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("no file name given or wrong executoin\n");
        exit(1);
    }

    FILE *file_in = fopen(argv[1], "r");
    int symbol_count[charcount] = {0};

    if (file_in == NULL)
    {
        printf("file can't be opened \n");
        exit(1);
    }

    int symbol = fgetc(file_in);
    while ((char)symbol != EOF)
    {
        symbol_count[symbol]++;
        symbol = fgetc(file_in);
    }

    fclose(file_in);

    printf("\n");

    size_t up_bound = charcount;
    Node *nodes[Nodes_size];

    // initializing the pointer array that points to Node data type from symbol_count
    for (size_t i = 0; i < up_bound; i++)
    {

        nodes[i] = aloc;
        init_node(nodes[i], symbol_count[i], -1, -1, i);
    }

    Node *root = huffmanTree(nodes, up_bound); // returns root of the constructed huffman tree.

    char code[codelen];

    // normal input text from file
    FILE *fpp;
    char *str;
    long file_size;

    fpp = fopen(argv[1], "rb");
    if (fpp == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    fseek(fpp, 0, SEEK_END);
    file_size = ftell(fpp);

    rewind(fpp); // sets the pointer to the starting of the file.

    str = (char *)malloc(file_size + 1);

    fread(str, 1, file_size, fpp);
    fclose(fpp);

    str[file_size] = '\0';

    char encs[127][32];

    char decoded_message[codelen];
    char encoded_message[codelen];

    decoded_message[0] = '\0';
    printf("\nencoding message: %s\n\n", str);
    for (int i = 1; i < charcount; i++)
    {

        encode(root, nodes, i, code, encs);
    }

    char prev[codelen];
    int encode_len = 0;
    for (size_t i = 0; i < file_size; i++)
    {
        encode_len = snprintf(encoded_message, codelen, "%s%s", prev, encs[str[i]]);
        snprintf(prev, codelen, "%s", encoded_message);
    }

    printf("len of the encoding %d  ", encode_len);
    printf("code : %s\n\n", encoded_message);

    // compressing encoded_message
    int i;
    int byte_num = -1;
    unsigned char message[(encode_len/8)+1];
    for (i = 0; i < encode_len; i++)
    {
        if (!(i % 8))
            byte_num++;
        if (encoded_message[i] == '0')
        {
            pack_zero(&message[byte_num]);
        }
        else
            pack_one(&message[byte_num]);
    }

    // writing the compressed message to file
    FILE *comp_file;
    comp_file = fopen("compressedfile.txt", "w");

    int numc = fwrite(message, sizeof message[0], byte_num + 1, comp_file);
    fclose(comp_file);


// reading compressed file 
    int comp_file_size = 0;
    comp_file = fopen("compressedfile.txt", "r");

    unsigned char comp_str[encode_len];

    fread(comp_str, sizeof message[0], byte_num+1, comp_file);
    fclose(comp_file);

    comp_str[byte_num+1] = '\0';

    // decompressing
    char bin[9];
    char buff[encode_len * 2];
    char prevb[encode_len * 2];
    prevb[0] = '\0';

    int bufflen = 8;
    for (int i = 0; i <= byte_num; i++)
    {

        itob(comp_str[i], bin);
   
        bufflen = snprintf(buff, encode_len * 2, "%s%s", prevb, bin);
        int prevlen = snprintf(prevb, bufflen + 1, "%s", buff);
    }

    buff[(byte_num * 8)] = '\0';

    int charweneed = encode_len % 8;
    char *buf = &bin[(encode_len - bufflen) + 1];
    int indexweneed = bufflen - charweneed;
    char *buft = &buff[indexweneed];
    char *newstr = strcat(buff, buft);

    decode(root, nodes, newstr, decoded_message, strlen(newstr));

    FILE *out_file;
    out_file = fopen("outfile.txt", "wb");

    int numw = fwrite(decoded_message, sizeof(char), file_size, out_file);
    fclose(out_file);

    free(str);
    for (size_t i = 0; i < Nodes_size; i++)
    {
        if (nodes[i] != NULL)
            free(nodes[i]);
    }

    return 0;
}
