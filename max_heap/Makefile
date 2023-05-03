heap_cmp: heap.c
	gcc -o ../bin/hsort heap.c

bubble_cmp: bubble.c
	gcc -o ../bin/bsort bubble.c

run:
	../bin/hsort input_text.txt > hsort.out.txt
	../bin/bsort input_text.txt > bsort.out.txt
	/usr/bin/sort input_text.txt > sort.out.txt

test_hsort:
	diff -iw sort.out.txt hsort.out.txt

test_bsort:
	diff -iw sort.out.txt bsort.out.txt

timing:
	time ../bin/hsort input_text.txt > hsort.out.txt
	time ../bin/bsort input_text.txt > bsort.out.txt
