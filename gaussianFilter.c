#include <opencv2/opencv.hpp>

IplImage* gaussianFilter(IplImage* src) {
	IplImage* image = cvCreateImage(cvGetSize(src), src->depth, 1);
	int nRadius = 1;
	int nSum = 0;
	for(int i = nRadius; i < src->height - nRadius; ++i) {
		for(int j = nRadius; j < src->widthStep - nRadius; ++j) {
			nSum = 0;
			for(int k = -nRadius; k <= nRadius; ++k) {
				for(int l = -nRadius; l <=nRadius; ++l) {
					if((k == -1 && l == -1) || (k == 1 && l == -1) || (k == -1 && l == 1) || (k == 1 && l == 1)) {
						nSum += (uchar)(src->imageData[src->widthStep * (i + k) + j + l]);
					}
					if((k == 0 && l == -1) || (k == -1 && l == 0) || (k == 1 && l == 0) || (k == 0 && l == 1)) {
						nSum += 2 * (uchar)(src->imageData[src->widthStep * (i + k) + j + l]);
					}
					else {
						nSum += 4 * (uchar)(src->imageData[src->widthStep * (i + k) + j + l]);
					}
				}
			}
			image->imageData[image->widthStep * i + j] = (uchar)(nSum / 16);
		}
	}
	return image;
}

int main(int argc, char const *argv[])
{
	IplImage *srcImg = cvLoadImage(argv[1], CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	cvNamedWindow("Origin", CV_WINDOW_AUTOSIZE);
	cvShowImage("Origin", srcImg);
	cvWaitKey(0);
	IplImage *destImg = gaussianFilter(srcImg);
	cvNamedWindow("Gaussian", CV_WINDOW_AUTOSIZE);
	cvShowImage("Gaussian", destImg);
	cvWaitKey(0);
	return 0;
}