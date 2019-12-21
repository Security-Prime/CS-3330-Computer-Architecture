#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
//#include <smmintrin.h>
#include <immintrin.h>

/* 
 * Please fill in the following team struct 
 */
who_t who = {
    "Nike",           /* Scoreboard name */

    "Farid Rajabi Nia",      /* First member full name */
    "fr2md@virginia.edu",     /* First member email address */
};

/*** UTILITY FUNCTIONS ***/

/* You are free to use these utility functions, or write your own versions
 * of them. */

/* A struct used to compute averaged pixel value */
typedef struct {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
    unsigned short alpha;
    unsigned short num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = sum->alpha = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->alpha += (int) p.alpha;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    current_pixel->alpha = (unsigned short) (sum.alpha/sum.num);
    return;
}

static void assign_sum_to_pixel6(pixel *current_pixel, pixel_sum sum) 
{
    sum.num = 6;
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    current_pixel->alpha = (unsigned short) (sum.alpha/sum.num);
    return;
}

static void assign_sum_to_pixel4(pixel *current_pixel, pixel_sum sum) 
{
    sum.num = 4;
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    current_pixel->alpha = (unsigned short) (sum.alpha/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(int jj=max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	for(int ii=max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	    accumulate_sum(&sum, src[RIDX(ii,jj,dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
 
    return current_pixel;
}

static pixel avg6(int dim, int i, int j, pixel *src) 
{
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(int jj=max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	for(int ii=max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	    accumulate_sum(&sum, src[RIDX(ii,jj,dim)]);

    assign_sum_to_pixel6(&current_pixel, sum);
 
    return current_pixel;
}

static pixel avg4(int dim, int i, int j, pixel *src) 
{
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(int jj=max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	for(int ii=max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	    accumulate_sum(&sum, src[RIDX(ii,jj,dim)]);

    assign_sum_to_pixel4(&current_pixel, sum);
 
    return current_pixel;
}


/******************************************************
 * Your different versions of the smooth go here
 ******************************************************/

/* 
 * naive_smooth - The naive baseline version of smooth
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
            dst[RIDX(i,j, dim)] = avg(dim, i, j, src);
}
/* 
 * rotate - Your current working version of smooth
 *          Our supplied version simply calls naive_smooth
 */
char another_smooth_descr[] = "another_smooth: Another version of rotate";
void another_smooth(int dim, pixel *src, pixel *dst) 
{
    // inside

     for (int i = 1; i < dim-1; i++){
	for (int j = 1; j < dim-1; j+=4){

            __m256i sum_of_pixels = _mm256_setzero_si256();
		
            __m128i pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, j, dim)]);
	    __m256i pix = _mm256_cvtepu8_epi16 (pixel); 
	    //sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
		
	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, j-1, dim)]);
	    __m256i pix1 = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,pix1);

	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, j, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

            pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, j+1, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, j-1, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, j+1, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, j-1, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, j, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
		
	    pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, j+1, dim)]);
	    pix = _mm256_cvtepu8_epi16 (pixel); 
	    sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
	
	    //__m256i val = _mm256_set1_epi16(7282);
	    //__m256i mul = _mm256_mulhi_epi16(sum_of_pixels, val); 
	    //__m256i result = _mm256_packus_epi16(mul, _mm256_unpackhi_epi16())
    	    		
   	    unsigned short pixel_elements[16];
            _mm256_storeu_si256((__m256i*) pixel_elements, sum_of_pixels);

	    dst[RIDX(i,j, dim)].red = (pixel_elements[0] * 7282) >> 16;
	    dst[RIDX(i,j, dim)].green = (pixel_elements[1]* 7282) >> 16;
	    dst[RIDX(i,j, dim)].blue = (pixel_elements[2]* 7282) >> 16;
	    dst[RIDX(i,j, dim)].alpha = (pixel_elements[3]* 7282) >> 16;
	    dst[RIDX(i,j+1, dim)].red = (pixel_elements[4]* 7282) >> 16;
	    dst[RIDX(i,j+1, dim)].green = (pixel_elements[5]* 7282) >> 16;
	    dst[RIDX(i,j+1, dim)].blue = (pixel_elements[6]* 7282) >> 16;
	    dst[RIDX(i,j+1, dim)].alpha = (pixel_elements[7]* 7282) >> 16;
	    dst[RIDX(i,j+2, dim)].red = (pixel_elements[8]* 7282) >> 16;
	    dst[RIDX(i,j+2, dim)].green = (pixel_elements[9]* 7282) >> 16;
	    dst[RIDX(i,j+2, dim)].blue = (pixel_elements[10]* 7282) >> 16;
	    dst[RIDX(i,j+2, dim)].alpha = (pixel_elements[11]* 7282) >> 16;
	    dst[RIDX(i,j+3, dim)].red = (pixel_elements[12]* 7282) >> 16;
	    dst[RIDX(i,j+3, dim)].green = (pixel_elements[13]* 7282) >> 16;
	    dst[RIDX(i,j+3, dim)].blue = (pixel_elements[14]* 7282) >> 16;
	    dst[RIDX(i,j+3, dim)].alpha = (pixel_elements[15]* 7282) >> 16;

	}
     }

    // 1st row
    for (int j = 1; j < dim; j++){
	 dst[RIDX(0,j, dim)] = avg6(dim, 0, j, src);

	/*__m256i sum_of_pixels = _mm256_setzero_si256();
		
         __m128i pixel = _mm_loadu_si128((__m128i*) &src[RIDX(0, j-1, dim)]);
	 __m256i pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(0, j, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
	
         pixel = _mm_loadu_si128((__m128i*) &src[RIDX(0, j+1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(1, j-1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(1, j, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(1, j+1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	unsigned short pixel_elements[16];
        _mm256_storeu_si256((__m256i*) pixel_elements, sum_of_pixels);

	dst[RIDX(0,j, dim)].red = pixel_elements[0]/6;
	dst[RIDX(0,j, dim)].green = pixel_elements[1]/6;
	dst[RIDX(0,j, dim)].blue = pixel_elements[2]/6;
	dst[RIDX(0,j, dim)].alpha = pixel_elements[3]/6;*/

	}
    // last row
    for (int j = 1; j < dim; j++){
	 dst[RIDX(dim-1,j, dim)] = avg6(dim, dim-1, j, src);
	 
	 /*__m256i sum_of_pixels = _mm256_setzero_si256();
		
         __m128i pixel = _mm_loadu_si128((__m128i*) &src[RIDX(dim-1, j-1, dim)]);
	 __m256i pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(dim-1, j, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
	
         pixel = _mm_loadu_si128((__m128i*) &src[RIDX(dim-1, j+1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(dim-2, j-1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(dim-2, j, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(dim-2, j+1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	unsigned short pixel_elements[16];
        _mm256_storeu_si256((__m256i*) pixel_elements, sum_of_pixels);

	dst[RIDX(dim-1,j, dim)].red = pixel_elements[0]/6;
	dst[RIDX(dim-1,j, dim)].green = pixel_elements[1]/6;
	dst[RIDX(dim-1,j, dim)].blue = pixel_elements[2]/6;
	dst[RIDX(dim-1,j, dim)].alpha = pixel_elements[3]/6; */

	}
    // 1st col
    for (int i = 1; i < dim; i++){
        dst[RIDX(i,0, dim)] = avg6(dim, i, 0, src);
	
	/* __m256i sum_of_pixels = _mm256_setzero_si256();
		
         __m128i pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, 0, dim)]);
	 __m256i pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, 0, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
	
         pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, 0, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, 1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, 1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, 1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	unsigned short pixel_elements[16];
        _mm256_storeu_si256((__m256i*) pixel_elements, sum_of_pixels);

	dst[RIDX(i,0, dim)].red = pixel_elements[0]/6;
	dst[RIDX(i,0, dim)].green = pixel_elements[1]/6;
	dst[RIDX(i,0, dim)].blue = pixel_elements[2]/6;
	dst[RIDX(i,0, dim)].alpha = pixel_elements[3]/6; */
	 
	}

    // last col
    for (int i = 1; i < dim; i++){
        dst[RIDX(i,dim-1, dim)] = avg6(dim, i, dim-1, src);
	/*
	 __m256i sum_of_pixels = _mm256_setzero_si256();
		
         __m128i pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, dim-2, dim)]);
	 __m256i pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, dim-2, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);
	
         pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, dim-2, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i-1, dim-1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i, dim-1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	 pixel = _mm_loadu_si128((__m128i*) &src[RIDX(i+1, dim-1, dim)]);
	 pix = _mm256_cvtepu8_epi16 (pixel); 
	 sum_of_pixels = _mm256_add_epi16(pix,sum_of_pixels);

	unsigned short pixel_elements[16];
        _mm256_storeu_si256((__m256i*) pixel_elements, sum_of_pixels);

	dst[RIDX(i,dim-1, dim)].red = pixel_elements[0]/6;
	dst[RIDX(i,dim-1, dim)].green = pixel_elements[1]/6;
	dst[RIDX(i,dim-1, dim)].blue = pixel_elements[2]/6;
	dst[RIDX(i,dim-1, dim)].alpha = pixel_elements[3]/6; */
 
	}
    //corners
	dst[RIDX(0,0, dim-1)] = avg4(dim, 0, 0, src);
	dst[RIDX(0,dim-1, dim-1)] = avg4(dim, 0, dim-1, src);
	dst[RIDX(dim,0, dim-1)] = avg4(dim, dim-1, 0, src);
	dst[RIDX(dim,dim-1, dim-1)] = avg4(dim, dim-1, dim-1, src);

}

/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth function by calling the add_smooth_function() for
 *     each test function. When you run the benchmark program, it will
 *     test and report the performance of each registered test
 *     function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&another_smooth, another_smooth_descr);
 
}
