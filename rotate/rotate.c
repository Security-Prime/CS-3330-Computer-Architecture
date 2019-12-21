#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following struct with your name and the name you'd like to appear on the scoreboard
 */
who_t who = {
    "Nike",           /* Scoreboard name */

    "Farid Rajabi Nia",   /* Full name */
    "fr2md@virginia.edu",  /* Email address */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}
/* 
 * rotate - Your current working version of rotate
 *          Our supplied version simply calls naive_rotate
 */
char another_rotate_descr[] = "another_rotate: Another version of rotate";
void another_rotate(int dim, pixel *src, pixel *dst) 
{
//pixel *dest;
    for (int j = 0; j < dim; j++){
	for (int i = 0; i < dim; i+=4){
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
	    dst[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
	    dst[RIDX(dim-1-j, i+2, dim)] = src[RIDX(i+2, j, dim)];
	    dst[RIDX(dim-1-j, i+3, dim)] = src[RIDX(i+3, j, dim)];
	    //dest[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
	    //dest[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
	    //dest[RIDX(dim-1-j, i+2, dim)] = src[RIDX(i+2, j, dim)];
	    //dest[RIDX(dim-1-j, i+3, dim)] = src[RIDX(i+3, j, dim)];
	}
    }
//dst = strcat(dst, dest);
}

void another_rotate1(int dim, pixel *src, pixel *dst) 
{
 for (int i = 0; i < dim; i+=4){
	
	for (int j = 0; j < dim; j+=2){
            // j=0
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
	    dst[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
	    dst[RIDX(dim-1-j, i+2, dim)] = src[RIDX(i+2, j, dim)];
            dst[RIDX(dim-1-j, i+3, dim)] = src[RIDX(i+3, j, dim)];
            // j=1
	    dst[RIDX(dim-1-j-1, i, dim)] = src[RIDX(i, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+1, dim)] = src[RIDX(i+1, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+2, dim)] = src[RIDX(i+2, j+1, dim)];
            dst[RIDX(dim-1-j-1, i+3, dim)] = src[RIDX(i+3, j+1, dim)];	
}
    }

}

void another_rotate2(int dim, pixel *src, pixel *dst) 
{
 for (int i = 0; i < dim; i+=8){
	for (int j = 0; j < dim; j++){
            dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
	    dst[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
	    dst[RIDX(dim-1-j, i+2, dim)] = src[RIDX(i+2, j, dim)];
            dst[RIDX(dim-1-j, i+3, dim)] = src[RIDX(i+3, j, dim)];
	    dst[RIDX(dim-1-j, i+4, dim)] = src[RIDX(i+4, j, dim)];
	    dst[RIDX(dim-1-j, i+5, dim)] = src[RIDX(i+5, j, dim)];
	    dst[RIDX(dim-1-j, i+6, dim)] = src[RIDX(i+6, j, dim)];
            dst[RIDX(dim-1-j, i+7, dim)] = src[RIDX(i+7, j, dim)];
            	
	}
    }

}
void another_rotate3(int dim, pixel *src, pixel *dst) 
{
 for (int i = 0; i < dim; i+=8){
	for (int j = 0; j < dim; j+=2){
	    // j=0           
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
	    dst[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
	    dst[RIDX(dim-1-j, i+2, dim)] = src[RIDX(i+2, j, dim)];
            dst[RIDX(dim-1-j, i+3, dim)] = src[RIDX(i+3, j, dim)];
	    dst[RIDX(dim-1-j, i+4, dim)] = src[RIDX(i+4, j, dim)];
	    dst[RIDX(dim-1-j, i+5, dim)] = src[RIDX(i+5, j, dim)];
	    dst[RIDX(dim-1-j, i+6, dim)] = src[RIDX(i+6, j, dim)];
            dst[RIDX(dim-1-j, i+7, dim)] = src[RIDX(i+7, j, dim)];
            // j=1
	    dst[RIDX(dim-1-j-1, i, dim)] = src[RIDX(i, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+1, dim)] = src[RIDX(i+1, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+2, dim)] = src[RIDX(i+2, j+1, dim)];
            dst[RIDX(dim-1-j-1, i+3, dim)] = src[RIDX(i+3, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+4, dim)] = src[RIDX(i+4, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+5, dim)] = src[RIDX(i+5, j+1, dim)];
	    dst[RIDX(dim-1-j-1, i+6, dim)] = src[RIDX(i+6, j+1, dim)];
            dst[RIDX(dim-1-j-1, i+7, dim)] = src[RIDX(i+7, j+1, dim)];
	
	}
    }

}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate function by calling the add_rotate_function() for
 *     each test function. When you run the benchmark program, it will
 *     test and report the performance of each registered test
 *     function.  
 *********************************************************************/

void register_rotate_functions() {
    add_rotate_function(&naive_rotate, naive_rotate_descr);
    add_rotate_function(&another_rotate, another_rotate_descr);
    add_rotate_function(&another_rotate1, another_rotate_descr);
    add_rotate_function(&another_rotate2, another_rotate_descr);
    add_rotate_function(&another_rotate3, another_rotate_descr);
}
