// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of width 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different widths and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

unsigned char avgLeftRight(unsigned char ***sourceImageData, int width, int i, int j)
{
	if (j > 0)
	{
		if (j < width - 1)
			return (unsigned char)(0.5 * ((float)*(((unsigned char *)sourceImageData + (i)*width) + (j-1))
										+ (float)*(((unsigned char *)sourceImageData + (i)*width) + (j+1))));  
		else
			return *(((unsigned char *)sourceImageData + (i)*width) + (j-1));
	}	
	else
		return *(((unsigned char *)sourceImageData + (i)*width) + (j+1));
}

unsigned char avgTopBottom(unsigned char ***sourceImageData, int height, int width, int i, int j)
{
	if (i > 0)
	{
		if (i < height - 1)
			return (unsigned char)(0.5 * ((float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j))
									+ (float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j))));
		else
			return *(((unsigned char *)sourceImageData + (i-1)*width) + (j));
	}
	else
		return *(((unsigned char *)sourceImageData + (i+1)*width) + (j));
}

unsigned char avgTopBottomLeftRight(unsigned char ***sourceImageData, int height, int width, int i, int j)
{
	return (unsigned char)(0.5 * ((float)avgLeftRight((unsigned char ***) sourceImageData, width, i, j) + 
								(float)avgTopBottom((unsigned char ***) sourceImageData, height, width, i, j)));
}
unsigned char avgCorners(unsigned char ***sourceImageData, int height, int width, int i, int j)
{
	if (i > 0 && j > 0)
	{
		if (i < height - 1 && j < width - 1)
			return (unsigned char)(0.25 * ((float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j-1)) + 
										(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j-1)) + 
										(float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j+1)) + 
										(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j+1))));
		else if (i < height - 1)
			return (unsigned char)(0.5 * ((float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j-1)) + 
										(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j-1))));
		else if (j < width - 1)
			return (unsigned char)(0.5 * ((float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j-1)) + 
										(float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j+1))));
		else
			return *(((unsigned char *)sourceImageData + (i-1)*width) + (j-1));
	}
	else if (i > 0)
		return (unsigned char)(0.5 * ((float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j+1)) + 
									(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j+1))));
	else if (j > 0)
		return (unsigned char)(0.5 * ((float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j-1)) + 
									(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j+1))));
	else
		return *(((unsigned char *)sourceImageData + (i+1)*width) + (j+1));
}
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
			/* Case 1 (green center 1)
			G B G
			R G R
			G B G
			*/
			if ((i % 2 == 0) && (j % 2 == 0))
			{
				// R = 0, G = 1, B = 2
				// green = center pixel
				destImageData[i][j][1] = Imagedata[i][j][0];
				// red = average of left and right
				destImageData[i][j][0] = avgLeftRight((unsigned char ***)Imagedata, width, i, j);
				// blue = average of top and bottom
				destImageData[i][j][2] = avgTopBottom((unsigned char ***)Imagedata, height, width, i, j);
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
				destImageData[i][j][2] = avgLeftRight((unsigned char ***)Imagedata, width, i, j);
				// red = average of top and bottom
				destImageData[i][j][0] = avgTopBottom((unsigned char ***)Imagedata, height, width, i, j);
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
				destImageData[i][j][1] = avgTopBottomLeftRight((unsigned char ***)Imagedata, height, width, i, j);
				// blue = average of topLeft, topRight, bottomLeft, and bottomRight
				destImageData[i][j][2] = avgCorners((unsigned char ***)Imagedata, height, width, i, j);
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
				unsigned char avgTBLR = avgTopBottomLeftRight((unsigned char ***)Imagedata, height, width, i, j);
				//printf("green = %f\n", (float)avgTBLR);
				destImageData[i][j][1] = avgTBLR;
				// red = average of topLeft, topRight, bottomLeft, and bottomRight
				destImageData[i][j][0] = avgCorners((unsigned char ***)Imagedata, height, width, i, j);
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
