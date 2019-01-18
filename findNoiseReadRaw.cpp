// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of width 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different widths and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

/* QUESTIONS for TA
*/

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel, BytesPerPixelOut;
	int width, height;
	const char *outputFile;
	
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

	// output file
	if (argc < 8) outputFile = "HW1_images/noiseOutput.raw";
	else outputFile = argv[7];
	
	
	// Allocate noisy image data array
	unsigned char cleanImageData[height][width][BytesPerPixel];
	// allocate clean image data array
	unsigned char noisyImageData[height][width][BytesPerPixel];
	// Allocate dest image data array
	unsigned char destImageData[height][width][BytesPerPixelOut];

	// Read clean image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) 
	{
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(cleanImageData, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	// Read noisy image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[2],"rb"))) 
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fread(noisyImageData, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	// loop through both image arrays and subtract the clean image from the noisy image pizel by pixel
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//printf("pixel (%d,%d) = %f\n", i, j, (float)noisyImageData[i][j][0]);
			destImageData[i][j][0] = noisyImageData[i][j][0] - cleanImageData[i][j][0];
		}
	}
	
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(outputFile,"wb"))) 
	{
		cout << "Cannot open file: " << outputFile << endl;
		exit(1);
	}

	printf("outputFile = %s\n", outputFile);
	fwrite(destImageData, sizeof(unsigned char), height*width*BytesPerPixelOut, file);
	fclose(file);

	return 0;
}
