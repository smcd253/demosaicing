// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of width 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different widths and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

/* QUESTIONS for TA
*/

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel, BytesPerPixelOut;
	int width, height;
	int N; // filter window size
	float c,s; // spread parameters
	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [width = 256] [height = 256] [BytesPerPixelOut = 1]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4) BytesPerPixel = 1; // default is grey image
	else BytesPerPixel = atoi(argv[3]);

	// Check if width is specified
	if (argc < 5) width = 256;
	else width = atoi(argv[4]);

	// check if height is specified
	if (argc < 6) height = 256;
	else height = atoi(argv[5]);

	// check if BytesPerPixelOut is specified
	if (argc < 7) BytesPerPixelOut = 1;
	else BytesPerPixelOut = atoi(argv[6]);

	// check if N for filtering is specified
	if (argc < 8) N = 1;
	else N = atoi(argv[7]);

	// check if spread parameters are specified
	if (argc < 9) c = 1.0;
	else c = atoi(argv[8]);

	if (argc < 10) s = 1.0;
	else s = atoi(argv[9]);
	
	// Allocate source image data array
	unsigned char sourceImageData[height][width][BytesPerPixel];
	// Allocate dest image data array
	unsigned char destImageData[height][width][BytesPerPixelOut];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) 
	{
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(sourceImageData, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	float last;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			float num, den, w, t2_min;
			// scan NXN square around source image pixel and find uniform average of all pixel values
			for (int l = -(N-1)/2; l <= (N-1)/2; l++)
			{
				for (int k = -(N-1)/2; k <= (N-1)/2; k++)
				{
					float t1 = -1.0*(powf(float(i) - float(i + k), 2.0) + powf(float(j) - float(j + l), 2.0))/(2*c*c);
					// note: ||A + B||^2 = (||A|| + ||B||)^2, ||A|| = sqrt(a1^2 + ... + an^2)
					// note: ‖u−v‖^2 = ‖u‖^2−2u^(T)v+‖v‖^2.
					float Iij = sqrt((float)i*i + (float)j*j);
					float Ilk = sqrt((float)((i+l)*(i+l)) + (float)((j+k)*(j+k)));
					float t2 = -1.0*powf(Iij - Ilk,2.0)/(2*s*s);
					//float t2 = -1.0*(powf((float)sourceImageData[j][i][0] - (float)sourceImageData[j + l][i + k][0], 2.0))/(2*s*s);
					w = expf(t1 + t2); 
					num += (float)sourceImageData[j + l][i + k][0] * w;
					den += w;
				}
			}
			float cur = num/den;
			destImageData[j][i][0] = (unsigned char)cur; 
			if (cur != last) printf("destImageData[%d][%d][0] = %f\n", j, i, cur);
			last = cur;
		}
	}
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) 
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

	fwrite(destImageData, sizeof(unsigned char), height*width*BytesPerPixelOut, file);
	fclose(file);

	return 0;
}
