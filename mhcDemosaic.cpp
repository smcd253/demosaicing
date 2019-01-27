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

unsigned char greenAtRedOrBlue(unsigned char ***sourceImageData, int width, int i, int j)
{
	// red or blue
						// red/blue components
	return (1.0/9.0) * (4.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j))-
						(float)*(((unsigned char *)sourceImageData + (i)*width) + (j-2))-
						(float)*(((unsigned char *)sourceImageData + (i)*width) + (j+2))-
						(float)*(((unsigned char *)sourceImageData + (i+2)*width) + (j))-
						(float)*(((unsigned char *)sourceImageData + (i-2)*width) + (j))
						+			
					// green components
					2.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j-1))+
					2.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j+1))+
					2.0 * (float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j))+
					2.0 * (float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j)));
}
unsigned char redAtBlue_or_blueAtRed(unsigned char ***sourceImageData, int width, int i, int j)
{
	// red or blue
					// major axis components
	return (1.0/9.0) * (6.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j))-
					3.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i)*width) + (j-2))-
					3.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i)*width) + (j+2))-
					3.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i+2)*width) + (j))-
					3.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i-2)*width) + (j))
						+
						// 2ndary axis components
						2.0 * (float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j-1))+
						2.0 * (float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j+1))+
						2.0 * (float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j-1))+
						2.0 * (float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j+1)));
}
unsigned char redAtGreenC1_or_blueAtGreenC2(unsigned char ***sourceImageData, int width, int i, int j)
{
					// green components
	return (1.0/11.0) * (5.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j))-
							(float)*(((unsigned char *)sourceImageData + (i)*width) + (j-2))-
							(float)*(((unsigned char *)sourceImageData + (i)*width) + (j+2))-
					1.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i+2)*width) + (j))-
					1.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i-2)*width) + (j))-
							(float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j-1))-
							(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j+1))-
							(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j-1))-
							(float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j+1))
							+
					// horizontal (red or blue) components
					4.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j-1))+
					4.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j+1)));
}
unsigned char blueAtGreenC1_or_redAtGreenC2(unsigned char ***sourceImageData, int width, int i, int j)
{
					// green components
	return (1.0/11.0) * (5.0 * (float)*(((unsigned char *)sourceImageData + (i)*width) + (j))-
					1.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i)*width) + (j-2))-
					1.0/2.0	* (float)*(((unsigned char *)sourceImageData + (i)*width) + (j+2))-
							(float)*(((unsigned char *)sourceImageData + (i+2)*width) + (j))-
							(float)*(((unsigned char *)sourceImageData + (i-2)*width) + (j))-
							(float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j-1))-
							(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j+1))-
							(float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j-1))-
							(float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j+1))
							+
					// vertical (red or blue) components
					4.0 * (float)*(((unsigned char *)sourceImageData + (i-1)*width) + (j))+
					4.0 * (float)*(((unsigned char *)sourceImageData + (i+1)*width) + (j)));
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
				destImageData[i][j][0] = redAtGreenC1_or_blueAtGreenC2((unsigned char ***)Imagedata, width, i, j);
				// blue = average of top and bottom
				destImageData[i][j][2] = blueAtGreenC1_or_redAtGreenC2((unsigned char ***)Imagedata, width, i, j);
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
				destImageData[i][j][2] = redAtGreenC1_or_blueAtGreenC2((unsigned char ***)Imagedata, width, i, j);
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
				// red
				destImageData[i][j][0] = Imagedata[i][j][0];
				// green
				destImageData[i][j][1] = greenAtRedOrBlue((unsigned char ***)Imagedata, width, i, j);
				// blue
				destImageData[i][j][2] = redAtBlue_or_blueAtRed((unsigned char ***)Imagedata, width, i, j);
			}
			/* Case 4 (blue center)
			R G R
			G B G
			R G R
			*/
			else if ((i % 2 == 1) && (j % 2 == 0))
			{
				// blue
				destImageData[i][j][2] = Imagedata[i][j][0];
				// green
				destImageData[i][j][1] = greenAtRedOrBlue((unsigned char ***)Imagedata, width, i, j);
				// red
				destImageData[i][j][0] = redAtBlue_or_blueAtRed((unsigned char ***)Imagedata, width, i, j);
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
