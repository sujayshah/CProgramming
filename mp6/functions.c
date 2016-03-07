#include "imageData.h"
#include "functions.h"

/*
 * INTRODUCTORY PARAGRAPH
 * ----------------------
 * The functions below implement various image manipulation techniques including: grayscale conversion; translations and blurring. In each case, the RGBA values for each pixel of the input image
 * have been stored into separate arrays on which the following operations are performed. The grayscale function works by multiplying each of these values with their respective weights and
 * summing them together to get a grayscale value for each pixel. The colour threshold checks the RGBA components of each pixel against respective threshold values. If each of them exceed the
 * threshold, the pixel remains unchanged from its input. Otherwise, it is set to black. The flip vertical function simply switches all the rows of the input image pixels, whilst keeping the 
 * columns fixed. Finally, blurring is carried out by first designing a filter using a mathematical equation. This filter is then applied to the input image, where the output pixel is equal to
 * the weighted sum of its surrounding pixels upon application of the filter.
 */  


/*
 * calculate_cosine_filter - calculates the cosine filter values
 * INTPUTS:  int radius- integer indicating the size of array. 
 *           The filter has 2*radius+1 rows and 2*radius+1 columns
 * OUTPUTS:  cosine_fitler - pointer to the 1-D array of size 
 *           (2*radius+1)*(2*radius+1). Appropriate space has already been
 *           allocated. This function must compute
 *           the appropriate values of this array as described in the wiki
 * RETURN VALUE: none
 */
void calculate_cosine_filter(double *cos_filter,int radius)
{
	int i, j, k; 
	double x, y;
	double weight = 0.0;
	int length = 2*radius + 1;
	
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < length; j++)
		{
			x = j - radius;
			y = i - radius;
			cos_filter[length*i + j] = cos((M_PI*x)/(2*radius)) + cos((M_PI*y)/(2*radius));
		}
	}

	for(k = 0; k < length*length; k++)
	{
		weight = weight + cos_filter[k];		
	}

	for(k = 0; k < length*length; k++)
	{
		cos_filter[k] = cos_filter[k]/weight;
	}	 		
}

/* convolve_image - performs a convolution between a filter and image
 * INPUTS: in_red - pointer to the input red channel (1-D array)
 *         in_green - pointer to the input green channel (1-D array)
 *         in_blue - pointer to the input blue channel (1-D array) 
 *         in_alpha - pointer to the input alpha channel (1-D array)
 *         filter - pointer to the convolution filter (1-D array)
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: out_red - pointer to the output red channel (1-D array)
 *          out_green - pointer to the output green channel (1-D array)
 *          out_blue - pointer to the output blue channel (1-D array)
 *          out_alpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Don't alter the values of the input image.
 *       Filter is already initialized and contains desired values.
 *       Appropriate space has been allocated for output arrays. 
 */
void convolve_image(uint8_t *in_red,uint8_t *in_green,uint8_t *in_blue,
                   uint8_t *in_alpha, uint8_t *out_red,uint8_t *out_green,
                   uint8_t *out_blue,uint8_t *out_alpha,const double *filter,
                   int radius,int width,int height)
{
	int a, b, c, d, i, j, k, x, y, area ,length;
	double in_sum_red, in_sum_green, in_sum_blue;
	in_sum_red = 0.0;
	in_sum_green = 0.0;
	in_sum_blue = 0.0;	
	area = width*height;
	length = 2*radius + 1;


	if(radius < 1)
	{
		for(k = 0; k < area; k++)
		{
			out_red[k] = in_red[k];
			out_green[k] = in_green[k];
			out_blue[k] = in_blue[k];
			out_alpha[k] = in_alpha[k];
		}
		return;
	}

	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			for(i = -radius; i < radius + 1; i++)
			{
				for(j = -radius; j < radius + 1; j++)
				{
					a = i + radius;
					b = j + radius;
					c = x + i;
					d = y + j;

					if(c < 0 || c > width-1 || d < 0 || d > height-1)
					{
						c = 0;
						d = 0;
					}
					else
					{
						in_sum_red = in_sum_red + filter[b*length + a]*in_red[d*width + c];
						in_sum_green = in_sum_green + filter[b*length + a]*in_green[d*width + c];
						in_sum_blue = in_sum_blue + filter[b*length + a]*in_blue[d*width + c];						
					}
				}
				//out_sum_red = out_sum_red + in_sum_red;
				//out_sum_green = out_sum_green + in_sum_green;
				//out_sum_blue = out_sum_blue + in_sum_blue;
			}
			out_red[y*width + x] = in_sum_red;
			out_green[y*width + x] = in_sum_green;
			out_blue[y*width + x] = in_sum_blue;
			out_alpha[y*width + x] = in_alpha[y*width + x];
			in_sum_red = 0.0;
			in_sum_green = 0.0;
			in_sum_blue = 0.0;
		}
	}						
}

