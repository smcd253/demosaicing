// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of width 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different widths and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "demosaic.h"

using namespace std;

/* QUESTIONS for TA
*/

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel, BytesPerPixelOut;
	int width, height;
	
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
	
	
	// Allocate source image data array
	unsigned char Imagedata[height][width][BytesPerPixel];
	// Allocate dest image data array
	unsigned char destImageData[height][width][BytesPerPixelOut];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) 
	{
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//blerp(Imagedata, destImageData);
		// assume layout:
	/*
	  0 1 2 3
	0 G R G R
	1 B G B G
	2 G R G R
	3 B G B G
	*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{ 
			// boundary cases
			// top row
			if (i == 0)
			{
				// top left corner (green)
				if (j == 0)
				{
					
				}
				// top middle
				else if (j != width - 1)
				{
					
				}
				// top right corner
				else
				{
					
				}
			}
			else if (i == height - 1)
			{
				// bottom left corner (green)
				if (j == 0)
				{
					
				}
				// bottom middle
				else if (j != width - 1)
				{
					
				}
				// bottom right corner
				else
				{
					
				}
			}
			// top right corner
			else if ((i == 0) && (j == width - 1))
			{

			}
			// bottom right corner
			else if ((i == height - 1) && (j == width - 1))
			{

			}
			// interior cases
			/* Case 1 (green center 1)
			G B G
			R G R
			G B G
			*/
			else if ((i % 2 == 0) && (j % 2 == 0))
			{
				// R = 0, G = 1, B = 2
				// green = center pixel
				destImageData[i][j][1] = Imagedata[i][j][0];
				// red = average of left and right
				destImageData[i][j][0] = (unsigned char)(0.5*((float)Imagedata[i][j-1][0] + (float)Imagedata[i][j+1][0]));
				// blue = average of top and bottom
				destImageData[i][j][2] = (unsigned char)(0.5*((float)Imagedata[i+1][j][0] + (float)Imagedata[i-1][j][0]));
			}
			/* Case 2 (green center 2)
			G R G
			B G B
			G R G
			*/
			else if ((i % 2 == 1) && (j % 2 == 1))
			{
				// R = 0, G = 1, B = 2
				// green = center pixel
				destImageData[i][j][1] = Imagedata[i][j][0];
				// blue = average of left and right
				destImageData[i][j][2] = (unsigned char)(0.5*((float)Imagedata[i][j-1][0] + (float)Imagedata[i][j+1][0]));
				// red = average of top and bottom
				destImageData[i][j][0] = (unsigned char)(0.5*((float)Imagedata[i+1][j][0] + (float)Imagedata[i-1][j][0]));
			}
			/* Case 3 (red center)
			B G B
			G R G
			B G B
			*/
			else if ((i % 2 == 0) && (j % 2 == 1))
			{
				// R = 0, G = 1, B = 2
				// red = center pixel
				destImageData[i][j][0] = Imagedata[i][j][0];
				// green = average of top, bottom, left, and right
				destImageData[i][j][1] = (unsigned char)(0.25*((float)Imagedata[i-1][j][0] + 
																(float)Imagedata[i+1][j][0]+
																(float)Imagedata[i][j+1][0] + 
																(float)Imagedata[i][j-1][0]));
				// blue = average of topLeft, topRight, bottomLeft, and bottomRight
				destImageData[i][j][2] = (unsigned char)(0.25*((float)Imagedata[i-1][j-1][0] + 
																(float)Imagedata[i+1][j-1][0] +
																(float)Imagedata[i-1][j+1][0] + 
																(float)Imagedata[i+1][j+1][0]));
			}
			/* Case 4 (blue center)
			R G R
			G B G
			R G R
			*/
			else if ((i % 2 == 1) && (j % 2 == 0))
			{
				// R = 0, G = 1, B = 2
				// blue = center pixel
				destImageData[i][j][2] = Imagedata[i][j][0];
				// green = average of top, bottom, left, and right
				destImageData[i][j][1] = (unsigned char)(0.25*((float)Imagedata[i-1][j][0] + 
																(float)Imagedata[i+1][j][0] +
																(float)Imagedata[i][j+1][0] + 
																(float)Imagedata[i][j-1][0]));
				// red = average of topLeft, topRight, bottomLeft, and bottomRight
				destImageData[i][j][0] = (unsigned char)(0.25*((float)Imagedata[i-1][j-1][0] + 
																(float)Imagedata[i+1][j-1][0] +
																(float)Imagedata[i-1][j+1][0] + 
																(float)Imagedata[i+1][j+1][0]));
			}
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
