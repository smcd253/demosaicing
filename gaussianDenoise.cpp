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

float findMean(unsigned char ***sourceImageData, int width, int i, int j, int N)
{
	float sum = 0;
	// scan NXN square around source image pixel and find uniform average of all pixel values
	for (int nh = -(N-1)/2; nh <= (N-1)/2; nh++)
	{
		for (int nw = -(N-1)/2; nw <= (N-1)/2; nw++)
		{
			sum += (float)*(((unsigned char *)sourceImageData + (i+nh)*width) + (j+nw));
		}
	}
	return sum / (float)(N*N);
}
float findVariance(unsigned char ***sourceImageData, int width, int i, int j, int N, float mean)
{
	float squareDiff = 0;
	for (int nh = -(N-1)/2; nh <= (N-1)/2; nh++)
	{
		for (int nw = -(N-1)/2; nw <= (N-1)/2; nw++)
		{
			float pixelVal = (float)*(((unsigned char *)sourceImageData + (i+nh)*width) + (j+nw));
			//printf("pixelVal = %f\n", pixelVal);
			squareDiff += (pixelVal - mean) * (pixelVal - mean);
		}
	}
	return squareDiff / (float)(N*N);
}
float gaussian(unsigned char ***sourceImageData, int height, int width, int i, int j, int N)
{
	//printf("%f\n",(float)*(((unsigned char *)sourceImageData + (i)*width) + (j)));

	// find mean of matrix
	//float mean = findMean((unsigned char ***)sourceImageData, width, i, j, N);
	
	// next find variance of the matrix
	float variance = 1.0; //findVariance((unsigned char ***)sourceImageData, width, i, j, N, mean);
	//calculate final output
	float maskSum = 0.0;
	for (int nh = -(N-1)/2; nh <= (N-1)/2; nh++)
	{
		for (int nw = -(N-1)/2; nw <= (N-1)/2; nw++)
		{
			maskSum += (1.0/sqrtf(2*M_PI*variance))*expf(-(nw*nw + nh*nh)/(2*variance)) * (float)*(((unsigned char *)sourceImageData + (i+nh)*width) + (j+nw));
		}
	}
	float res = powf((1.0/N-1),2.0)*maskSum;
	printf("res = %f\n", res);
	return res;
}

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel, BytesPerPixelOut;
	int width, height;
	int N;
	
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
	if (argc < 8) N = 3;
	else N = atoi(argv[7]);
	
	
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
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			destImageData[i][j][0] = (unsigned char)gaussian((unsigned char ***)sourceImageData, height, width, i, j, N);
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
