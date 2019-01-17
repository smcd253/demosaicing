// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

/* QUESTIONS for TA
1. do I have the right idea for the implementation of bilinear interpolation?
*/
void blerp (/*unsigned char (*Imagedata)[Size][Size], unsigned char (*destImageData)[Size][3]*/)
{
	// 	// assume layout:
	// /*
	//   0 1 2 3
	// 0 G R G R
	// 1 B G B G
	// 2 G R G R
	// 3 B G B G
	// */
	// for (int i = 0; i < Size; i++)
	// {
	// 	for (int j = 0; j < Size; j++)
	// 	{ 
	// 		/* Case 1 (green center 1)
	// 		G B G
	// 		R G R
	// 		G B G
	// 		*/
	// 		if ((i % 2 == 0) && (j % 2 == 0))
	// 		{
	// 			// R = 0, G = 1, B = 2
	// 			// green = center pixel
	// 			destImageData[i][j][1] = Imagedata[i][j][1];
	// 			// red = average of left and right
	// 			destImageData[i][j][0] = (unsigned char)(0.5*((float)Imagedata[i-1][j][0] + (float)Imagedata[i+1][j][0]));
	// 			// blue = average of top and bottom
	// 			destImageData[i][j][2] = (unsigned char)(0.5*((float)Imagedata[i][j+1][0] + (float)Imagedata[i][j-1][0]));

	// 		}
	// 		/* Case 2 (green center 2)
	// 		G R G
	// 		B G B
	// 		G R G
	// 		*/
	// 		else if ((i % 2 == 1) && (j % 2 == 1))
	// 		{
	// 			// R = 0, G = 1, B = 2
	// 			// green = center pixel
	// 			destImageData[i][j][1] = Imagedata[i][j][1];
	// 			// blue = average of left and right
	// 			destImageData[i][j][2] = (unsigned char)(0.5*((float)Imagedata[i-1][j][0] + (float)Imagedata[i+1][j][0]));
	// 			// red = average of top and bottom
	// 			destImageData[i][j][0] = (unsigned char)(0.5*((float)Imagedata[i][j+1][0] + (float)Imagedata[i][j-1][0]));
	// 		}
	// 		/* Case 3 (red center)
	// 		B G B
	// 		G R G
	// 		B G B
	// 		*/
	// 		else if ((i % 2 == 1) && (j % 2 == 0))
	// 		{
	// 			// R = 0, G = 1, B = 2
	// 			// red = center pixel
	// 			destImageData[i][j][0] = Imagedata[i][j][0];
	// 			// green = average of top, bottom, left, and right
	// 			destImageData[i][j][1] = (unsigned char)(0.25*((float)Imagedata[i-1][j][0] + 
	// 															(float)Imagedata[i+1][j][0]) +
	// 															(float)Imagedata[i][j+1][0] + 
	// 															(float)Imagedata[i][j-1][0]);
	// 			// blue = average of topLeft, topRight, bottomLeft, and bottomRight
	// 			destImageData[i][j][2] = (unsigned char)(0.25*((float)Imagedata[i-1][j-1][0] + 
	// 															(float)Imagedata[i+1][j-1][0]) +
	// 															(float)Imagedata[i-1][j+1][0] + 
	// 															(float)Imagedata[i+1][j+1][0]);
	// 		}
	// 		/* Case 4 (blue center)
	// 		R G R
	// 		G B G
	// 		R G R
	// 		*/
	// 		else if ((i % 2 == 1) && (j % 2 == 0))
	// 		{
	// 			// R = 0, G = 1, B = 2
	// 			// red = center pixel
	// 			destImageData[i][j][2] = Imagedata[i][j][0];
	// 			// green = average of top, bottom, left, and right
	// 			destImageData[i][j][1] = (unsigned char)(0.25*((float)Imagedata[i-1][j][0] + 
	// 															(float)Imagedata[i+1][j][0]) +
	// 															(float)Imagedata[i][j+1][0] + 
	// 															(float)Imagedata[i][j-1][0]);
	// 			// red = average of topLeft, topRight, bottomLeft, and bottomRight
	// 			destImageData[i][j][0] = (unsigned char)(0.25*((float)Imagedata[i-1][j-1][0] + 
	// 															(float)Imagedata[i+1][j-1][0]) +
	// 															(float)Imagedata[i-1][j+1][0] + 
	// 															(float)Imagedata[i+1][j+1][0]);
	// 		}
	// 	}
	// }
}

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	
	// Allocate source image data array
	unsigned char Imagedata[Size][Size][BytesPerPixel];
	// Allocate dest image data array
	unsigned char destImageData[Size][Size][3];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
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
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{ 
			/* Case 1 (green center 1)
			G B G
			R G R
			G B G
			*/
			if ((i % 2 == 0) && (j % 2 == 0))
			{
				if ((i != 0) && (j != 0))
				{
					// R = 0, G = 1, B = 2
					// green = center pixel
					destImageData[i][j][1] = Imagedata[i][j][1];
					// red = average of left and right
					destImageData[i][j][0] = (unsigned char)(0.5*((float)Imagedata[i-1][j][0] + (float)Imagedata[i+1][j][0]));
					// blue = average of top and bottom
					destImageData[i][j][2] = (unsigned char)(0.5*((float)Imagedata[i][j+1][0] + (float)Imagedata[i][j-1][0]));
				}
				else
				{
					
				}
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
				destImageData[i][j][1] = Imagedata[i][j][1];
				// blue = average of left and right
				destImageData[i][j][2] = (unsigned char)(0.5*((float)Imagedata[i-1][j][0] + (float)Imagedata[i+1][j][0]));
				// red = average of top and bottom
				destImageData[i][j][0] = (unsigned char)(0.5*((float)Imagedata[i][j+1][0] + (float)Imagedata[i][j-1][0]));
			}
			/* Case 3 (red center)
			B G B
			G R G
			B G B
			*/
			else if ((i % 2 == 1) && (j % 2 == 0))
			{
				// R = 0, G = 1, B = 2
				// red = center pixel
				destImageData[i][j][0] = Imagedata[i][j][0];
				// green = average of top, bottom, left, and right
				destImageData[i][j][1] = (unsigned char)(0.25*((float)Imagedata[i-1][j][0] + 
																(float)Imagedata[i+1][j][0]) +
																(float)Imagedata[i][j+1][0] + 
																(float)Imagedata[i][j-1][0]);
				// blue = average of topLeft, topRight, bottomLeft, and bottomRight
				destImageData[i][j][2] = (unsigned char)(0.25*((float)Imagedata[i-1][j-1][0] + 
																(float)Imagedata[i+1][j-1][0]) +
																(float)Imagedata[i-1][j+1][0] + 
																(float)Imagedata[i+1][j+1][0]);
			}
			/* Case 4 (blue center)
			R G R
			G B G
			R G R
			*/
			else if ((i % 2 == 1) && (j % 2 == 0))
			{
				// R = 0, G = 1, B = 2
				// red = center pixel
				destImageData[i][j][2] = Imagedata[i][j][0];
				// green = average of top, bottom, left, and right
				destImageData[i][j][1] = (unsigned char)(0.25*((float)Imagedata[i-1][j][0] + 
																(float)Imagedata[i+1][j][0]) +
																(float)Imagedata[i][j+1][0] + 
																(float)Imagedata[i][j-1][0]);
				// red = average of topLeft, topRight, bottomLeft, and bottomRight
				destImageData[i][j][0] = (unsigned char)(0.25*((float)Imagedata[i-1][j-1][0] + 
																(float)Imagedata[i+1][j-1][0]) +
																(float)Imagedata[i-1][j+1][0] + 
																(float)Imagedata[i+1][j+1][0]);
			}
		}
	}
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(destImageData, sizeof(unsigned char), Size*Size*3, file);
	fclose(file);

	return 0;
}
