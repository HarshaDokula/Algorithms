# MAX HEAP TREE

## Properties of Max Heap tree

1. it is always a complete tree.

## Basic understanding on how the program works

1. The input_text.txt is read.
2. Build a heap trees using the input lines , on arrays.
3. perform heap sort

    since the string array is required to be sorted in place, 
    step 1: the root node of the heap is swaped with the last node of the array, so now the last node of array is guaranteed to be the largest. Now the array bounds are updated to not touch the last node of the array (i.e, decrease the num of nodes by 1)
    step 2: repeat step 1 till the leaf node is reached.

## how to execute

* To compile the heap algorithm.

''' make '''

* To compile the bubble sort algorithm.

''' make bubble_cmp'''

* To run all the algoritms and produce out puts.
''' make run '''

It runs all the sorting algoritms using the 'input_text.txt' file places the output into the respective '<>.out.txt' files.

* To check the timing of the algorithm

''' make timing '''

## Citations

1. for the hsort algorithm , "Fundamentals of Computer Algorithms by Ellis Horowitz, Sartaj Sahni, Sanguthevar Rajasekaran" was reffered.