/* convert_to_gray - convert the input image to grayscale
 * INPUTS: in_red - pointer to the input red channel (1-D array)
 *         in_green - pointer to the input green channel (1-D array)
 *         in_blue - pointer to the input blue channel (1-D array)
 *         in_alpha - pointer to the input alpha channel (1-D array)
 *         gmonomult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale (3 element array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: out_red - pointer to the output red channel (1-D array)
 *          out_green - pointer to the output green channel (1-D array)
 *          out_blue - pointer to the output blue channel (1-D array)
 *          out_alpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       gmonomult contains the desired grayscale weights.
 *       Appropriate space has been allocated for output arrays. 
 *       Don't alter the values of the input image.
 */
void convert_to_gray(uint8_t *in_red,uint8_t *in_green,uint8_t *in_blue,
                   uint8_t *in_alpha,uint8_t *out_red,uint8_t *out_green,
                   uint8_t *out_blue,uint8_t *out_alpha,
                   const double *gmonomult,int width,int height)
{
	int i, area;
	double a, b, c, gray_num;

	area = width*height;

	for(i = 0; i < area; i++)
	{
		a = in_red[i]*gmonomult[0];
		b = in_green[i]*gmonomult[1];
		c = in_blue[i]*gmonomult[2];		
		
		gray_num = a + b + c;
		out_red[i] = out_green[i] = out_blue[i] = gray_num;
		out_alpha[i] = in_alpha[i];
	}
}

/* flip_vertical- flips image vertically such that the bottom row of pixels
 *                in the input image is the top row of pixels in the output 
 *                image, the second most bottom row in the input image is the 
 *                second row from the top of the input image, and so on. This should
 *                flip the image upside-down.
 * INPUTS: in_red - pointer to the input red channel (1-D array)
 *         in_green - pointer to the input green channel (1-D array)
 *         in_blue - pointer to the input blue channel (1-D array)
 *         in_alpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: out_red - pointer to the output red channel (1-D array)
 *          out_green - pointer to the output green channel (1-D array)
 *          out_blue - pointer to the output blue channel (1-D array)
 *          out_alpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays. 
 *       Don't alter the values of the input image.
 */
void flip_vertical(uint8_t *in_red,uint8_t *in_green,uint8_t *in_blue,
                 uint8_t *in_alpha,uint8_t *out_red,uint8_t *out_green,
                 uint8_t *out_blue,uint8_t *out_alpha,int width,int height)
{
	int i, j;
	
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			out_red[width*i + j] = in_red[width*(height-1-i) + j];
			out_green[width*i + j] = in_green[width*(height-1-i) + j];
			out_blue[width*i + j] = in_blue[width*(height-1-i) + j];
			out_alpha[width*i + j] = in_alpha[width*(height-1-i) + j];
		}
	}
}

/* color_threshold - for each pixel of input image, compares value to red, green, and blue threshold.
                     If the values exceed all three thresholds, set the output image to the input image values. 
                     Otherwise, set them to zero. Alpha should remain unchanged.
 * INPUTS: in_red - pointer to the input red channel (1-D array)
 *         in_green - pointer to the input green channel (1-D array)
 *         in_blue - pointer to the input blue channel (1-D array)
 *         in_alpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: out_red - pointer to the output red channel (1-D array)
 *          out_green - pointer to the output green channel (1-D array)
 *          out_blue - pointer to the output blue channel (1-D array)
 *          out_alpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays. 
 *       Don't alter the values of the input image.
 */
void color_threshold(uint8_t *in_red,uint8_t *in_green,uint8_t *in_blue,
                 uint8_t *in_alpha,uint8_t *out_red,uint8_t *out_green,
                 uint8_t *out_blue,uint8_t *out_alpha,int width,int height,
                 int red_threshold,int blue_threshold,int green_threshold)
{
	int i, area;

	area = width*height;

	for(i = 0; i < area; i++)
	{
		if(in_red[i] > red_threshold)
		{
			if(in_green[i] > green_threshold)
			{
				if(in_blue[i] > blue_threshold)
				{
					out_red[i] = in_red[i];
					out_green[i] = in_green[i];
					out_blue[i] = in_blue[i];
					out_alpha[i] = in_alpha[i];
				}
				else
				{
					out_red[i] = out_green[i] = out_blue[i] = 0;
					out_alpha[i] = 255; 
				}
			}
			else
			{
				out_red[i] = out_green[i] = out_blue[i] = 0;
				out_alpha[i] = 255; 
			}
		}
		else
		{
			out_red[i] = out_green[i] = out_blue[i] = 0;
			out_alpha[i] = 255; 
		}
	}	     
}
