/*

Denis Doci
UIN 663855180
doci2

unroll	INT 64bit   FLOAT 64bit   INT 32bit    FLOAT 32bit

none    6.80  	       7.24         6.68	  8.98

2X2	    4.87	       4.81	        4.71 	  4.89
 
4X4     4.91           4.53	        4.23	  4.42

8X8     4.12           3.99	        3.82	  4.08


//--------------- Questions ------------------//
Questions:

1. The biggest benefit to the loop unrolling can be seen in doing a 2x2
   unroll on any of the systems. As the unroll gets bigger the effect on
   the CPE of the function gets smaller. There is a variety of reasons fo this as discussed below

2. The function as it unrolls more approaches the throughput bound for the operation.
   This is because the piplines are filling for all functinal units capable
   of completing the operation.
   
   Also there is a limiting factor in the memory associated with using a large loop unroll. As the
   unroll increases the amount of loop overhead increases. 
 

 *
 */
#include "combine.h"

/* Combining functions */

char inner1_descr[] = "inner1: original loop no unrolling";
/* $begin inner1 */
void inner1(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum = (data_t) 0;
for (i=0;i<length;i++){
    sum = sum + udata[i] * vdata[i];
    }
*dest = sum;
}


char inner2_descr[] = "inner2: unroll 2x and 2 accumulators"; 
/* $begin inner2 */
void inner2(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
int limit = length - 1; 
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t acc0 = (data_t) 0;
data_t acc1 = (data_t) 0;


for (i=0;i<=limit;i+=2){
    acc0 += udata[i] * vdata[i];
    acc1 += udata[i+1] * vdata[i+1];
    }
for(; i<length; i++){
   acc0 += udata[i] * vdata[i];
}
*dest = acc0 + acc1;
}


char inner4_descr[] = "inner4: unroll 4x and 4 accumulators"; 
/* $begin inner4 */
void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
long int length = vec_length(u);
long limit = length - 3;
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t acc0 = (data_t) 0;
data_t acc1 = (data_t) 0;
data_t acc2 = (data_t) 0;
data_t acc3 = (data_t) 0;

for (i=0;i<limit;i+=4){
    acc0 += udata[i] * vdata[i];
    acc1 += udata[i+1] * vdata[i+1];
    acc2 += udata[i+2] * vdata[i+2];
    acc3 += udata[i+3] * vdata[i+3];
}
for(; i<length; i++){
   acc0 += udata[i] * vdata[i];
}
*dest = acc0 + acc1 + acc2 + acc3; 
}

char inner8_descr[] = "inner8: unroll 8x and 8 accumulators"; 
/* $begin inner8 */
void inner8(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
long int length = vec_length(u);
long int limit = length - 7;
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);

data_t acc0 = (data_t) 0;
data_t acc1 = (data_t) 0;
data_t acc2 = (data_t) 0;
data_t acc3 = (data_t) 0;
data_t acc4 = (data_t) 0;
data_t acc5 = (data_t) 0;
data_t acc6 = (data_t) 0;
data_t acc7 = (data_t) 0;
for (i=0;i<limit;i+=8){
    acc0 += udata[i] * vdata[i];
    acc1 += udata[i+1] * vdata[i+1];
    acc2 += udata[i+2] * vdata[i+2];
    acc3 += udata[i+3] * vdata[i+3];
    acc4 += udata[i+4] * vdata[i+4];
    acc5 += udata[i+5] * vdata[i+5];
    acc6 += udata[i+6] * vdata[i+6];
    acc7 += udata[i+7] * vdata[i+7];
    }
for(;i<length; i++)
   acc0 += udata[i] * vdata[i];
*dest = acc0 + acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7;
}




void register_combiners(void)
{
    add_combiner(inner1, inner1, inner1_descr);
    add_combiner(inner2, inner1, inner2_descr);
    add_combiner(inner4, inner1, inner4_descr);
    add_combiner(inner8, inner1, inner8_descr);
}
