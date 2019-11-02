#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include<stdbool.h>
#define ARR_LEN(ARR) (sizeof ARR / sizeof *ARR)
#include<limits.h>
#define FILEPATH argv[2]

u_int32_t float_to_bits(const float f);
float int_bits(const u_int32_t u);

static void radix_sort(int *a, const size_t len);
int main(int argc, char *argv[])
{
    
    int i;
   int  result;
    int i_max = 10;
    float fd;
    float *map;  /* mmapped array of int's */
	fd  = open(FILEPATH, O_RDWR);
       if(fd < 0){
           printf("open error\n");
       }
       struct stat myStat = {};
       if (fstat(fd, &myStat)){
           printf("fstat error\n");
       }

	off_t size = myStat.st_size;
	
	static int array[100000000];
       map  = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
       if (map == MAP_FAILED){
           printf("mmap error\n");
       }
    double fl;
    int j;
   
	for (i = 0; i < size/4; ++i) {
	j = float_to_bits(map[i]);
        array[i] = j;
    }


   radix_sort(array, size/4);
	int counter = 0;
    for (size_t i = 0; i < size/4; i++){
	map[i] = int_bits(array[i]);
	if(map[i] >= 0 && counter==0) counter = i;
    }

	int start= 0;
        float tmp;

       for(i = counter-1; i >= counter/2; --i){
	tmp = map[i];
	map[i] = map[start];
	map[start] = tmp;
	start++;
	
       }
	
    return 0;

  close(fd);

}
float  int_bits(const u_int32_t u)
{
    union {
        u_int32_t  u;
        float     f;
    } temp;

    temp.u = u;
    return temp.f;
}


u_int32_t float_to_bits(const float f)
{
  union {
        u_int32_t  u;
        float     f;
    } temp;

    temp.f = f;
    return temp.u;
}


static void swap(unsigned *a, unsigned *b) {
    unsigned tmp = *a;
    *a = *b;
    *b = tmp;
}

static void rad_sort_u(unsigned *from, unsigned *to, unsigned bit)
{
	if (!bit || to < from + 1) return;

	unsigned *ll = from, *rr = to - 1;
	for (;;) {
		while (ll < rr && !(*ll & bit)) ll++;
		while (ll < rr &&  (*rr & bit)) rr--;
		if (ll >= rr) break;
		swap(ll, rr);
	}

	if (!(bit & *ll) && ll < to) ll++;
	bit >>= 1;

	rad_sort_u(from, ll, bit);
	rad_sort_u(ll, to, bit);
}

static void radix_sort(int *a, const size_t len)
{
	size_t i;
	unsigned *x = (unsigned*) a;

	for (i = 0; i < len; i++)
            x[i] ^= INT_MIN;

        rad_sort_u(x, x + len, INT_MIN);

        for (i = 0; i < len; i++)
            x[i] ^= INT_MIN;
}

