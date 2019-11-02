# float-radix-sort-C
C program to sort a set of 4-byte float point values in ascending order using radixsort. The values are saved in a file. After sorting, the original file should still save the sorted values. 
The radix-sort implementation should be flexible to support sorting the values as binaries
or hexadecimals. When the values are sorted as binaries, the program should usetwo lists, and
in each round of the sort your program adds every value to one of the lists based on the bit
being examined in this round. When the values are sorted as hexadecimals, the program
uses 16 lists, and in each round of the sort your program adds every value to one of the lists
based on the hexadecimal digit (i.e., 4 binary digits) bit being examined in this round.
 Your program should take two arguments. One is the number of bits, 1 for sorting the
values as binaries and 4 for sorting the values as hexadecimals. Thus, it represents the
number of bits in each digit used in the sort. The second argument is the pathname of the
file containing the data to be sorted. The number of float-point values saved in the file can
be calculated using file size and the size of each float point value (i.e., 4 bytes). Thus, there
is no need to specify the number of values. For example, to sort the float point values saved
in ./file5k as hexadecimals, you can use the following command:
./your_program 4 ./file5k
 The implementation of radix-sort needs to use bitwise operations. Read online articles or
get a C programming book for how to use bitwise operations. Bitwise operations cannot be
directly applied to float point values. You may need to use union to include two types, float
and int, to allow your program to access a value with these two different types.
Special attention is needed to handle the problem caused by sign bits. If sign bits are
handled in the same way as other bits, after the last round of sort, all the negative values
will be organized after positive values, and the negative values are in descending order.
Thus, you need to reverse the order of negative values and put them before positive values
in the file.
