/*

Katarzyna Krawczyk
kkrawc6 
 

 
 QUESTIONS:
 
 1. There was a greate benefit in the initial unroll (2x2). In most cases it decreased the
    CPE by at least 2 cycles per element. After that, in the subsequent unrolls this benefit is less
    and less visable as the CPE doesnt change that much from 4x4 to 8x8.
 
 2. As noted in book pages 539 - 540 (3rd Edition), there is a bound on the throughput of each function. 
    This causes the CPE values to taper off in improvement as you approach this bound. The reason this
    bound exists is but is never achieved is because of limitations in memory and pipeline capabilities. These
    limitations are tested with all the overhead associated with having more unrolls.
 
TABLE:
 
        ------------------//stages//---------------------
 unrolls float 32     float 64         int 32    int 64

 orig    7.82  	        7.49            6.65	  6.27

 2x2	 4.72	        4.85	        4.72 	  4.89

 4x4     4.16           4.55	        4.13	  4.42

 8x8     3.83           4.02	        3.77	  4.08
 
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
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum0 = (data_t) 0;
data_t sum1 = (data_t) 0;
int limit = length - 1;


for (i=0;i<=limit;i+=2){
    sum0 += udata[i] * vdata[i];
    sum1 += udata[i+1] * vdata[i+1];
    }
for(; i<length; i++){
   sum0 += udata[i] * vdata[i];
}
*dest = sum0 + sum1;
}


char inner4_descr[] = "inner4: unroll 4x and 4 accumulators";
/* $begin inner4 */
void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum0 = (data_t) 0;
data_t sum1 = (data_t) 0;
data_t sum2 = (data_t) 0;
data_t sum3 = (data_t) 0;
int limit = length - 3;

for (i=0;i<limit;i+=4){
    sum0 += udata[i] * vdata[i];
    sum1 += udata[i+1] * vdata[i+1];
    sum2 += udata[i+2] * vdata[i+2];
    sum3 += udata[i+3] * vdata[i+3];
}
for(; i<length; i++)
   sum0 += udata[i] * vdata[i];
*dest = sum0 + sum1 + sum2 + sum3; 
}

char inner8_descr[] = "inner8: unroll 8x and 8 accumulators";
/* $begin inner8 */
void inner8(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
int limit = length - 7;

data_t sum0 = (data_t) 0;
data_t sum1 = (data_t) 0;
data_t sum2 = (data_t) 0;
data_t sum3 = (data_t) 0;
data_t sum4 = (data_t) 0;
data_t sum5 = (data_t) 0;
data_t sum6 = (data_t) 0;
data_t sum7 = (data_t) 0;
for (i=0;i<limit;i+=8){
    sum0 += udata[i] * vdata[i];
    sum1 += udata[i+1] * vdata[i+1];
    sum2 += udata[i+2] * vdata[i+2];
    sum3 += udata[i+3] * vdata[i+3];
    sum4 += udata[i+4] * vdata[i+4];
    sum5 += udata[i+5] * vdata[i+5];
    sum6 += udata[i+6] * vdata[i+6];
    sum7 += udata[i+7] * vdata[i+7];
    }
for(;i<length; i++)
   sum0 += udata[i] * vdata[i];
*dest = sum0 + sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7;
}




void register_combiners(void)
{
    add_combiner(inner1, inner1, inner1_descr);
    add_combiner(inner2, inner1, inner2_descr);
    add_combiner(inner4, inner1, inner4_descr);
    add_combiner(inner8, inner1, inner8_descr);
}

