#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cmath>
using namespace cv;
void gradient(Mat &src,Mat &dst,bool rgb){
    Mat gray;
    int r=src.rows,c=src.cols,i,j,k;
    if(rgb)cvtColor(src,gray,CV_BGR2GRAY);
    else gray=src.clone();
    dst.create(Size(c,r),CV_8UC1);
    for(i=1;i<r-1;i++){
	for(j=0;j<c-1;j++){
	    int sumx=0,sumy=0;
		for(k=0;k<9;k++){
		    Scalar intensity=gray.at<uchar>(i-(k/3)-1,j-1-k%3);
		    sumx=sumx+intensity.val[0]*(k%3-1);
		    sumy=sumy+intensity.val[0]*(k/3-1);
		}
	    int sum=sqrt((sumx*sumx+sumy*sumy)/18);
	    dst.at<uchar>(i,j)=sum;
	}
    }
}
