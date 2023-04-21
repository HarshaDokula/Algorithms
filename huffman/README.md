# Huffman compression Using arrays.

compressing the given file using huffamn coding.


## Basic understanding of the program works.

1. read the input_text.txt file.
2. count the character frequency.
3. build the tree for huffman encoding using arrays.
4. build a encoding table that has encoded strings for each char.
5. convert the input_text to huffman coding , in char array.
6. convert the char array of zeros and ones to bit representation (for size compression) and store in compressedfile.txt
7. Read the compressedfile.txt to get the bit representation of the message , convert it to char array of zeros and ones.
8. use the tree for converting it back to the message.


## how to compile

'''
make \ENTER
'''

## how to run

Kindly put the input text to be entered in 'input_text.txt' and then
'''
make test \ENTER
'''

else to give any files as input.

'''
.huff <input file name.txt> \ENTER
'''

## Example output

Note: additional to input it will wirte the decoded message to a file "outfile.txt" and the compressed data is compressedfile.txt

'''
./huff input_text.txt


encoding message: sdfdsf
s
dfs
fdsgfhghgherwfe
sc4r3ytym
h.;';q1
21  dfds
3qe3bv


code: 01011110011111010001011010011111100101001100111110100001001100000011000000110000000101101110000010000011010110100110010101101110110111110110101111101010111000110000101001110011101001010110011011110001100111001010010111100111110100111110110101000011101110011110111011

decoded message: sdfdsf
s
dfs
fdsgfhghgherwfe
sc4r3ytym
h.;';q1
21  dfds
3qe3bv

63 chars written


'''

## Citations

1. fseek  -> https://en.cppreference.com/w/c/io/fseek
2. ftell  ->  https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-ftell-get-current-file-position
3. snprintf -> https://www.ibm.com/docs/en/i/7.3?topic=functions-snprintf-print-formatted-data-buffer
4. fwrite -> https://www.ibm.com/docs/en/i/7.2?topic=functions-fwrite-write-items
5. for iteger to binary conversion -> https://stackoverflow.com/questions/5488377/converting-an-integer-to-binary-in-c


## Things to improve.

* The decompressed message length is taken for the encoded message, make the decompressed message length variable.
* the decoding of the message is done using huffman tree, do it using variable length substrings and hash map table for character encoding to decode back to original message.
* there are character array to store message or the encoded message [in the tansient stages], change them to write directly to files.


