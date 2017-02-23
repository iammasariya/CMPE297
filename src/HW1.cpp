/*
 * HW1.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: pranav
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

void convolution2D(Mat src, int k)
{
	Mat dest, kernel;
	kernel = Mat::ones(k,k,CV_32F)/(float) k*k;

	filter2D(src,dest,-1,kernel,Point(-1,-1),0,BORDER_DEFAULT);
	imshow( "filter2D HW1_normalBox", dest );
}

void getGaussianBlurr(Mat src, int k)
{
	Mat dest;

	GaussianBlur( src, dest, Size( k, k ), 0, 0 );
	imshow( "filter2D HW1_gaussian", dest );
}

void getGaussianWithKernel(Mat src, int k)
{
	Mat dest, kernel;
	int sigma;

	sigma = 0.3*((k-1)*0.5 - 1) + 0.8;
	kernel = getGaussianKernel(k,sigma);

	filter2D(src,dest,-1,kernel,Point(-1,-1),0,BORDER_DEFAULT);
	imshow( "filter2D HW2_gaussian_kernel", dest );
}

void getLoG(Mat src, int k){
	Mat dest,grey_dest,LoGdest,kernel;

	GaussianBlur( src, dest, Size( k, k ), 0, 0 );
	cvtColor( dest, grey_dest, CV_BGR2GRAY );

	Laplacian( grey_dest, LoGdest,CV_16S, k, 1, 0, BORDER_DEFAULT );
	imshow( "filter2D HW3_LoG", LoGdest );
}

int main(int argc, char** argv){
	Mat src, grSrc;

	src = imread(argv[1],1);

	if(!src.data)
	{
		return -1;
	}
	imshow( "filter2D HW1_src", src );
	cv::cvtColor(src, grSrc, CV_BGR2GRAY);
	imshow( "filter2D HW1_grey", grSrc );

	convolution2D(grSrc,3);
	getGaussianBlurr(grSrc,15);
	getGaussianWithKernel(grSrc,15);
	getLoG(src,15);

	waitKey(0);

	return 0;
}


